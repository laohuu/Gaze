#ifndef GAZE_ENGINE_RENDERER_H
#define GAZE_ENGINE_RENDERER_H

namespace Gaze {

    enum class RendererAPI {
        None = 0, OpenGL = 1
    };

    class Renderer {
    public:
        inline static RendererAPI GetAPI() { return s_RendererAPI; }

    private:
        static RendererAPI s_RendererAPI;
    };

} // Gaze

#endif //GAZE_ENGINE_RENDERER_H
