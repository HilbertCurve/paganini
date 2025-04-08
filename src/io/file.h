/* date = March 16, 2025 5:07 PM */


#ifndef FILE_H
#define FILE_H
#include <fstream>

#include "core/resource.h"

namespace paganini {

class file final : public resource {
public:
    file();
    explicit file(const std::string &fp);
    ~file() override;

    std::string get_line();
    // more file stuff
private:
    std::fstream file_handle;
};

} // paganini

#endif //FILE_H
