/* date = March 16, 2025 4:38 PM */


#include "window.h"

#include "common.h"

#include "core/app.h"
#include "io/input.h"

namespace paganini {
    window::window() {
        this->width = DEFAULT_WIDTH;
        this->height = DEFAULT_HEIGHT;
        this->name = std::string(DEFAULT_NAME);
        back = glfwCreateWindow(
            static_cast<int>(width),
            static_cast<int>(height),
            name.c_str(), nullptr, nullptr
        );

        if (!back) {
            app::register_error("Could not initialize GLFW window.", __FILE__, __LINE__);
        }

        glfwMakeContextCurrent(back);

        glfwSetKeyCallback(back, input::_key_callback);
        glfwSetCursorPosCallback(back, input::_mouse_callback);
        glfwSetScrollCallback(back, input::_scroll_callback);
    }

    window::~window() {
        if (!glfwWindowShouldClose(this->back)) glfwSetWindowShouldClose(this->back, true);
        glfwDestroyWindow(this->back);
    }
} // paganini