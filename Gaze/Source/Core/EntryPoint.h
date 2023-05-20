#ifndef GAZE_ENTRYPOINT_H
#define GAZE_ENTRYPOINT_H


int main(int argc, char **argv) {
    Gaze::Log::Init();

    GZ_CORE_WARN("Hello Gaze Engine");
    int a = 5;
    GZ_INFO("Hello! Var={0}", a);

    auto app = Gaze::CreateApplication();
    app->Run();
    delete app;
    return 0;
}

#endif //GAZE_ENTRYPOINT_H
