/* date = March 15, 2025 9:11 PM */

#include "renderer.h"

#include <cstring>

#include "common.h"

#include "vertex_buffer.h"
#include "window.h"
#include "core/app.h"

namespace paganini {
    void enable_attributes() {
        int offset = 0;
        _p_gl_call(glVertexAttribPointer, 0, POSITION_COUNT, GL_FLOAT, GL_FALSE, sizeof(vertex_buffer::vertex), reinterpret_cast<void *>(offset));
        offset += POSITION_COUNT * sizeof(float);
        _p_gl_call(glVertexAttribPointer, 1, COLOR_COUNT,    GL_FLOAT, GL_FALSE, sizeof(vertex_buffer::vertex), reinterpret_cast<void *>(offset));
        offset += COLOR_COUNT * sizeof(float);
        _p_gl_call(glVertexAttribPointer, 2, UV_COUNT,       GL_FLOAT, GL_FALSE, sizeof(vertex_buffer::vertex), reinterpret_cast<void *>(offset));
        offset += UV_COUNT * sizeof(float);
        _p_gl_call(glVertexAttribPointer, 3, TEX_ID_COUNT,   GL_INT,   GL_FALSE, sizeof(vertex_buffer::vertex), reinterpret_cast<void *>(offset));

        for (int i = 0; i < LAYOUT_COUNT; i++) {
            _p_gl_call(glEnableVertexAttribArray, i);
        }
    }

    void disable_attributes() {
        for (int i = 0; i < LAYOUT_COUNT; i++) {
            _p_gl_call(glDisableVertexAttribArray, i);
        }
    }

    const char *VERTEX_CODE =
            "#version 330 core\n"
            "layout (location=0) in vec3 v_pos;\n"
            "layout (location=1) in vec4 v_color;\n"
            "layout (location=2) in vec2 v_uv;\n"
            "layout (location=3) in int v_tex_id;\n"
            "\n"
            "out vec3 f_pos;\n"
            "out vec4 f_color;\n"
            "out vec2 f_uv;\n"
            "out int f_tex_id;\n"
            "\n"
            "void main()\n"
            "{\n"
            "    f_pos = v_pos;\n"
            "    f_color = v_color;\n"
            "    f_uv = v_uv;\n"
            "    f_tex_id = v_tex_id;\n"
            "    gl_Position = vec4(v_pos, 1.0);"
            "}";

    const char *FRAGMENT_CODE =
            "#version 330 core\n"
            "\n"
            "in vec3 f_pos;\n"
            "in vec4 f_color;\n"
            "in vec2 f_uv;\n"
            "flat in int tex_id;\n"
            "\n"
            "out vec4 color;\n"
            "\n"
            "void main()\n"
            "{\n"
            "    color = f_color;\n"
            "}";

    void renderer::start() {
        auto &b = *this->buffer;
        _p_gl_call(glGenBuffers, 1, &b.vbo)
        _p_gl_call(glGenBuffers, 1, &b.ebo)

        _p_gl_call(glGenVertexArrays, 1, &b.vao);

        _p_gl_call(glBindVertexArray, b.vao);

        vertex_id = _p_gl_eval(glCreateShader, GL_VERTEX_SHADER);
        fragment_id = _p_gl_eval(glCreateShader, GL_FRAGMENT_SHADER);

        // compile vertex shader code
        GLint result = GL_FALSE;
        int32_t log_length = 0;

        int vert_size = static_cast<int>(strlen(VERTEX_CODE));

        _p_gl_call(glShaderSource, vertex_id, 1, &VERTEX_CODE, &vert_size);
        _p_gl_call(glCompileShader, vertex_id);

        _p_gl_call(glGetShaderiv, vertex_id, GL_COMPILE_STATUS, &result);
        _p_gl_call(glGetShaderiv, vertex_id, GL_INFO_LOG_LENGTH, &log_length);

        if (log_length > 0) {
            char err_msg[log_length + 1];
            _p_gl_call(glGetShaderInfoLog, vertex_id, log_length, nullptr, &err_msg[0]);
            _p_warning("failure to compile vertex shader:\n%s", err_msg);
        }

        // compile fragment shader code
        result = GL_FALSE;
        log_length = 0;

        int frag_size = static_cast<int>(strlen(FRAGMENT_CODE));

        _p_gl_call(glShaderSource, fragment_id, 1, &FRAGMENT_CODE, &frag_size);
        _p_gl_call(glCompileShader, fragment_id);

        _p_gl_call(glGetShaderiv, fragment_id, GL_COMPILE_STATUS, &result);
        _p_gl_call(glGetShaderiv, fragment_id, GL_INFO_LOG_LENGTH, &log_length);

        if (log_length > 0) {
            char err_msg[log_length + 1];
            _p_gl_call(glGetShaderInfoLog, fragment_id, log_length, nullptr, &err_msg[0]);
            _p_warning("failure to compile fragment shader:\n%s", err_msg);
        }

        // link shader program
        result = GL_FALSE;
        log_length = 0;

        shader_id = _p_gl_eval(glCreateProgram);
        _p_gl_call(glAttachShader, shader_id, vertex_id);
        _p_gl_call(glAttachShader, shader_id, fragment_id);
        _p_gl_call(glLinkProgram, shader_id);

        _p_gl_call(glGetProgramiv, shader_id, GL_LINK_STATUS, &result);
        _p_gl_call(glGetProgramiv, shader_id, GL_INFO_LOG_LENGTH, &log_length);

        if (log_length > 0) {
            char err_msg[log_length + 1];
            _p_gl_call(glGetShaderInfoLog, shader_id, log_length, nullptr, &err_msg[0]);
            _p_warning("failure to link shaders:\n%s", err_msg);
        }

        // TODO:
        // create a window using glfw
        // create a rendering context using gl
        // make a vertex buffer (using custom vertex layouts would be goated)
        // render triangle
    }

