#ifndef GAZE_ENGINE_RENDERCOMMAND_H
#define GAZE_ENGINE_RENDERCOMMAND_H

#include "RendererAPI.h"

namespace Gaze {

    class RenderCommand {
    public:
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
        static RendererAPI *s_RendererAPI;
    };

} // Gaze

#endif //GAZE_ENGINE_RENDERCOMMAND_H
