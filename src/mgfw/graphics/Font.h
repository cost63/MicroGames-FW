#pragma once

#include <string>

namespace mg {

/* Forward declarations */

class Font {
public:
    Font();
    ~Font();

    bool loadFromFile(const std::string& filename);

    void clear();

private:
    void* m_library;
    void* m_face;

};

} // namespace mg
