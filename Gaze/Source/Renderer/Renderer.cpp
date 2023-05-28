#include "GazePCH.h"
#include "Renderer.h"

namespace Gaze {

    Renderer::SceneData *Renderer::s_SceneData = new Renderer::SceneData;

    void Renderer::BeginScene(OrthographicCamera &camera) {
        s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
    }

    void Renderer::EndScene() {
    }

    void Renderer::Submit(const Gaze::Ref<Shader> &shader, const Gaze::Ref<VertexArray> &vertexArray,
                          const glm::mat4 &transform
    ) {
        shader->Bind();
        shader->SetMat4("u_ViewProjection",
                        s_SceneData->ViewProjectionMatrix);
        shader->SetMat4("u_Transform", transform);

        vertexArray->Bind();

        RenderCommand::DrawIndexed(vertexArray);
    }
} // Gaze