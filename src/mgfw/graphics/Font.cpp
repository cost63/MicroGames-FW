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

Texture& Font::getTex() {
    return m_glyphCatalog.begin()->second.texture;
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
    GlyphLayer layer;

    // Setup default texture
    Image image;
    image.create(Vec2u(charSize * 4, charSize * 4), Color::Transparent);

    layer.texture.copyFromImage(image);
    layer.lengths.resize(4, 0);

    return m_glyphCatalog.insert(std::make_pair(charSize, layer)).first->second;
}

Font::Glyph Font::addGlyph(uint16_t charCode, Font::GlyphLayer& layer) const {
    Glyph glyph;

    // White color for the glyph (colors are added in vertices through shaders)
    SDL_Color color;
    color.r = 255;
    color.g = 0;
    color.b = 0;
    color.a = 255;

    SDL_Surface* surface = TTF_RenderGlyph_Blended((TTF_Font*)m_handle, charCode, color);

    // Make sure glyph's surface was created properly
    if(!surface) {
        priv::logError(
                "Failed to setup font glyph with following errors:\n" +
                std::string(TTF_GetError())
        );

        return glyph;
    }

    // Convert pixels because TTF gives us wrong format
    uint8_t* pixels = Image::convertPixelFormat(
                            (uint8_t*)surface->pixels,
                            surface->w * surface->h,
                            priv::getFormatFromSDLFormat(surface->format->format),
                            Image::RGBA
                      );

    std::cout << Color((uint8_t*)surface->pixels) << std::endl;
    std::cout << Color(pixels) << std::endl;

    const Vec2u glyphSize   = Vec2u(surface->w, surface->h);
    const Vec2u texSize     = layer.texture.getSize();

    // Variables used when looking for free space in a row
    // Note: length of the first row is as default because in case we don't find
    // a free row, we enlarge the texture which will create free space in
    // all rows, thus we use the first one
    uint16_t rowIndex   = 0;
    uint16_t rowLength  = layer.lengths[0];
    bool wasRowFound    = false;

    // Find row that has space for the glyph
    for(uint16_t i = 0; i < layer.lengths.size(); i++) {
        uint16_t& length = layer.lengths[i];

        // If the glyph width fits in the row
        if(length + glyphSize.w < texSize.w ) {
            rowIndex    = i;
            rowLength   = length;
            wasRowFound = true;
            break;
        }
    }

    if(!wasRowFound) {
        enlargeLayerTexture(layer);
    }

    // Add glyph's width to the row's length
    layer.lengths[rowIndex] += glyphSize.w;

    // Get height of the current font. +1 is an offset to prevent some unwanted artifacts
    const int fontHeight = TTF_FontHeight((TTF_Font*)m_handle) + 1;
    const Vec2u glyphPos = Vec2u(rowLength, rowIndex * fontHeight);

    layer.texture.setPixels(pixels, glyphPos, glyphSize);

    // Store glyph's clip on the layer textures
    glyph.clip.x = glyphPos.x;
    glyph.clip.y = glyphPos.y;
    glyph.clip.w = glyphSize.w;
    glyph.clip.h = glyphSize.h;

    // Store the glyph in the layer
    layer.glyphs[charCode] = glyph;

    // Clean up the glyph surface and pixels
    SDL_FreeSurface(surface);
    delete[] pixels;

    return glyph;
}

void Font::enlargeLayerTexture(Font::GlyphLayer& layer) const {
    // For code readability
    Texture& texture = layer.texture;

    // Setup enlarged image
    Image enlarged;
    enlarged.create(texture.getSize() * 2);
    // Copy all pixels from original texture
    enlarged.copyPixels(texture.copyToImage().getPixels(), texture.getSize());

    // Re-create texture from the enlarged image
    texture.copyFromImage(enlarged);
}

} // namespace mg
