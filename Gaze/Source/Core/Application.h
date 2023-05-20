#ifndef GAZE_APPLICATION_H
#define GAZE_APPLICATION_H

#include "Core.h"

int main(int argc, char **argv);

namespace Gaze {

    class Application {
    public:
        Application();
        virtual ~Application();

        void Run();
    };

    Application *CreateApplication();
} // Gaze

#endif //GAZE_APPLICATION_H
