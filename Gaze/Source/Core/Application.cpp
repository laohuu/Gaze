#include "GazePCH.h"
#include "Application.h"

namespace Gaze {
    Application::Application() {
    }

    Application::~Application() {
    }

    void Application::Run() {

        WindowResizeEvent e(1280, 720);
        if (e.IsInCategory(EventCategoryApplication))
        {
            GZ_TRACE(e.ToString());
        }
        if (e.IsInCategory(EventCategoryInput))
        {
            GZ_TRACE(e.ToString());
        }
//        while (true) {
//        }
    }
} // Gaze