/* date = March 15, 2025 10:24 PM */


#ifndef APP_H
#define APP_H
#include <memory>
#include <unordered_set>
#include <vector>

#include "system.h"

namespace paganini {

class app final {
public:
    void init();
    void run();
    void close();

    void add(entity *e) {
        entities.insert(e);
        e->start();
    }

    static void register_error(const char *str, const char *file, int line);

    static app &get();

    [[nodiscard]] double get_dt() const { return dt; }

private:
    void clean();
    app();

    // I am defeated
    std::vector<system *> systems;
    std::unordered_set<entity *> entities;
    bool closing = false;
    double dt{};
    // file log_file;

    // to make this thing a singleton
    static app *_inst;
};

} // paganini

#endif //APP_H
