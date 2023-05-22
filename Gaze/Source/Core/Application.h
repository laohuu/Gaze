#ifndef GAZE_APPLICATION_H
#define GAZE_APPLICATION_H

#include "Core.h"
#include "Core/Log.h"

#include "Core/Window.h"
#include "Core/LayerStack.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "ImGui/ImGuiLayer.h"

#include "Renderer/Shader.h"
#include "Renderer/Buffer.h"

int main(int argc, char **argv);

namespace Gaze {

    class Application {
    public:
        Application();

        virtual ~Application();

        void OnEvent(Event &e);

        void PushLayer(Layer *layer);

        void PushOverlay(Layer *layer);

        inline Window &GetWindow() { return *m_Window; }

        static Application &Get() { return *s_Instance; }

        void Run();

    private:
        bool OnWindowClose(WindowCloseEvent &e);

        bool OnWindowResize(WindowResizeEvent &e);

    private:
        std::unique_ptr<Window> m_Window;

        ImGuiLayer *m_ImGuiLayer;
        bool m_Running = true;
        LayerStack m_LayerStack;
        unsigned int m_VertexArray;
        std::unique_ptr<Shader> m_Shader;
        std::unique_ptr<VertexBuffer> m_VertexBuffer;
        std::unique_ptr<IndexBuffer> m_IndexBuffer;
        bool m_Minimized;

    private:
        static Application *s_Instance;
    };

    Application *CreateApplication();

} // Gaze

#endif //GAZE_APPLICATION_H
