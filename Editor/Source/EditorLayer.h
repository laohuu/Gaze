#ifndef GAZE_ENGINE_EDITORLAYER_H
#define GAZE_ENGINE_EDITORLAYER_H

#include "Gaze.h"
#include "Panels/SceneHierarchyPanel.h"
#include "Panels/ContentBrowserPanel.h"
#include "Renderer/EditorCamera.h"

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

        void OnScenePlay();

        void OnSceneStop();

        // UI Panels
        void UI_Toolbar();

    private:
        bool OnKeyPressed(KeyPressedEvent &e);

        bool OnMouseButtonPressed(MouseButtonPressedEvent &e);

        void NewScene();

        void OpenScene();

        void OpenScene(const std::filesystem::path &path);

        void SaveSceneAs();

    private:
        Gaze::OrthographicCameraController m_CameraController;

        // Temp
        Gaze::Ref<Gaze::VertexArray> m_SquareVA;
        Gaze::Ref<Gaze::Shader> m_FlatColorShader;
        Gaze::Ref<Gaze::Framebuffer> m_Framebuffer;

        Gaze::Ref<Scene> m_ActiveScene;
        Entity m_SquareEntity;
        Entity m_CameraEntity;
        Entity m_SecondCamera;

        Entity m_HoveredEntity;

        bool m_PrimaryCamera = true;

        Gaze::Ref<Gaze::Texture2D> m_CheckerboardTexture;

        bool m_ViewportFocused = false, m_ViewportHovered = false;
        glm::vec2 m_ViewportSize = {0.0f, 0.0f};
        glm::vec2 m_ViewportBounds[2];

        glm::vec4 m_SquareColor = {0.2f, 0.3f, 0.8f, 1.0f};

        int m_GizmoType = -1;

        EditorCamera m_EditorCamera;

        enum class SceneState {
            Edit = 0, Play = 1, Simulate = 2
        };
        SceneState m_SceneState = SceneState::Edit;

        // Panels
        SceneHierarchyPanel m_SceneHierarchyPanel;
        ContentBrowserPanel m_ContentBrowserPanel;

        // Editor resources
        Gaze::Ref<Gaze::Texture2D> m_IconPlay, m_IconStop;
    };
}


#endif //GAZE_ENGINE_EDITORLAYER_H
