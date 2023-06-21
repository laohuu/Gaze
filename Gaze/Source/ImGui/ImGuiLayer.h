#ifndef GAZE_ENGINE_IMGUI_IMGUILAYER_H
#define GAZE_ENGINE_IMGUI_IMGUILAYER_H

#include "Core/Layer.h"

#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"

namespace Gaze
{

    class ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer() override = default;

        void OnAttach() override;
        void OnDetach() override;
        void OnEvent(Event& e) override;

        void Begin();
        void End();

        void BlockEvents(bool block) { m_BlockEvents = block; }

        void SetDarkThemeColors();

        static uint32_t GetActiveWidgetID() ;

    private:
        bool m_BlockEvents = true;
    };

} // namespace Gaze

#endif // GAZE_ENGINE_IMGUI_IMGUILAYER_H
