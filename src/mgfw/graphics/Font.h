#pragma once

#include <string>
#include <map>

#include "../math/Rect.h"
#include "../graphics/Texture.h"

namespace mg {

class Font {
public:
    struct Glyph {
        iRect clip;
    };

public:
    Font();
    ~Font();

    // Arg charSize serves to increase performance of creating text from string
    bool loadFromFile(const std::string& filename, uint16_t charSize = 11);

    Font::Glyph getGlyph(uint16_t charCode, uint16_t charSize) const;

private:
    /* Private structures */
    struct GlyphLayer {
        // Contains a glyph for each character code
        std::map<uint16_t, Glyph> glyphs;
        // Texture of all glyphs
        Texture texture;
    };

private:
    /* Private methods */
    void clear();

    bool setCurFontSize(uint16_t charSize) const;

    Font::GlyphLayer& addLayer(uint16_t charSize) const;
    Font::Glyph addGlyph(uint16_t charCode, Font::GlyphLayer& layer) const;

    void enlargeLayerTexture(Font::GlyphLayer& layer) const;

private:
    /* Member variables */
//    // We use this so we don't have to load font file over and over
//    // again when using different size of currently loaded font handle
//    void* m_file;             // Loaded font file

    mutable void* m_handle;         // Font's TTF handle
    std::string m_fontFilename;     // Stores font's filename so it can be reloaded when font size changes
    uint16_t m_curFontSize;         // Size of currently loaded font

    // Contains all glyph layers under charSize keys
    mutable std::map<uint16_t, GlyphLayer> m_glyphCatalog;
};

} // namespace mg

