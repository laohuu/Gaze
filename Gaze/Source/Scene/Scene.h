#ifndef GAZE_ENGINE_SCENE_H
#define GAZE_ENGINE_SCENE_H

#include "entt.hpp"
#include "Core/Timestep.h"

namespace Gaze {

    class Scene {
    public:
        Scene();

        ~Scene();

        entt::entity CreateEntity();

        // TEMP
        entt::registry &Reg() { return m_Registry; }

        void OnUpdate(Timestep ts);

    private:
        entt::registry m_Registry;
    };

} // Gaze

#endif //GAZE_ENGINE_SCENE_H
