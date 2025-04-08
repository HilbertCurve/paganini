/* date = March 15, 2025 10:14 PM */


#ifndef COMPONENT_H
#define COMPONENT_H

namespace paganini {

class component {
public:
    virtual ~component() = default;

    virtual void start() = 0;
    virtual void update(double dt) = 0;
    virtual void stop() = 0;
};

} // paganini

#endif //COMPONENT_H
