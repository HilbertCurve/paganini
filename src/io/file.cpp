/* date = March 16, 2025 5:07 PM */


#include "file.h"

#include <fstream>

namespace paganini {
    file::file() {
        file("/dev/null");
    }

    file::file(const std::string &fp) {
        file_handle.open(fp, std::ios::in | std::ios::out);
    }

    file::~file() {
        if (file_handle.is_open()) file_handle.close();
    }
} // paganini