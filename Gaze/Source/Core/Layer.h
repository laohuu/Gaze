#ifndef GAZE_ENGINE_LAYER_H
#define GAZE_ENGINE_LAYER_H

#include "Core/Core.h"
#include "Events/Event.h"

namespace Gaze {

    class Layer
    {
    public:
        Layer(const std::string& name = "Layer");
        virtual ~Layer() = default;

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate() {}
        virtual void OnImGuiRender() {}
        virtual void OnEvent(Event& event) {}

        const std::string& GetName() const { return m_DebugName; }
    protected:
        std::string m_DebugName;
    };

}


#endif //GAZE_ENGINE_LAYER_H
