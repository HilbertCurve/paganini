/* date = May 01, 2025 12:26 PM */


#ifndef SOUND_BOARD_H
#define SOUND_BOARD_H
#include "core/system.h"

namespace paganini {

class sound_board final : public system {
public:
    static void list_devices();

    void start() override;

    void update(double dt) override {};

    void clean() override;

private:
    ALCdevice *device = nullptr;
    ALCcontext * context = nullptr;
};

} // paganini

#endif //SOUND_BOARD_H
