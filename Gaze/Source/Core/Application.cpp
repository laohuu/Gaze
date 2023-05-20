#include "GazePCH.h"
#include "Application.h"

#include <GLFW/glfw3.h>

namespace Gaze {

    Application::Application() {
        m_Window = std::unique_ptr<Window>(Window::Create());
    }

    Application::~Application() {
    }

    void Application::Run() {

        WindowResizeEvent e(1280, 720);
        if (e.IsInCategory(EventCategoryApplication)) {
            GZ_TRACE(e.ToString());
        }
        if (e.IsInCategory(EventCategoryInput)) {
            GZ_TRACE(e.ToString());
        }
        while (m_Running) {
            glClearColor(1.0f, 0.5f, 0.2f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            m_Window->OnUpdate();
        }
    }
} // Gaze