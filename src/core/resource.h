/* date = March 15, 2025 10:19 PM */


#ifndef RESOURCE_H
#define RESOURCE_H
#include <string>

namespace paganini {

class resource {
public:
    virtual ~resource() = default;

    [[nodiscard]] const std::string &get_name() const { return name; }
    void set_name(const std::string &n) { name = n; }

protected:
    std::string name{};
};

} // paganini

#endif //RESOURCE_H
