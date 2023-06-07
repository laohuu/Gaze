#ifndef GAZE_ENGINE_IMGUILAYER_H
#define GAZE_ENGINE_IMGUILAYER_H

#include "Core/Layer.h"

#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"

namespace Gaze {
    class ImGuiLayer : public Layer {
    public:
        ImGuiLayer();

        ~ImGuiLayer() override = default;

        void OnAttach() override;

        void OnDetach() override;

        void OnEvent(Event &e) override;

        void Begin();

        void End();

        void BlockEvents(bool block) { m_BlockEvents = block; }

        void SetDarkThemeColors();

    private:
        bool m_BlockEvents = true;
    };
}

#endif //GAZE_ENGINE_IMGUILAYER_H
