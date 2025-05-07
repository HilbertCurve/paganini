/* date = March 15, 2025 9:13 PM */


#ifndef SYSTEM_H
#define SYSTEM_H
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "entity.h"

namespace paganini {
    class entity;
    class resource;

    class system {
    public:
        virtual ~system();

        virtual void start() = 0;

        virtual void update(double dt) = 0;

        virtual void clean() = 0;

        /**
         * Registers a resource with this system. Full ownership of this resource is assumed here.
         *
         * @param name
         * @param r A pointer to the resource. Note that freeing of this resource is handled in-class.
         */
        void add_resource(const std::string &name, resource *r);
        void remove_resource(const std::string &name);

    protected:
        std::unordered_map<std::string, resource *> resources;
        // note: this is a view into the entities of the application
        std::unordered_set<entity *> *entities = nullptr;
        friend class app;
    };
} // paganini

#endif //SYSTEM_H
