/* date = March 15, 2025 10:06 PM */

#include "entity.h"
#include "component.h"

namespace paganini {
    void entity::update(const double dt) {
        for (component *c : components) {
            c->update(dt);
        }
    }

    void entity::stop() {
        for (component *c : components) {
            c->stop();
            delete c;
        }
        components.clear();
    }
} // paganini