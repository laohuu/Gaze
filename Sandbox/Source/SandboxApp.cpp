#include <Gaze.h>
#include <Core/EntryPoint.h>

#include "Sandbox2D.h"
#include "ExampleLayer.h"

class Sandbox : public Gaze::Application {
public:
    Sandbox(const Gaze::ApplicationSpecification &specification)
            : Gaze::Application(specification) {
//        PushLayer(new ExampleLayer());
        PushLayer(new Sandbox2D());
    }

    ~Sandbox() override {}

private:

};

Gaze::Application *Gaze::CreateApplication() {
    ApplicationSpecification spec;
    spec.Name = "Sandbox";

    return new Sandbox(spec);
}
