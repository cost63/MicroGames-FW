#pragma once

#include <string>

namespace mg {

class Font {
public:
    Font();
    ~Font();

    bool loadFromFile(const std::string& filename);

private:
    void clear();

private:
    void* m_handle;

};

} // namespace mg
