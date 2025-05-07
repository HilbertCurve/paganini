/* date = March 16, 2025 5:07 PM */


#include "file.h"

#include <fstream>
#include <iostream>

#include "common.h"

namespace paganini {
    file::file() {
        this("/dev/null");
        this->fp = "/dev/null";
        this->binary = true;
    }

    file::file(const std::string &fp) {
        file_handle.open(fp, std::ios::in | std::ios::out | std::ios::binary);
        this->fp = fp;
        this->binary = true;
    }

    file::file(const std::string &fp, bool is_binary) {
        if (is_binary)
            file_handle.open(fp, std::ios::in | std::ios::out);
        else
            file_handle.open(fp, std::ios::in | std::ios::out | std::ios::binary);
        this->fp = fp;
        this->binary = false;
    }

    file::~file() {
        if (file_handle.is_open()) file_handle.close();
    }

    // Gets a line from a text file. Returns an empty string if line read from binary file.
    std::string file::get_line() {
        if (binary) {
            _p_warning("Cannot get line from binary file '%s'.", name.c_str());
            return "";
        }

        std::string ret;
        file_handle >> ret;
        if (file_handle.bad()) {
            _p_warning("Error while reading file '%s'", name.c_str());
            return "";
        }
        return ret;
    }

    // Sets the current position using an offset and an offset marker. See `man 2 lseek` for general structure.
    long file::seek(const long offset, seek_from whence) {
        file_handle.seekg(offset, static_cast<std::ios_base::seekdir>(whence));
        return file_handle.tellg();
    }

    // Returns the current position in the file.
    long file::tell() {
        return file_handle.tellg();
    }

    // Reads entire file contents into a char vector.
    // Resets position to old position before dump.
    long file::dump(std::vector<char> &out) {
        auto old_pos = tell();
        seek(0, end);
        auto len = tell();
        seek(old_pos, start);

        out.reserve(len);
        file_handle.read(out.data(), len);

        return len;
    }

    // note: this function is (very) unsafe!
    long file::read(void *buf, const long len) {
        auto old_pos = tell();
        file_handle.read(static_cast<char *>(buf), len);
        auto new_pos = tell();
        return new_pos - old_pos;
    }
} // paganini
