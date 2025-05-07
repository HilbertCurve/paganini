/* date = May 01, 2025 2:03 PM */


#include "wav_file.h"

#include "common.h"

namespace paganini {
    wav_file::wav_file(const std::string &fp) : file(fp) {
        // TODO: replace with recoverable errors.
        char header[4];
        _p_assert(read<char[4]>(header) == 4, "WAV File Error: Couldn't read RIFF header.");

    }
} // paganini