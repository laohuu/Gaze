#include "GazePCH.h"

#include "Renderer.h"
#include "Renderer2D.h"

namespace Gaze
{
    Scope<Renderer::SceneData> Renderer::s_SceneData = CreateScope<Renderer::SceneData>();
    static RendererAPI*        s_RendererAPI         = nullptr;

    struct RendererData
    {
        Ref<ShaderLibrary> m_ShaderLibrary;

        Ref<Texture2D>   WhiteTexture;
        Ref<TextureCube> BlackCubeTexture;
    };

    static RendererData* s_Data = nullptr;

    void Renderer::Init()
    {
        GZ_PROFILE_FUNCTION();

        s_Data = new RendererData();

        RenderCommand::Init();
        Renderer2D::Init();
    }

    void Renderer::Shutdown() { Renderer2D::Shutdown(); }

    RendererCapabilities& Renderer::GetCapabilities() { return s_RendererAPI->GetCapabilities(); }

    Ref<ShaderLibrary> Renderer::GetShaderLibrary() { return s_Data->m_ShaderLibrary; }

    void Renderer::OnWindowResize(uint32_t width, uint32_t height) { RenderCommand::SetViewport(0, 0, width, height); }

    void Renderer::BeginScene(OrthographicCamera& camera)
    {
        s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
    }

    void Renderer::EndScene() {}

    void Renderer::Submit(Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform)
    {
        shader->Bind();
        shader->SetMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
        shader->SetMat4("u_Transform", transform);

        vertexArray->Bind();

        RenderCommand::DrawIndexed(vertexArray);
    }

    Ref<Texture2D> Renderer::GetWhiteTexture() { return s_Data->WhiteTexture; }

    Ref<TextureCube> Renderer::GetBlackCubeTexture() { return s_Data->BlackCubeTexture; }
} // namespace Gaze