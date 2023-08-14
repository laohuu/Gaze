#ifndef GAZE_ENGINE_RENDERERAPI_H
#define GAZE_ENGINE_RENDERERAPI_H

#include "VertexArray.h"

#include "Scene/Scene.h"

#include "RendererCapabilities.h"
#include "RendererTypes.h"

#include <glm/glm.hpp>

namespace Gaze
{
    enum class PrimitiveType
    {
        None = 0,
        Triangles,
        Lines
    };

    enum class RendererAPIType
    {
        None   = 0,
        OpenGL = 1
    };

    using RendererID = uint32_t;

    class RendererAPI
    {
    public:
        virtual ~RendererAPI() = default;

        virtual void Init() = 0;

        virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;

        virtual void SetClearColor(const glm::vec4& color) = 0;

        virtual void Clear() = 0;

        virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0) = 0;

        virtual void DrawLines(const Ref<VertexArray>& vertexArray, uint32_t vertexCount) = 0;

        virtual void SetLineWidth(float width) = 0;

        static Scope<RendererAPI> Create();

        virtual RendererCapabilities& GetCapabilities() = 0;

        static RendererAPIType Current() { return s_CurrentRendererAPI; }

    private:
        static RendererAPIType s_CurrentRendererAPI;
    };

} // namespace Gaze

#endif // GAZE_ENGINE_RENDERERAPI_H
