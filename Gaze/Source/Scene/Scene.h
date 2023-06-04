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

        void DestroyEntity(Entity entity);

        void OnUpdate(Timestep ts);

        void OnViewportResize(uint32_t width, uint32_t height);

        Entity GetPrimaryCameraEntity();

    private:
        template<typename T>
        void OnComponentAdded(Entity entity, T &component);

    private:
        entt::registry m_Registry;
        uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;

        friend class Entity;

        friend class SceneHierarchyPanel;

        friend class SceneSerializer;
    };

} // Gaze

#endif //GAZE_ENGINE_SCENE_H
