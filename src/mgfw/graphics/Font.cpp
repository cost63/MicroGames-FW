#include "Font.h"

#include "SDL2/SDL_ttf.h"

#include "../system/ErrorLog.h"

namespace mg {

Font::Font()
: m_handle(nullptr)
{}

Font::~Font() {
    clear();
}

bool Font::loadFromFile(const std::string& filename) {
    clear();

    m_handle = TTF_OpenFont(filename.c_str(), 11);

    if(!m_handle) {
        priv::logError(
                "Failed to open font at: " +
                filename +
                "\n" +
                TTF_GetError()
        );

        return false;
    }

    return true;
}

void Font::clear() {
    if(m_handle) {
        TTF_CloseFont((TTF_Font*)m_handle);
    }
}

} // namespace mg
