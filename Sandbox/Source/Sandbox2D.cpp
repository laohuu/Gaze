
#include "Sandbox2D.h"

#include <imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Core/Timer.h"

Sandbox2D::Sandbox2D()
        : Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f) {
}

void Sandbox2D::OnAttach() {
    GZ_PROFILE_FUNCTION();

    m_CheckerboardTexture = Gaze::Texture2D::Create(
            "C:/Users/hangh/Documents/GitHub/Gaze/Sandbox/Assets/Textures/Checkerboard.png");
}

void Sandbox2D::OnDetach() {
    GZ_PROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate(Gaze::Timestep ts) {

    GZ_PROFILE_FUNCTION();

    // Update
    m_CameraController.OnUpdate(ts);


    // Render
    Gaze::Renderer2D::ResetStats();

    {
        GZ_PROFILE_SCOPE("Renderer Prep");
        Gaze::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
        Gaze::RenderCommand::Clear();
    }

    {
        GZ_PROFILE_SCOPE("Renderer Draw");

        static float rotation = 0.0f;
        rotation += ts * 50.0f;

        Gaze::Renderer2D::BeginScene(m_CameraController.GetCamera());

        Gaze::Renderer2D::DrawRotatedQuad({1.0f, 0.0f}, {0.8f, 0.8f}, -45.0f, {0.8f, 0.2f, 0.3f, 1.0f});
        Gaze::Renderer2D::DrawQuad({-1.0f, 0.0f}, {0.8f, 0.8f}, {0.8f, 0.2f, 0.3f, 1.0f});
        Gaze::Renderer2D::DrawQuad({0.5f, -0.5f}, {0.5f, 0.75f}, {0.2f, 0.3f, 0.8f, 1.0f});
        Gaze::Renderer2D::DrawQuad({0.0f, 0.0f, -0.1f}, {20.0f, 20.0f}, m_CheckerboardTexture, 10.0f);
        Gaze::Renderer2D::DrawRotatedQuad({-2.0f, 0.0f, 0.0f}, {1.0f, 1.0f}, rotation, m_CheckerboardTexture, 20.0f);

        Gaze::Renderer2D::EndScene();

        Gaze::Renderer2D::BeginScene(m_CameraController.GetCamera());
        for (float y = -5.0f; y < 5.0f; y += 0.5f) {
            for (float x = -5.0f; x < 5.0f; x += 0.5f) {
                glm::vec4 color = {(x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.7f};
                Gaze::Renderer2D::DrawQuad({x, y}, {0.45f, 0.45f}, color);
            }
        }
        Gaze::Renderer2D::EndScene();
    }

}

void Sandbox2D::OnImGuiRender() {
    GZ_PROFILE_FUNCTION();

    ImGui::Begin("Settings");

    auto stats = Gaze::Renderer2D::GetStats();
    ImGui::Text("Renderer2D Stats:");
    ImGui::Text("Draw Calls: %d", stats.DrawCalls);
    ImGui::Text("Quads: %d", stats.QuadCount);
    ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
    ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

    ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
    ImGui::End();
}

void Sandbox2D::OnEvent(Gaze::Event &e) {
    m_CameraController.OnEvent(e);
}