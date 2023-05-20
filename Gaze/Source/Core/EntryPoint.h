#ifndef GAZE_ENTRYPOINT_H
#define GAZE_ENTRYPOINT_H


int main(int argc, char **argv) {
    Gaze::Log::Init();

    GZ_CORE_WARN("Hello Gaze Engine");

    auto app = Gaze::CreateApplication();
    app->Run();
    delete app;
    return 0;
}

#endif //GAZE_ENTRYPOINT_H
