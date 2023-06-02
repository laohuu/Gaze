#ifndef GAZE_ENTRYPOINT_H
#define GAZE_ENTRYPOINT_H

#include "Core/Base.h"

int main(int argc, char **argv) {
    Gaze::Log::Init();

    GZ_CORE_WARN("Hello Gaze Engine");

    GZ_PROFILE_BEGIN_SESSION("Startup", "C:/Users/hangh/Documents/GitHub/Gaze/GazeProfile-Startup.json");
    auto app = Gaze::CreateApplication();
    GZ_PROFILE_END_SESSION();


    GZ_PROFILE_BEGIN_SESSION("Runtime", "C:/Users/hangh/Documents/GitHub/Gaze/GazeProfile-Runtime.json");
    app->Run();
    GZ_PROFILE_END_SESSION();

    GZ_PROFILE_BEGIN_SESSION("Startup", "C:/Users/hangh/Documents/GitHub/Gaze/GazeProfile-Shutdown.json");
    delete app;
    GZ_PROFILE_END_SESSION();
    return 0;
}

#endif //GAZE_ENTRYPOINT_H
