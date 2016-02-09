#pragma once

#include <string>
#include <map>

#include "../math/Rect.h"

namespace mg {

class Font {
public:
    struct Glyph {
        iRect clip;
    };

public:
    Font();
    ~Font();

    bool loadFromFile(const std::string& filename);

    Font::Glyph getGlyph(uint16_t charCode, uint16_t charSize) const;

private:
    void clear();

private:
    void* m_handle;


    using GlyphLayer = std::map<uint16_t, Glyph>;
    using GlyphCatalog = std::map<uint16_t, GlyphLayer>;

    mutable GlyphCatalog m_glyphCatalog;

};

} // namespace mg
