/* date = March 15, 2025 10:24 PM */


#include "app.h"

#include <iostream>

#include "system.h"

#include "renderer/renderer.h"

namespace paganini {
    void app::init() {
        for (auto *s : systems)
            s->start();
    }

    void app::run() {
        double t0 = 0.0, t1 = 0.0;
        t0 = glfwGetTime();
        double dt = t0;
        while (!this->closing) {
            t0 = glfwGetTime();

            for (const auto& s : systems) {
                s->update(dt);
            }

            t1 = glfwGetTime();
            dt = t1 - t0;
            this->dt = dt;
        }
        this->clean();
    }

    void app::close() {
        this->closing = true;
    }

    void app::register_error(const char *str, const char *file, const int line) {
        std::cout << "ERROR: received in " << file << ":" << line
                << str << '\n';
    }

    app *_inst = nullptr;

    app & app::get() {
        if (!_inst) {
            _inst = new app();
        }
        return *_inst;
    }

    void app::clean() {
        for (auto *s : systems) {
            delete s;
        }
        systems.clear();
    }

    app::app() {
        // start up the app with baseline systems
        systems.push_back(new renderer());
    }

    app *app::_inst = nullptr;
} // paganini