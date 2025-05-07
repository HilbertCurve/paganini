/* date = May 01, 2025 12:26 PM */

#include <al.h>
#include <alc.h>

#include "sound_board.h"

#include <cstring>
#include <iostream>

#include "common.h"

// tutorials that have helped:
// https://moderncprogramming.com/programming-with-openal-in-pure-c-how-to-start/
//

namespace paganini {
    void sound_board::list_devices() {
        auto *devices = alcGetString(nullptr, ALC_DEVICE_SPECIFIER);
        const ALCchar *device = devices;

        _p_message("ALC Devices:")
        while (device && *device != 0) {
            std::cout << device << '\n';
            device += strlen(device) + 1;
        }
    }

    void sound_board::start() {
        // ALboolean enumeration;

        device = alcOpenDevice(nullptr);
        if (!device) {
            _p_error("OpenAL could not open device!");
        }

        if (!alcIsExtensionPresent(nullptr, "ALC_ENUMERATION_EXT")) {
            _p_warning("Note: device enumeration not enabled.");
        } else {
            list_devices();
        }

        context = alcCreateContext(device, nullptr);
        if (!alcMakeContextCurrent(context)) {
            _p_error("Could not make OpenAL context current!");
        }
    }

    void sound_board::clean() {
        // TODO
    }
} // paganini