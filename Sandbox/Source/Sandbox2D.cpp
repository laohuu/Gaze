
#include "Sandbox2D.h"

#include <imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Core/Timer.h"

Sandbox2D::Sandbox2D()
        : Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f) {
}

void Sandbox2D::OnAttach() {
    m_CheckerboardTexture = Gaze::Texture2D::Create(
            "C:/Users/hangh/Documents/GitHub/Gaze/Sandbox/Assets/Textures/Checkerboard.png");
}

void Sandbox2D::OnDetach() {
}

void Sandbox2D::OnUpdate(Gaze::Timestep ts) {



    // Update
    Gaze::Timer timer;
    m_CameraController.OnUpdate(ts);
    GZ_CORE_WARN("OnUpdate took {0} ms", timer.ElapsedMillis());

    // Render
    timer.Reset();
    Gaze::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
    Gaze::RenderCommand::Clear();

    Gaze::Renderer2D::BeginScene(m_CameraController.GetCamera());

    Gaze::Renderer2D::DrawQuad({-1.0f, 0.0f}, {0.8f, 0.8f}, {0.8f, 0.2f, 0.3f, 1.0f});
    Gaze::Renderer2D::DrawQuad({0.5f, -0.5f}, {0.5f, 0.75f}, {0.2f, 0.3f, 0.8f, 1.0f});
    Gaze::Renderer2D::DrawQuad({0.0f, 0.0f, -0.1f}, {1.0f, 1.0f}, m_CheckerboardTexture);

    Gaze::Renderer2D::EndScene();
    GZ_CORE_WARN("Render took {0} ms", timer.ElapsedMillis());
}

void Sandbox2D::OnImGuiRender() {
    ImGui::Begin("Settings");
    ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
    ImGui::End();
}

void Sandbox2D::OnEvent(Gaze::Event &e) {
    m_CameraController.OnEvent(e);
}