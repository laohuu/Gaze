#include <Gaze.h>
#include <Core/EntryPoint.h>

#include "Sandbox2D.h"
#include "ExampleLayer.h"


class Sandbox : public Gaze::Application {
public:
    Sandbox() {
//        PushLayer(new ExampleLayer());
        PushLayer(new Sandbox2D());
    }

    ~Sandbox() override {}

private:

};

Gaze::Application *Gaze::CreateApplication() {
    return new Sandbox();
}
