
#include "Sandbox2D.h"

#include "imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

Sandbox2D::Sandbox2D()
        : Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f) {
}

void Sandbox2D::OnAttach() {

}

void Sandbox2D::OnDetach() {
}

void Sandbox2D::OnUpdate(Gaze::Timestep ts) {
    // Update
    m_CameraController.OnUpdate(ts);

    // Render
    Gaze::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
    Gaze::RenderCommand::Clear();

    Gaze::Renderer2D::BeginScene(m_CameraController.GetCamera());

    Gaze::Renderer2D::DrawQuad({0.0f, 0.0f}, {1.0f, 1.0f}, {0.8f, 0.2f, 0.3f, 1.0f});

    Gaze::Renderer2D::EndScene();

//    m_FlatColorShader->Bind();
//    m_FlatColorShader->SetFloat4("u_Color", m_SquareColor);

}

void Sandbox2D::OnImGuiRender() {
    ImGui::Begin("Settings");
    ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
    ImGui::End();
}

void Sandbox2D::OnEvent(Gaze::Event &e) {
    m_CameraController.OnEvent(e);
}