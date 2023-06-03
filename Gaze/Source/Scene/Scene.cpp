#include "GazePCH.h"
#include "Scene.h"

#include "Components.h"
#include "Renderer/Renderer2D.h"
#include "Entity.h"

namespace Gaze {

    static void DoMath(const glm::mat4 &transform) {

    }

    static void OnTransformConstruct(entt::registry &registry, entt::entity entity) {

    }

    Entity Scene::CreateEntity(const std::string &name) {
        Entity entity = {m_Registry.create(), this};
        entity.AddComponent<TransformComponent>();
        auto &tag = entity.AddComponent<TagComponent>();
        tag.Tag = name.empty() ? "Entity" : name;
        return entity;
    }

    void Scene::OnUpdate(Timestep ts) {

        // Render 2D
        Camera *mainCamera = nullptr;
        glm::mat4 cameraTransform;
        {
            auto view = m_Registry.view<TransformComponent, CameraComponent>();
            for (auto entity: view) {
                auto [transform, camera] = view.get<TransformComponent, CameraComponent>(entity);

                if (camera.Primary) {
                    mainCamera = &camera.Camera;
                    cameraTransform = transform.Transform;
                    break;
                }
            }
        }

        if (mainCamera) {
            Renderer2D::BeginScene(mainCamera->GetProjection(), cameraTransform);

            // Draw sprites
            {
                auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
                for (auto entity: group) {
                    auto [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

                    Renderer2D::DrawQuad(transform, sprite.Color);
                }
            }

            Renderer2D::EndScene();
        }

    }


} // Gaze