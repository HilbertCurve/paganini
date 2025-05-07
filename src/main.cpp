#include <iostream>

#include "core/app.h"
#include "renderer/renderable.h"
#include "renderer/vertex_buffer.h"

class debug_renderable : public paganini::renderable {
public:
    void start() override {}

    void update(double dt) override {}

    void stop() override {}

    void fill_buffer(paganini::vertex_buffer &buffer) override {
        buffer.put_rect({0.0, 0.0, 0.0}, {10.0, 10.0});
    }
};

class debug_rect : public paganini::entity {
    void start() override {
        this->components.push_back(new debug_renderable());
    }
};

int main() {
    std::cout << "Hello, World!" << std::endl;

    auto &a = paganini::app::get();
    a.init();

    a.add(new debug_rect());

    a.run();
}
