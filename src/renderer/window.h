/* date = March 16, 2025 4:38 PM */


#ifndef WINDOW_H
#define WINDOW_H
#include <cstdint>

#include "core/resource.h"

struct GLFWwindow;

namespace paganini {

class window final : public resource {
public:
    window();
    ~window() override;

    GLFWwindow *get_back() {
        return back;
    }

private:
    GLFWwindow *back{};

    const uint32_t DEFAULT_WIDTH = 800, DEFAULT_HEIGHT = 600;
    uint32_t width, height;

    const char *DEFAULT_NAME = "Paganini";
    std::string name;
};

} // paganini

#endif //WINDOW_H
