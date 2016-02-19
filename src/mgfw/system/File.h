#pragma once

#include <string>
#include <fstream>

/*
    The main reason behind making this class is to make
    file input and output more intuitive then it is with
    std::iostream.
    For this reason you may find some similar things to
    work a bit differently.
*/

/*
    TODO List:
        - Decide whether to separate Read, Write, ReadWrite in to their own files
        - Add support for << operator
        - Add seek/find returning bool, index, line
        - Add save function ( similar to close, just keeps the file opened )
            -> Is this really necessary?
*/

namespace mg {

class File {
public:
    enum Flags {
        Read        = 1 << 0,
        Write       = 1 << 1,
        ReadWrite   = 1 << 2,
        Binary      = 1 << 3,
        Clear       = 1 << 4,
        Append      = 1 << 5,
        Prepend     = 1 << 6,   // TODO(Smeky) This is not supported yet
    };

public:
    File();
    ~File();

    // Opens files with given flags
    bool open(const std::string& filename, File::Flags flags);
    bool isOpen() const;

    // Close the file
    void close();

    // Writes given string in to the file
    void write(const std::string& str);
    void write(const char* str, uint32_t n);

    std::string read();

//    // Looks for a string inside the file and returns first line
//    // that contains given string
//    // Returns empty string if nothing was found
//    std::string findLineContaining(const std::string& str);

private:
    // All handles where only one is active at the time
    std::fstream m_handle;
    // Stored flags provided in file opening
    File::Flags m_flags;
};

} // namespace mg
