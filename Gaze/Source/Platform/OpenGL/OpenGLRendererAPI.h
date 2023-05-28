#ifndef GAZE_ENGINE_OPENGLRENDERERAPI_H
#define GAZE_ENGINE_OPENGLRENDERERAPI_H

#include "Renderer/RendererAPI.h"

namespace Gaze {

    class OpenGLRendererAPI : public RendererAPI {
    public:
        void SetClearColor(const glm::vec4 &color) override;

        void Clear() override;

        void DrawIndexed(const std::shared_ptr<VertexArray> &vertexArray) override;
    };

} // Gaze

#endif //GAZE_ENGINE_OPENGLRENDERERAPI_H