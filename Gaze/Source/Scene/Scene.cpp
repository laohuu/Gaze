#include "GazePCH.h"
#include "Scene.h"

#include "Components.h"
#include "Renderer/Renderer2D.h"

namespace Gaze {

    static void DoMath(const glm::mat4 &transform) {

    }

    static void OnTransformConstruct(entt::registry &registry, entt::entity entity) {

    }

    Scene::Scene() = default;

    Scene::~Scene() = default;

    entt::entity Scene::CreateEntity() {
        return m_Registry.create();
    }

    void Scene::OnUpdate(Timestep ts) {
        // Draw sprites
        {
            auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
            for (auto entity: group) {
                auto [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

                Renderer2D::DrawQuad(transform, sprite.Color);
            }
        }
    }

} // Gaze