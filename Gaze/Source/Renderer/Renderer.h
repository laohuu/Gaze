#ifndef GAZE_ENGINE_RENDERER_H
#define GAZE_ENGINE_RENDERER_H

#include "RenderCommand.h"

namespace Gaze {

    class Renderer {
    public:
        static void BeginScene();

        static void EndScene();

        static void Submit(const std::shared_ptr<VertexArray> &vertexArray);

        inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
    };

} // Gaze

#endif //GAZE_ENGINE_RENDERER_H
