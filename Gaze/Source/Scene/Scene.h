#ifndef GAZE_ENGINE_SCENE_H
#define GAZE_ENGINE_SCENE_H

#include "entt.hpp"
#include "Core/Timestep.h"

namespace Gaze {

    class Entity;

    class Scene {
    public:
        Scene() = default;

        ~Scene() = default;

        Entity CreateEntity(const std::string &name = std::string());

        void OnUpdate(Timestep ts);

    private:
        entt::registry m_Registry;

        friend class Entity;
    };

} // Gaze

#endif //GAZE_ENGINE_SCENE_H
