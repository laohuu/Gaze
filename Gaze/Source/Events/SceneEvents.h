#ifndef GAZE_ENGINE_SCENEEVENTS_H
#define GAZE_ENGINE_SCENEEVENTS_H

#include "Event.h"
#include "Scene/Entity.h"
#include "Scene/Scene.h"

#include <sstream>

namespace Gaze
{
    class SceneEvent : public Event
    {
    public:
        const Ref<Scene>& GetScene() const { return m_Scene; }
        Ref<Scene>        GetScene() { return m_Scene; }

        EVENT_CLASS_CATEGORY(EventCategoryApplication | EventCategoryScene)
    protected:
        SceneEvent(const Ref<Scene>& scene) : m_Scene(scene) {}

        Ref<Scene> m_Scene;
    };

    class ScenePreStartEvent : public SceneEvent
    {
    public:
        ScenePreStartEvent(const Ref<Scene>& scene) : SceneEvent(scene) {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "ScenePreStartEvent: " << m_Scene->GetName();
            return ss.str();
        }

        EVENT_CLASS_TYPE(ScenePreStart)
    };

    class ScenePostStartEvent : public SceneEvent
    {
    public:
        ScenePostStartEvent(const Ref<Scene>& scene) : SceneEvent(scene) {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "ScenePostStartEvent: " << m_Scene->GetName();
            return ss.str();
        }

        EVENT_CLASS_TYPE(ScenePostStart)
    };

    class ScenePreStopEvent : public SceneEvent
    {
    public:
        ScenePreStopEvent(const Ref<Scene>& scene) : SceneEvent(scene) {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "ScenePreStopEvent: " << m_Scene->GetName();
            return ss.str();
        }

        EVENT_CLASS_TYPE(ScenePreStop)
    };

    class ScenePostStopEvent : public SceneEvent
    {
    public:
        ScenePostStopEvent(const Ref<Scene>& scene) : SceneEvent(scene) {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "ScenePostStopEvent: " << m_Scene->GetName();
            return ss.str();
        }

        EVENT_CLASS_TYPE(ScenePostStop)
    };
} // namespace Gaze

#endif // GAZE_ENGINE_SCENEEVENTS_H
