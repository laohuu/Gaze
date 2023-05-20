#ifndef GAZE_ENTRYPOINT_H
#define GAZE_ENTRYPOINT_H


int main(int argc, char** argv) {
    std::cout << "Hello Gaze";
    auto app = Gaze::CreateApplication();
    app->Run();
    delete app;
    return 0;
}

#endif //GAZE_ENTRYPOINT_H
