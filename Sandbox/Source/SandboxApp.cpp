#include <Gaze.h>
#include "Events/KeyEvent.h"
//#include "ExampleLayer.h"



class ExampleLayer : public Gaze::Layer {
public:
    ExampleLayer() {};

    virtual ~ExampleLayer() = default;

    virtual void OnAttach() override {};

    virtual void OnDetach() override {};

    void OnUpdate() override {
//        GZ_TRACE("ExampleLayer OnUpdate!");
    };

    virtual void OnImGuiRender() override {};

    void OnEvent(Gaze::Event &event) override {
        if (event.GetEventType() == Gaze::EventType::KeyPressed) {
            Gaze::KeyPressedEvent &e = (Gaze::KeyPressedEvent &) event;
            GZ_TRACE("{0}", e);
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
