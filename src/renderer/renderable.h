/* date = May 01, 2025 1:04 PM */


#ifndef RENDERABLE_H
#define RENDERABLE_H
#include "core/component.h"

namespace paganini {
    class vertex_buffer;

    class renderable : public component {
public:
    virtual void fill_buffer(vertex_buffer &buffer) = 0;
};

} // paganini

#endif //RENDERABLE_H
