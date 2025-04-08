/* date = March 29, 2025 9:43 PM */


#include "vertex_buffer.h"

#include "common.h"

namespace paganini {
    // note: the layout is like this:
    // pos: 2 floats, 0 offset
    // color: 4 floats, 8 offset
    // uvs: 2 floats, 24 offset
    // texid: 1 int, 32 offset
    // full length: 36 bytes

    vertex_buffer::vertex_buffer() {
        data = new vertex[1000];
        indices = new uint32_t[1000];
        vert_count = 0;
        // note: byte count = vert_count * 36

        index_count = 0;
        // note: primitive count is index count / 3
        dirty = false;
    }

    vertex_buffer::~vertex_buffer() {
        delete data;
    }

    void vertex_buffer::put(const glm::vec3 &pos, const glm::vec4 &color, const glm::vec2 &uv, int tex_id) {
        this->data[vert_count].position = pos;
        this->data[vert_count].color = color;
        this->data[vert_count].uv = uv;
        this->data[vert_count].tex_id = tex_id;
        vert_count++;
    }

    void vertex_buffer::put_n(vertex *vs, size_t length) {
        for (int i = 0; i < length; i++) {
            this->data[vert_count++] = vs[i];
        }
    }

    void vertex_buffer::put_rect(const glm::vec3 & pos, const glm::vec2 &wh) {
        this->put_rect(pos, wh, {1.0, 1.0, 1.0, 1.0});
    }

    void vertex_buffer::put_rect(const glm::vec3 & pos, const glm::vec2 &wh, const glm::vec4 &color) {
        glm::vec3 verts[4] = {
            pos + glm::vec3(wh.x, 0.0, 0.0),
            pos,
            pos + glm::vec3(0.0, wh.y, 0.0),
            pos + glm::vec3(wh, 0.0),
        };

        for (auto & vert : verts) {
            this->data[vert_count++] = {
                vert,
                color,
                glm::vec2(0.0),
                0
            };
        }

        this->indices[index_count + 0] = 3;
        this->indices[index_count + 1] = 2;
        this->indices[index_count + 2] = 0;

        this->indices[index_count + 3] = 0;
        this->indices[index_count + 4] = 2;
        this->indices[index_count + 5] = 1;

        index_count += 6;
    }
} // paganini