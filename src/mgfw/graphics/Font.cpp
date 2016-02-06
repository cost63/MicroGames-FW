#include "Font.h"

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H
#include FT_OUTLINE_H
#include FT_BITMAP_H
#include FT_STROKER_H

#include "../system/ErrorLog.h"

namespace mg {

Font::Font()
: m_library(nullptr)
, m_face(nullptr)
{}

Font::~Font() {
    clear();
}

bool Font::loadFromFile(const std::string& filename) {
    // Clean up
    clear();

    // Initialize FreeType
    FT_Library library;
    if(FT_Init_FreeType(&library) != 0) {
        priv::logError("Failed to initialize FreeType for font: " + filename);

        return false;
    }

    m_library = library;

    // Load the new font face
    FT_Face face;
    if(FT_New_Face(static_cast<FT_Library>(m_library), filename.c_str(), 0, &face) != 0) {
        priv::logError("Failed to create font face for: " + filename);

        return false;
    }

    m_face = face;

    return true;
}

void Font::clear() {
    if(m_face) {
        FT_Done_Face(static_cast<FT_Face>(m_face));
    }
}

} // namespace mg
