#ifndef GAZE_ENGINE_SCENE_H
#define GAZE_ENGINE_SCENE_H

#include "Core/Timestep.h"
#include "Core/UUID.h"
#include "entt.hpp"

#include "Renderer/EditorCamera.h"

class b2World;

namespace Gaze
{
    class Entity;

    class Scene : public RefCounted
    {
    public:
        Scene(const std::string& name = "UntitledScene", bool isEditorScene = false, bool initalize = true);
        ~Scene();

        void Init();
        void OnShutdown();

        static Ref<Scene> Copy(Ref<Scene> other);

        Entity CreateEntity(const std::string& name = std::string());
        Entity CreateEntityWithUUID(UUID uuid, const std::string& name = std::string());
        void   DestroyEntity(Entity entity);

        void OnRuntimeStart();
        void OnRuntimeStop();

        void OnSimulationStart();
        void OnSimulationStop();

        void OnUpdateRuntime(Timestep ts);
        void OnUpdateSimulation(Timestep ts, EditorCamera& camera);
        void OnUpdateEditor(Timestep ts, EditorCamera& camera);
        void OnViewportResize(uint32_t width, uint32_t height);

        Entity DuplicateEntity(Entity entity);

        Entity FindEntityByName(std::string_view name);
        Entity GetEntityByUUID(UUID uuid);

        Entity GetPrimaryCameraEntity();

        const std::string& GetName() const { return m_Name; }
        void               SetName(const std::string& name) { m_Name = name; }

        bool IsRunning() const { return m_IsRunning; }
        bool IsPaused() const { return m_IsPaused; }

        void SetPaused(bool paused) { m_IsPaused = paused; }

        void Step(int frames = 1);

        template<typename... Components>
        auto GetAllEntitiesWith()
        {
            return m_Registry.view<Components...>();
        }

    private:
        template<typename T>
        void OnComponentAdded(Entity entity, T& component);

        void OnPhysics2DStart();
        void OnPhysics2DStop();

        void RenderScene(EditorCamera& camera);

    private:
        UUID           m_SceneID;
        entt::entity   m_SceneEntity = entt::null;
        entt::registry m_Registry;

        std::string m_Name;
        bool        m_IsEditorScene = false;
        uint32_t    m_ViewportWidth = 0, m_ViewportHeight = 0;

        bool m_IsRunning  = false;
        bool m_IsPaused   = false;
        int  m_StepFrames = 0;

        std::unordered_map<UUID, entt::entity> m_EntityMap;

        friend class Entity;
        friend class SceneSerializer;
        friend class SceneHierarchyPanel;
    };
} // namespace Gaze

#endif // GAZE_ENGINE_SCENE_H
