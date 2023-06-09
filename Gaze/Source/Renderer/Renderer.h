#ifndef GAZE_ENGINE_RENDERER_H
#define GAZE_ENGINE_RENDERER_H

#include "RenderCommand.h"
#include "OrthographicCamera.h"
#include "Shader.h"

namespace Gaze {

    class Renderer {
    public:
        static void Init();

        static void Shutdown();

        static void OnWindowResize(uint32_t width, uint32_t height);

        static void BeginScene(OrthographicCamera &camera);

        static void EndScene();

        static void Submit(const Gaze::Ref<Shader> &shader, const Gaze::Ref<VertexArray> &vertexArray,
                           const glm::mat4 &transform = glm::mat4(1.0f));

        static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

    private:
        struct SceneData {
            glm::mat4 ViewProjectionMatrix;
        };

        static Scope <SceneData> s_SceneData;
    };

} // Gaze

#endif //GAZE_ENGINE_RENDERER_H
