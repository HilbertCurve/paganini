/* date = April 08, 2025 9:19 AM */


#include "input.h"

namespace paganini {
    void input::update(double) {
        auto &_inst = get();
        for (int key = 0; key < 256; key++) {
            _inst.up_keys.keys[key] = _inst.keys.keys[key];
        }

        _inst.mouse.scroll_x = 0;
        _inst.mouse.scroll_y = 0;
    }

    // TODO: mods
    void input::_key_callback(GLFWwindow *, int key, int, int action, int mods) {
        auto &_inst = get();
        if (action == GLFW_PRESS) {
            _inst.down_keys.keys[key] = !get().keys.keys[key];
            _inst.keys.keys[key] = true;
        } else if (action == GLFW_RELEASE) {
            _inst.up_keys.keys[key] = _inst.keys.keys[key];
            _inst.keys.keys[key] = false;
            _inst.down_keys.keys[key] = false;
        }
    }

    void input::_mouse_callback(GLFWwindow *, double xpos, double ypos) {
        auto &_inst = get();

        _inst.mouse.mouse_dx = xpos - _inst.mouse.mouse_x;
        _inst.mouse.mouse_dy = ypos - _inst.mouse.mouse_y;

        _inst.mouse.mouse_x = xpos;
        _inst.mouse.mouse_y = ypos;
    }

    void input::_scroll_callback(GLFWwindow *, double xoffset, double yoffset) {
        get().mouse.scroll_x = xoffset;
        get().mouse.scroll_y = yoffset;
    }

    input *input::_inst = nullptr;
} // paganini
