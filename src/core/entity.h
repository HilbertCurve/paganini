/* date = March 15, 2025 10:06 PM */


#ifndef ENTITY_H
#define ENTITY_H
#include <memory>
#include <vector>

namespace paganini {

class component;

class entity {
public:
    virtual ~entity() = default;

    virtual void start() = 0;
    virtual void update(double dt);
    virtual void stop();

protected:
    std::vector<component *> components{};
    std::string name;
};

} // paganini

#endif //ENTITY_H
