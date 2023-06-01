#ifndef GAZE_APPLICATION_H
#define GAZE_APPLICATION_H

#include "Base.h"
#include "Core/Log.h"

#include "Core/Window.h"
#include "Core/LayerStack.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"

#include "Timestep.h"

#include "ImGui/ImGuiLayer.h"


int main(int argc, char **argv);

namespace Gaze {

    class Application {
    public:
        Application();

        virtual ~Application();

        void OnEvent(Event &e);

        void PushLayer(Layer *layer);

        void PushOverlay(Layer *layer);

        Window &GetWindow() { return *m_Window; }

        static Application &Get() { return *s_Instance; }

    private:
        void Run();

        bool OnWindowClose(WindowCloseEvent &e);

        bool OnWindowResize(WindowResizeEvent &e);

    private:
        Gaze::Scope<Window> m_Window;

        ImGuiLayer *m_ImGuiLayer;
        bool m_Running = true;
        LayerStack m_LayerStack;

        bool m_Minimized;
        float m_LastFrameTime = 0.0f;

    private:
        static Application *s_Instance;

        friend int::main(int argc, char **argv);
    };

    Application *CreateApplication();

} // Gaze

#endif //GAZE_APPLICATION_H
