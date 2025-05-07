/* date = March 15, 2025 10:06 PM */


#ifndef ENTITY_H
#define ENTITY_H
#include <memory>
#include <vector>

#include "common.h"

namespace paganini {
    class component;

    class entity {
    public:
        virtual ~entity() = default;

        virtual void start() = 0;

        virtual void update(double dt);

        virtual void stop();

        template<typename T>
        T *get() {
            for (auto *c : components) {
                T *casted = dynamic_cast<T *>(c);
                if (!casted) continue;
                return casted;
            }

            return nullptr;
        }

    protected:
        std::vector<component *> components{};
        std::string name;
    };
} // paganini

#endif //ENTITY_H
