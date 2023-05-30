#ifndef GAZE_ENGINE_EXAMPLELAYER_H
#define GAZE_ENGINE_EXAMPLELAYER_H

#include "Gaze.h"

class ExampleLayer : public Gaze::Layer {
public:
    ExampleLayer();

    ~ExampleLayer() override = default;

    void OnAttach() override;

    void OnDetach() override;

    void OnUpdate(Gaze::Timestep ts) override;

    void OnImGuiRender() override;

    void OnEvent(Gaze::Event &event) override;

private:
    Gaze::ShaderLibrary m_ShaderLibrary;
    Gaze::Ref<Gaze::Shader> m_Shader;
    Gaze::Ref<Gaze::VertexArray> m_VertexArray;

    Gaze::Ref<Gaze::Shader> m_FlatColorShader;
    Gaze::Ref<Gaze::VertexArray> m_SquareVA;

    Gaze::Ref<Gaze::Texture2D> m_Texture, m_ChernoLogoTexture;

    Gaze::OrthographicCameraController m_CameraController;

    glm::vec3 m_SquareColor = {0.2f, 0.3f, 0.8f};
};


#endif //GAZE_ENGINE_EXAMPLELAYER_H
