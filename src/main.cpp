#include <iostream>

#include "core/app.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    auto &a = paganini::app::get();
    a.init();
    a.run();
}