    void renderer::update(double dt) {
        auto &w = *reinterpret_cast<window *>(resources["window"]);

        GLFWwindow *back = w.get_back();

        if (!glfwWindowShouldClose(back)) {
            _p_gl_call(glClearColor, 0.2f, 0.3f, 0.3f, 1.0f);
            _p_gl_call(glClear, GL_COLOR_BUFFER_BIT);

            buffer->put_rect({-0.8, -0.8, 0.0}, {1.6, 1.6}, {0.1f, 0.14f, 0.24f, 1.0f});

            buffer->put({-0.4, -0.4, 1.0}, {0.1f, 0.54f, 0.24f, 1.0f}, {0.0, 0.0}, 0);
            buffer->indices[buffer->index_count++] = buffer->vert_count - 1;
            buffer->put({-0.0, 0.4, 1.0}, {0.4f, 0.14f, 0.24f, 1.0f}, {0.0, 0.0}, 0);
            buffer->indices[buffer->index_count++] = buffer->vert_count - 1;
            buffer->put({0.4, -0.4, 1.0}, {0.9f, 0.14f, 0.24f, 1.0f}, {0.0, 0.0}, 0);
            buffer->indices[buffer->index_count++] = buffer->vert_count - 1;

            this->render();

            glfwSwapBuffers(back);
            glfwPollEvents();
        } else {
            app::get().close();
        }
    }


    void renderer::render() const {
        _p_gl_call(glBindBuffer, GL_ARRAY_BUFFER, this->buffer->vbo);
        _p_gl_call(glBufferData, GL_ARRAY_BUFFER, this->buffer->vert_count * LAYOUT_SIZE, this->buffer->data, GL_DYNAMIC_DRAW);
        _p_gl_call(glBindVertexArray, this->buffer->vao);
        _p_gl_call(glBindBuffer, GL_ELEMENT_ARRAY_BUFFER, this->buffer->ebo);
        _p_gl_call(
            glBufferData,
            GL_ELEMENT_ARRAY_BUFFER,
            this->buffer->index_count * sizeof(uint32_t),
            this->buffer->indices,
            GL_DYNAMIC_DRAW
        );

        _p_gl_call(glUseProgram, shader_id);

        _p_gl_call(glBindVertexArray, this->buffer->vao);
        enable_attributes();

        _p_gl_call(glDrawElements, GL_TRIANGLES, this->buffer->index_count, GL_UNSIGNED_INT, nullptr);

        disable_attributes();
        _p_gl_call(glBindVertexArray, 0);

        this->buffer->vert_count = 0;
        this->buffer->index_count = 0;

        _p_gl_call(glUseProgram, 0);
    }

    void renderer::clean() {
        glfwTerminate();
    }

    renderer::renderer(): system() {
        if (!glfwInit()) {
            app::register_error("Could not initialize GLFW library.", __FILE__, __LINE__);
        }
        add_resource("window", new window());
        if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
            app::register_error("Could not initialize GLAD OpenGL library.", __FILE__, __LINE__);
        }

        auto *w = reinterpret_cast<window *>(this->resources["window"]);
        glfwSetFramebufferSizeCallback(w->get_back(), [](GLFWwindow *, int width, int height) {
            _p_gl_call(glViewport, 0, 0, width, height);
        });

        this->add_resource("vb", new vertex_buffer());
        buffer = reinterpret_cast<vertex_buffer *>(this->resources["vb"]);
    }

    renderer::~renderer() {
        glfwTerminate();
    }
} // paganini
