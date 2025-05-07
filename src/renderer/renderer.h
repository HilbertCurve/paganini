/* date = March 15, 2025 9:11 PM */


#ifndef RENDERER_H
#define RENDERER_H

#include "vertex_buffer.h"
#include "core/system.h"

#ifndef _p_gl_call
#define _p_gl_call(func, args...)\
{\
    glGetError();\
    func(args);\
    if (glGetError() != 0)\
        printf("GL Error with function %s at %s:%d \n", #func, __FILE__, __LINE__);\
}
#define _p_gl_call_paganini_defined
#endif

#ifndef _p_gl_eval
#define _p_gl_eval(func, args...)\
({\
    glGetError();\
    auto val = func(args);\
    if (glGetError() != 0)\
        printf("GL Error received calling function %s: \n", #func);\
    val;\
})
#define _p_gl_call_paganini_defined
#endif

namespace paganini {
    class renderer final : public system {
    public:
        renderer();

        ~renderer() override;

        void start() override;

        void update(double dt) override;

        void render() const;

        void clean() override;

        vertex_buffer *buffer;

    private:
        static renderer *_inst;

        // opengl shader ids
        GLuint vertex_id{}, fragment_id{}, shader_id{};
    };
} // paganini

#endif //RENDERER_H
