/* date = April 08, 2025 9:19 AM */


#ifndef INPUT_H
#define INPUT_H

#include <glm/vec2.hpp>

#include "common.h"
#include "core/system.h"

namespace paganini {

class input final : public system {
public:
    const input &operator=(const input &other) = delete;
    input &operator=(input &other) = delete;

    void start() override {}
    void update(double dt) override;
    void clean() override {}

    static input &get() {
        if (!_inst) _inst = new input();
        return *_inst;
    }

    class {
    public:
        [[nodiscard]] glm::vec2 pos() const {
            return {mouse_x, mouse_y};
        }
        [[nodiscard]] glm::vec2 dpos() const {
            return {mouse_dx, mouse_dy};
        }
        [[nodiscard]] double scroll() const {
            return scroll_y;
        }
        [[nodiscard]] glm::vec2 scroll_xy() const {
            return {scroll_x, scroll_y};
        }

    private:
        friend class input;

        double mouse_x{}, mouse_y{}, mouse_dx{}, mouse_dy{};
        double scroll_x{}, scroll_y{};
    } mouse;

    class {
    public:
        bool operator[](const uint32_t button) const {
            if (button >= 8) {
                _p_warning("Mouse button number %u doesn't exist.", button);
                return false;
            }
            return buttons[button];
        }
    private:
        friend class input;
        bool buttons[8] = {};
    } buttons;

    class {
    public:
        bool operator[](const uint32_t keycode) const {
            if (keycode >= 256) {
                _p_warning("Keycode number %u doesn't exist.", keycode);
                return false;
            }
            return keys[keycode];
        }
    private:
        friend class input;
        bool keys[256] = {};
    } keys;

    class {
    public:
        bool operator[](const uint32_t keycode) const {
            if (keycode >= 256) {
                _p_warning("Keycode number %u doesn't exist.", keycode);
                return false;
            }
            return keys[keycode];
        }
    private:
        friend class input;
        bool keys[256] = {};
    } down_keys;

    class {
    public:
        bool operator[](const uint32_t keycode) const {
            if (keycode >= 256) {
                _p_warning("Keycode number %u doesn't exist.", keycode);
                return false;
            }
            return keys[keycode];
        }
    private:
        friend class input;
        bool keys[256] = {};
    } up_keys;

private:
    friend class window;

    static void _key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void _mouse_callback(GLFWwindow* window, double xpos, double ypos);
    static void _scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

    input() = default;

    static input *_inst;
};

} // paganini

#endif //INPUT_H
