/* date = April 06, 2025 4:14 PM */


#ifndef COMMON_H
#define COMMON_H

#include <cstdio>
#include <cstdlib>
#include <cstddef>
#include <cstdint>

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#define _p_error(message, ...) \
{\
fprintf(stderr, "\x1B[01m\x1B[31mERROR:\x1B[0m ");\
fprintf(stderr, message __VA_OPT__(,) __VA_ARGS__);\
fprintf(stderr, "\n");\
exit(-1);\
}

#define _p_warning(message, ...) \
{\
fprintf(stdout, "\x1B[01m\x1B[31mWARNING:\x1B[0m ");\
fprintf(stdout, message __VA_OPT__(,) __VA_ARGS__);\
fprintf(stdout, "\n");\
}

#define _p_message(message, ...) \
{\
printf("\x1B[01m\x1B[32mINFO:\x1B[0m ");\
printf(message __VA_OPT__(,) __VA_ARGS__);\
printf("\n");\
}

#define _p_assert(x, reason, ...) \
if (!(x))\
{\
fprintf(stderr, "\x1B[01m\x1B[31mERROR: Assertion failed at file %s, line %d:\x1B[0m ",\
__FILE__, __LINE__);\
fprintf(stderr, reason __VA_OPT__(,) __VA_ARGS__);\
fprintf(stderr, "\n");\
exit(-1);\
}

#endif //COMMON_H
