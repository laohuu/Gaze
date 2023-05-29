
#include "Sandbox2D.h"

#include "imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

Sandbox2D::Sandbox2D()
        : Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f) {
}

void Sandbox2D::OnAttach() {
    m_SquareVA = Gaze::VertexArray::Create();

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
    m_SquareVA->AddVertexBuffer(squareVB);

    uint32_t squareIndices[6] = {0, 1, 2, 2, 3, 0};
    Gaze::Ref<Gaze::IndexBuffer> squareIB;
    squareIB = Gaze::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
    m_SquareVA->SetIndexBuffer(squareIB);

    m_FlatColorShader = Gaze::Shader::Create(
            "C:/Users/hangh/Documents/GitHub/Gaze/Sandbox/Assets/Shaders/FlatColor.glsl");
}

void Sandbox2D::OnDetach() {
}

void Sandbox2D::OnUpdate(Gaze::Timestep ts) {
    // Update
    m_CameraController.OnUpdate(ts);

    // Render
    Gaze::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
    Gaze::RenderCommand::Clear();

    Gaze::Renderer::BeginScene(m_CameraController.GetCamera());

    m_FlatColorShader->Bind();
    m_FlatColorShader->SetFloat4("u_Color", m_SquareColor);

    Gaze::Renderer::Submit(m_FlatColorShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

    Gaze::Renderer::EndScene();
}

void Sandbox2D::OnImGuiRender() {
    ImGui::Begin("Settings");
    ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
    ImGui::End();
}

void Sandbox2D::OnEvent(Gaze::Event &e) {
    m_CameraController.OnEvent(e);
}