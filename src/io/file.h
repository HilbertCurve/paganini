/* date = March 16, 2025 5:07 PM */


#ifndef FILE_H
#define FILE_H
#include <cstdint>
#include <fstream>
#include <vector>

#include "core/resource.h"

namespace paganini {

class file : public resource {
public:
    file();
    explicit file(const std::string &fp);
    file(const std::string &fp, bool is_binary);
    ~file() override;

    std::string get_line();

    enum seek_from {
        start = std::_Ios_Seekdir::_S_beg,
        current = std::_Ios_Seekdir::_S_cur,
        end = std::_Ios_Seekdir::_S_end,
    };

    long seek(long offset, seek_from whence);

    long tell();

    long dump(std::vector<char> &out);

    // This function upholds basic safety measures so long as T is a POD data type.
    // TODO: this could be subject to decent unit testing?
    template<typename T>
    requires std::is_pod_v<T>
    long read(T &buf) {
        return read(&buf, sizeof(T));
    }

    // more file stuff
protected:
    long read(void *buf, long len);

private:
    std::fstream file_handle;
    bool binary = false;
    std::string fp;
};

} // paganini

#endif //FILE_H
