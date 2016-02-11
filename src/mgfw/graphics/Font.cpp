#include "Font.h"

#include "SDL2/SDL_ttf.h"

#include "../system/ErrorLog.h"

namespace mg {

Font::Font()
: m_handle(nullptr)
, m_curFontSize(0)
{}

Font::~Font() {
    clear();
}

bool Font::loadFromFile(const std::string& filename, uint16_t charSize /*= 11*/) {
    clear();

    m_handle = TTF_OpenFont(filename.c_str(), charSize);

    if(!m_handle) {
        priv::logError(
                "Failed to open font at: " +
                filename +
                "\n" +
                TTF_GetError()
        );

        return false;
    }

    m_curFontSize   = charSize;
    m_fontFilename  = filename;

    return true;
}

Font::Glyph Font::getGlyph(uint16_t charCode, uint16_t charSize) const {
    // Look for glyph layer of given character size
    auto foundLayer = m_glyphCatalog.find(charSize);

    // If layer was found
    if(foundLayer != m_glyphCatalog.end()) {
        // Look for glyph of given character code
        auto foundGlyph = foundLayer->second.glyphs.find(charCode);

        // If glyph was found
        if(foundGlyph != foundLayer->second.glyphs.end()) {
            return foundGlyph->second;
        }
        else {
            // No glyph was found, create a new one
            return addGlyph(charCode, foundLayer->second);
        }
    }
    else {
        // No layer was found, create a new one
        GlyphLayer& layer = addLayer(charSize);

        // If current font has wrong character size
        if(m_curFontSize != charSize) {
            // Load font with correct size
            if(!setCurFontSize(charSize)) {
                return Glyph();
            }
        }

        // Also add the glyph
        return addGlyph(charCode, layer);
    }
}

/* Private */

void Font::clear() {
    if(m_handle) {
        TTF_CloseFont((TTF_Font*)m_handle);
    }
}

bool Font::setCurFontSize(uint16_t charSize) const {
    if(m_handle) {
        TTF_CloseFont((TTF_Font*)m_handle);
    }

    m_handle = TTF_OpenFont(m_fontFilename.c_str(), charSize);

    if(!m_handle) {
        priv::logError(
                "Failed to load font for character size change\n" +
                std::string(TTF_GetError())
        );

        return false;
    }

    return true;
}

Font::GlyphLayer& Font::addLayer(uint16_t charSize) const {
    return m_glyphCatalog.insert(std::make_pair(charSize, GlyphLayer())).first->second;
}

Font::Glyph Font::addGlyph(uint16_t charCode, Font::GlyphLayer& layer) const {
    Glyph glyph;

    // White color for the glyph (colors are added in vertices through shaders)
    SDL_Color color;
    color.r = 255;
    color.g = 255;
    color.b = 255;
    color.a = 255;

    SDL_Surface* surface = TTF_RenderGlyph_Blended((TTF_Font*)m_handle, charCode, color);

    if(!surface) {
        priv::logError(
                "Failed to setup font glyph with following errors:\n" +
                std::string(TTF_GetError())
        );

        return glyph;
    }



    return glyph;
}

void Font::enlargeLayerTexture(Font::GlyphLayer& layer) const {
    Image original = layer.texture.copyToImage();
}

} // namespace mg
