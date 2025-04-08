/* date = March 15, 2025 9:13 PM */


#ifndef SYSTEM_H
#define SYSTEM_H
#include <memory>
#include <unordered_map>
#include <vector>

namespace paganini {
    class entity;
    class resource;

    class system {
public:
    virtual ~system() = default;

    virtual void start() = 0;
    virtual void update(double dt) = 0;
    virtual void clean() = 0;

    /**
     * Registers a resource with this system. Full ownership of this resource is assumed here.
     *
     * @param name
     * @param r An r-value of a resource. Create one using std::move(your_resource).
     */
    void add_resource(const std::string &name, resource *r);

protected:
    std::unordered_map<std::string, resource *> resources;
    std::vector<entity *> entities;
};

} // paganini

#endif //SYSTEM_H
