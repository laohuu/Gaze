#ifndef GAZE_ENGINE_SANDBOX2D_H
#define GAZE_ENGINE_SANDBOX2D_H

#include "Gaze.h"
#include "ParticleSystem.h"

class Sandbox2D : public Gaze::Layer {
public:
    Sandbox2D();

    virtual ~Sandbox2D() = default;

    void OnAttach() override;

    void OnDetach() override;

    void OnUpdate(Gaze::Timestep ts) override;

    void OnImGuiRender() override;

    void OnEvent(Gaze::Event &e) override;

private:
    Gaze::OrthographicCameraController m_CameraController;

    // Temp
    Gaze::Ref<Gaze::VertexArray> m_SquareVA;
    Gaze::Ref<Gaze::Shader> m_FlatColorShader;
    Gaze::Ref<Gaze::Framebuffer> m_Framebuffer;

    Gaze::Ref<Gaze::Texture2D> m_CheckerboardTexture;

    glm::vec4 m_SquareColor = {0.2f, 0.3f, 0.8f, 1.0f};

    ParticleProps m_Particle;
    ParticleSystem m_ParticleSystem;
};

#endif //GAZE_ENGINE_SANDBOX2D_H
