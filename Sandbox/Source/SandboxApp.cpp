#include <Gaze.h>
#include "Events/KeyEvent.h"

class ExampleLayer : public Gaze::Layer {
public:
    ExampleLayer() {};

    virtual ~ExampleLayer() = default;

    virtual void OnAttach() override {};

    virtual void OnDetach() override {};

    void OnUpdate() override {
        if (Gaze::Input::IsKeyPressed(Gaze::Key::Tab))
            GZ_TRACE("Tab key is pressed (poll)!");
    };

    virtual void OnImGuiRender() override {};

    void OnEvent(Gaze::Event &event) override {
        if (event.GetEventType() == Gaze::EventType::KeyPressed) {
            auto &e = (Gaze::KeyPressedEvent &) event;
            if (e.GetKeyCode() == Gaze::Key::Tab)
                GZ_TRACE("Tab key is pressed (event)!");
            GZ_TRACE("{0}", (char) e.GetKeyCode());
        }
    };
};


class Sandbox : public Gaze::Application {
public:
    Sandbox() {
        PushLayer(new ExampleLayer());
    }

    ~Sandbox() {}

private:

};

Gaze::Application *Gaze::CreateApplication() {
    return new Sandbox();
}
