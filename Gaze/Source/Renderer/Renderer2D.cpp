#include "GazePCH.h"
#include "Renderer2D.h"

#include "VertexArray.h"
#include "Shader.h"
#include "RenderCommand.h"

namespace Gaze {

    struct Renderer2DStorage {
        Gaze::Ref<VertexArray> QuadVertexArray;
        Gaze::Ref<Shader> FlatColorShader;
    };

    static Renderer2DStorage *s_Data;

    void Renderer2D::Init() {
        s_Data = new Renderer2DStorage();
        s_Data->QuadVertexArray = VertexArray::Create();

        float squareVertices[5 * 4] = {
                -0.5f, -0.5f, 0.0f,
                0.5f, -0.5f, 0.0f,
                0.5f, 0.5f, 0.0f,
                -0.5f, 0.5f, 0.0f
        };

        Gaze::Ref<Gaze::VertexBuffer> squareVB;
        squareVB = Gaze::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
        squareVB->SetLayout({
                                    {Gaze::ShaderDataType::Float3, "a_Position"}
                            });
        s_Data->QuadVertexArray->AddVertexBuffer(squareVB);

        uint32_t squareIndices[6] = {0, 1, 2, 2, 3, 0};
        Gaze::Ref<Gaze::IndexBuffer> squareIB;
        squareIB = Gaze::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
        s_Data->QuadVertexArray->SetIndexBuffer(squareIB);

        s_Data->FlatColorShader = Gaze::Shader::Create(
                "C:/Users/hangh/Documents/GitHub/Gaze/Sandbox/Assets/Shaders/FlatColor.glsl");
    }

    void Renderer2D::Shutdown() {
        delete s_Data;
    }

    void Renderer2D::BeginScene(const OrthographicCamera &camera) {
        s_Data->FlatColorShader->Bind();
        s_Data->FlatColorShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
        s_Data->FlatColorShader->SetMat4("u_Transform", glm::mat4(1.0f));
    }

    void Renderer2D::EndScene() {

    }

    void Renderer2D::DrawQuad(const glm::vec2 &position, const glm::vec2 &size, const glm::vec4 &color) {
        DrawQuad({position.x, position.y, 0.0f}, size, color);
    }

    void Renderer2D::DrawQuad(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &color) {
        s_Data->FlatColorShader->Bind();
        s_Data->FlatColorShader->SetFloat4("u_Color", color);

        s_Data->QuadVertexArray->Bind();
        RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
    }
} // Gaze