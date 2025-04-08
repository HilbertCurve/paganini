/* date = March 29, 2025 9:43 PM */


#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include "common.h"

#include "core/resource.h"

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace paganini {

    constexpr uint32_t LAYOUT_COUNT = 4;

    constexpr uint32_t POSITION_COUNT = 3;
    constexpr uint32_t COLOR_COUNT = 4;
    constexpr uint32_t UV_COUNT = 2;
    constexpr uint32_t TEX_ID_COUNT = 1;
    constexpr uint32_t LAYOUT_SIZE = 40;

class vertex_buffer final : public resource {
public:
    struct vertex {
        glm::vec3 position{};
        glm::vec4 color{};
        glm::vec2 uv{};
        unsigned int tex_id{};
    };

    vertex_buffer();

    ~vertex_buffer() override;

    void put(const glm::vec3 &pos, const glm::vec4 &color, const glm::vec2 &uv, int tex_id);
    void put_n(vertex *vs, size_t length);

    void put_rect(const glm::vec3 &pos, const glm::vec2 &wh);
    void put_rect(const glm::vec3 &pos, const glm::vec2 &wh, const glm::vec4 &color);

    friend class renderer;

private:
    vertex *data = nullptr;
    uint32_t *indices = nullptr;

    uint32_t vert_count;
    uint32_t index_count;

    // opengl buffer ids
    GLuint vao{}, vbo{}, ebo{};

    bool dirty;
};

} // paganini

#endif //VERTEX_BUFFER_H
