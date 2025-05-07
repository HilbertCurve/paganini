/* date = March 15, 2025 9:13 PM */


#include "system.h"

#include <ranges>

#include "resource.h"

namespace paganini {
    system::~system() {
        resources.clear();
    }

    void system::add_resource(const std::string &name, resource *r) {
        this->resources.insert(std::make_pair(name, r));
    }

    void system::remove_resource(const std::string &name) {
        if (const auto it = resources.find(name); it != resources.end()) {
            delete it->second;
            resources.erase(it);
        }
    }
} // paganini