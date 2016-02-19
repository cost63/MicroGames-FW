#include "File.h"

#include "../system/ErrorLog.h"

namespace mg {

File::File()
{}

File::~File() {
    if(isOpen()) {
        m_handle.close();
    }
}

bool File::open(const std::string& filename, File::Flags flags) {
    std::ios_base::openmode mode;

    // Store given flags
    m_flags = flags;

    // TODO(Smeky) Improve these if statements and bitwise operations a bit
    //      -> Flag ReadWrite should not require its own bitwise value ( more likely combination of Read and Write flags )
    //      -> Flags Read and Write should be possible to add separately but keep the error handling
    // Convert Read and Write flags in to std open mode
    if(flags & Flags::ReadWrite) {
        mode = std::ios::in | std::ios::out;
    }
    else {
        if(flags & Flags::Read) {
            mode = std::ios::in;
        }
        else if(flags & Flags::Write) {
            mode = std::ios::out;
        }
        else {
            priv::logError("Unable to open file. Neither Read nor Write flags was specified", "[Warning]");

            return false;
        }
    }

    if(flags & Flags::Binary) {
        mode |= std::ios_base::binary;
    }

    if(flags & Flags::Append) {
        mode |= std::ios_base::app;
    }

    if(flags & Flags::Clear) {
        mode |= std::ios_base::trunc;
    }

    m_handle.open(filename.c_str(), mode);

    return isOpen();
}

bool File::isOpen() const {
    return m_handle.is_open();
}

void File::close() {
    if(isOpen()) {
        m_handle.close();
    }
}

void File::write(const std::string& str) {
    m_handle << str;
}

void File::write(const char* str, uint32_t n) {
    m_handle.write(str, n);
}

std::string File::read() {
    std::string input;

    // Make sure file can be read
    if(m_flags & (Flags::Read | Flags::ReadWrite)) {
        // Read whole file into the string
        // Ref: http://stackoverflow.com/questions/18816126/c-read-the-whole-file-in-buffer
        input = std::string((std::istreambuf_iterator<char>(m_handle)), std::istreambuf_iterator<char>());
    }

    return input;
}

} // namespace mg
