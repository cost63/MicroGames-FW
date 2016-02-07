#pragma once

#include <string>

namespace mg {

/* Forward declarations */

class Font {
public:
    Font();
    ~Font();

    void clear();

    bool loadFromFile(const std::string& filename);

private:
    void* m_library;
    void* m_face;

};

} // namespace mg
