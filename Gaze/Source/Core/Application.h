#ifndef GAZE_APPLICATION_H
#define GAZE_APPLICATION_H

#include "Core.h"
#include "Core/Log.h"

#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Window.h"

int main(int argc, char **argv);

namespace Gaze {

    class Application {
    public:
        Application();

        virtual ~Application();

        void Run();
    private:
        std::unique_ptr<Window> m_Window;
        bool m_Running = true;
    };

    Application *CreateApplication();

} // Gaze

#endif //GAZE_APPLICATION_H
