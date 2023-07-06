#ifndef GAZE_ENGINE_PHYSICSSYSTEM_H
#define GAZE_ENGINE_PHYSICSSYSTEM_H

#include "Events/SceneEvents.h"
#include "PhysicsSettings.h"

namespace Gaze
{
    class PhysicsSystem
    {
    public:
        static void Init();
        static void Shutdown();

        static PhysicsSettings&   GetSettings() { return s_PhysicsSettings; }

    private:
        static void OnEvent(Event& event);

    private:
        inline static PhysicsSettings s_PhysicsSettings;
    };
} // namespace Gaze

#endif // GAZE_ENGINE_PHYSICSSYSTEM_H
