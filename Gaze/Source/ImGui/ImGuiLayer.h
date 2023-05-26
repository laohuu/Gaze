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

        ~ImGuiLayer() = default;

        virtual void OnAttach() override;

        virtual void OnDetach() override;

        virtual void OnImGuiRender() override;

        void Begin();

        void End();

    private:
        float m_Time = 0.0f;
    };
}

#endif //GAZE_ENGINE_IMGUILAYER_H
