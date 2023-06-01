#ifndef GAZE_ENGINE_LAYER_H
#define GAZE_ENGINE_LAYER_H

#include "Core/Base.h"
#include "Events/Event.h"
#include "Timestep.h"

namespace Gaze {

    class Layer
    {
    public:
        Layer(const std::string& name = "Layer");
        virtual ~Layer() = default;

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate(Timestep ts) {}
        virtual void OnImGuiRender() {}
        virtual void OnEvent(Event& event) {}

        const std::string& GetName() const { return m_DebugName; }
    protected:
        std::string m_DebugName;
    };

}


#endif //GAZE_ENGINE_LAYER_H
