cmake_minimum_required(VERSION 3.30)
project(paganini)

set(CMAKE_CXX_STANDARD 20)

add_executable(paganini
        vendor/glad/src/glad.c
        vendor/glad/include/glad/glad.h

        src/main.cpp
        src/renderer/renderer.cpp
        src/renderer/renderer.h
        src/core/system.cpp
        src/core/system.h
        src/core/entity.cpp
        src/core/entity.h
        src/core/component.cpp
        src/core/component.h
        src/core/resource.cpp
        src/core/resource.h
        src/core/app.cpp
        src/core/app.h
        src/renderer/window.cpp
        src/renderer/window.h
        src/io/file.cpp
        src/io/file.h
        src/renderer/vertex_buffer.cpp
        src/renderer/vertex_buffer.h
        src/common.h
)

include(FetchContent)

FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG bf71a834948186f4097caa076cd2663c69a10e1e
)

FetchContent_MakeAvailable(glm)

find_package(glfw3 REQUIRED)

target_include_directories(paganini PRIVATE src vendor/glad/include)
target_link_libraries(paganini PRIVATE glfw3 glm::glm)
