/* date = May 01, 2025 2:03 PM */


#ifndef WAV_FILE_H
#define WAV_FILE_H
#include "io/file.h"

namespace paganini {

class wav_file final : public file {
public:
    explicit wav_file(const std::string &fp);
};

} // paganini

#endif //WAV_FILE_H
