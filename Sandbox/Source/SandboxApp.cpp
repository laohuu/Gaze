#include <Gaze.h>
#include <Core/EntryPoint.h>

class Sandbox : public Gaze::Application {
public:
    Sandbox() {}
    ~Sandbox() {}

private:

};

Gaze::Application *Gaze::CreateApplication() {
    return new Sandbox();
}
