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

    struct ApplicationCommandLineArgs {
        int Count = 0;
        char **Args = nullptr;

        const char *operator[](int index) const {
            GZ_CORE_ASSERT(index < Count);
            return Args[index];
        }
    };

    struct ApplicationSpecification {
        std::string Name = "Gaze Application";
        ApplicationCommandLineArgs CommandLineArgs;
    };

    class Application {
    public:
        Application(const ApplicationSpecification &specification);

        virtual ~Application();

        void OnEvent(Event &e);

        void PushLayer(Layer *layer);

        void PushOverlay(Layer *layer);

        Window &GetWindow() { return *m_Window; }

        void Close();

        ImGuiLayer *GetImGuiLayer() { return m_ImGuiLayer; }

        static Application &Get() { return *s_Instance; }

        const ApplicationSpecification &GetSpecification() const { return m_Specification; }

    private:
        void Run();

        bool OnWindowClose(WindowCloseEvent &e);

        bool OnWindowResize(WindowResizeEvent &e);

    private:
        ApplicationSpecification m_Specification;
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

    // To be defined in CLIENT
    Application *CreateApplication(ApplicationCommandLineArgs args);

} // Gaze

#endif //GAZE_APPLICATION_H
