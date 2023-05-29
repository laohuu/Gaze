#ifndef GAZE_ENGINE_RENDERCOMMAND_H
#define GAZE_ENGINE_RENDERCOMMAND_H

#include "RendererAPI.h"

namespace Gaze {

    class RenderCommand {
    public:
        inline static void Init() {
            s_RendererAPI->Init();
        }

        inline static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
            s_RendererAPI->SetViewport(x, y, width, height);
        }

        inline static void SetClearColor(const glm::vec4 &color) {
            s_RendererAPI->SetClearColor(color);
        }

        inline static void Clear() {
            s_RendererAPI->Clear();
        }

        inline static void DrawIndexed(const Gaze::Ref<VertexArray> &vertexArray) {
            s_RendererAPI->DrawIndexed(vertexArray);
        }

    private:
        static Scope<RendererAPI> s_RendererAPI;
    };

} // Gaze

#endif //GAZE_ENGINE_RENDERCOMMAND_H
