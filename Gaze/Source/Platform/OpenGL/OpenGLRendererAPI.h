#ifndef GAZE_ENGINE_OPENGLRENDERERAPI_H
#define GAZE_ENGINE_OPENGLRENDERERAPI_H

#include "Renderer/RendererAPI.h"

namespace Gaze
{

    class OpenGLRendererAPI : public RendererAPI
    {
    public:
        void Init() override;

        void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;

        void SetClearColor(const glm::vec4& color) override;

        void Clear() override;

        void DrawIndexed(const Gaze::Ref<VertexArray>& vertexArray, uint32_t indexCount) override;

        void DrawLines(const Gaze::Ref<VertexArray>& vertexArray, uint32_t vertexCount) override;

        void SetLineWidth(float width) override;

         RendererCapabilities& GetCapabilities() override;
    };

} // namespace Gaze

#endif // GAZE_ENGINE_OPENGLRENDERERAPI_H
