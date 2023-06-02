#ifndef GAZE_ENGINE_EDITORLAYER_H
#define GAZE_ENGINE_EDITORLAYER_H

#include "Gaze.h"

namespace Gaze {

    class EditorLayer : public Layer {
    public:
        EditorLayer();

        ~EditorLayer() override = default;

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

        bool m_ViewportFocused = false, m_ViewportHovered = false;
        glm::vec2 m_ViewportSize = {0.0f, 0.0f};

        glm::vec4 m_SquareColor = {0.2f, 0.3f, 0.8f, 1.0f};
    };
}


#endif //GAZE_ENGINE_EDITORLAYER_H
