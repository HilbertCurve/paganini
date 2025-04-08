/* date = March 15, 2025 9:13 PM */


#include "system.h"
#include "resource.h"

namespace paganini {
    void system::add_resource(const std::string &name, resource *r) {
        this->resources.insert(std::make_pair(name, r));
    }
} // paganini