#ifndef GAZE_ENGINE_RENDERERAPI_H
#define GAZE_ENGINE_RENDERERAPI_H

#include "glm/glm.hpp"
#include "VertexArray.h"

namespace Gaze {

    class RendererAPI {
    public:
        enum class API {
            None = 0, OpenGL = 1
        };

    public:
        virtual void SetClearColor(const glm::vec4 &color) = 0;

        virtual void Clear() = 0;

        virtual void DrawIndexed(const std::shared_ptr<VertexArray> &vertexArray) = 0;

        inline static API GetAPI() { return s_API; }

    public:
        static API s_API;

    };

} // Gaze

#endif //GAZE_ENGINE_RENDERERAPI_H
