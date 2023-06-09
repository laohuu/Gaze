#include "Scene.h"
#include "GazePCH.h"

#include "Components.h"
#include "Entity.h"
#include "Physics/2D/Physics2D.h"
#include "Physics/3D/PhysicsScene.h"
#include "Renderer/Renderer2D.h"
#include "ScriptableEntity.h"
#include "Scripting/ScriptEngine.h"

// Box2D
#include "box2d/b2_body.h"
#include "box2d/b2_circle_shape.h"
#include "box2d/b2_fixture.h"
#include "box2d/b2_polygon_shape.h"
#include "box2d/b2_world.h"

namespace Gaze
{
    std::unordered_map<UUID, Scene*> s_ActiveScenes;

    struct SceneComponent
    {
        UUID SceneID;
    };

    class PhysXContactListener : public physx::PxSimulationEventCallback
    {
    public:
        virtual void onConstraintBreak(physx::PxConstraintInfo* constraints, physx::PxU32 count) override
        {
            PX_UNUSED(constraints);
            PX_UNUSED(count);
        }

        virtual void onWake(physx::PxActor** actors, physx::PxU32 count) override
        {
            PX_UNUSED(actors);
            PX_UNUSED(count);
        }

        virtual void onSleep(physx::PxActor** actors, physx::PxU32 count) override
        {
            PX_UNUSED(actors);
            PX_UNUSED(count);
        }

        virtual void onContact(const physx::PxContactPairHeader& pairHeader,
                               const physx::PxContactPair*       pairs,
                               physx::PxU32                      nbPairs) override
        {
            Entity& a = *(Entity*)pairHeader.actors[0]->userData;
            Entity& b = *(Entity*)pairHeader.actors[1]->userData;
        }

        virtual void onTrigger(physx::PxTriggerPair* pairs, physx::PxU32 count) override
        {
            PX_UNUSED(pairs);
            PX_UNUSED(count);
        }

        virtual void onAdvance(const physx::PxRigidBody* const* bodyBuffer,
                               const physx::PxTransform*        poseBuffer,
                               const physx::PxU32               count) override
        {
            PX_UNUSED(bodyBuffer);
            PX_UNUSED(poseBuffer);
            PX_UNUSED(count);
        }
    };

    static PhysXContactListener s_PhysXContactListener;

    struct PhysXSceneComponent
    {
        // NOTE: PhysX does some internal ref counting, and thus doesn't allow unique_ptr
        physx::PxScene* World;
    };

    Scene::Scene(const std::string& name, bool isEditorScene, bool initalize) :
        m_Name(name), m_IsEditorScene(isEditorScene)
    {
        m_SceneEntity = m_Registry.create();
        m_Registry.emplace<SceneComponent>(m_SceneEntity, m_SceneID);
        s_ActiveScenes[m_SceneID] = this;

        if (!initalize)
            return;

        Box2DWorldComponent& b2dWorld =
            m_Registry.emplace<Box2DWorldComponent>(m_SceneEntity, std::make_unique<b2World>(b2Vec2 {0.0f, -9.8f}));

        physx::PxSceneDesc sceneDesc      = PhysicsScene::CreateSceneDesc();
        sceneDesc.gravity                 = physx::PxVec3(0.0F, -9.8F, 0.0F);
        sceneDesc.simulationEventCallback = &s_PhysXContactListener;
        PhysXSceneComponent& physxWorld =
            m_Registry.emplace<PhysXSceneComponent>(m_SceneEntity, PhysicsScene::CreateScene(sceneDesc));

        Init();
    }

    Scene::~Scene()
    {
        // Clear the registry so that all callbacks are called
        m_Registry.clear();

        s_ActiveScenes.erase(m_SceneID);
    }

    void Scene::Init() {}

    void Scene::OnShutdown()
    {
        //        auto            physxView  = m_Registry.view<PhysXSceneComponent>();
        //        physx::PxScene* physxScene = m_Registry.get<PhysXSceneComponent>(physxView.front()).World;
        //        physxScene->release();
    }

    template<typename... Component>
    static void
    CopyComponent(entt::registry& dst, entt::registry& src, const std::unordered_map<UUID, entt::entity>& enttMap)
    {
        (
            [&]() {
                auto view = src.view<Component>();
                for (auto srcEntity : view)
                {
                    entt::entity dstEntity = enttMap.at(src.get<IDComponent>(srcEntity).ID);

                    auto& srcComponent = src.get<Component>(srcEntity);
                    dst.emplace_or_replace<Component>(dstEntity, srcComponent);
                }
            }(),
            ...);
    }

    template<typename... Component>
    static void CopyComponent(ComponentGroup<Component...>,
                              entt::registry&                               dst,
                              entt::registry&                               src,
                              const std::unordered_map<UUID, entt::entity>& enttMap)
    {
        CopyComponent<Component...>(dst, src, enttMap);
    }

    template<typename... Component>
    static void CopyComponentIfExists(Entity dst, Entity src)
    {
        (
            [&]() {
                if (src.HasComponent<Component>())
                    dst.AddOrReplaceComponent<Component>(src.GetComponent<Component>());
            }(),
            ...);
    }

    template<typename... Component>
    static void CopyComponentIfExists(ComponentGroup<Component...>, Entity dst, Entity src)
    {
        CopyComponentIfExists<Component...>(dst, src);
    }

    Gaze::Ref<Scene> Scene::Copy(Gaze::Ref<Scene> other)
    {
        Gaze::Ref<Scene> newScene = CreateRef<Scene>();

        newScene->m_ViewportWidth  = other->m_ViewportWidth;
        newScene->m_ViewportHeight = other->m_ViewportHeight;

        auto&                                  srcSceneRegistry = other->m_Registry;
        auto&                                  dstSceneRegistry = newScene->m_Registry;
        std::unordered_map<UUID, entt::entity> enttMap;

        // Create entities in new scene
        auto idView = srcSceneRegistry.view<IDComponent>();
        for (auto e : idView)
        {
            UUID        uuid      = srcSceneRegistry.get<IDComponent>(e).ID;
            const auto& name      = srcSceneRegistry.get<TagComponent>(e).Tag;
            Entity      newEntity = newScene->CreateEntityWithUUID(uuid, name);
            enttMap[uuid]         = (entt::entity)newEntity;
        }

        // Copy components (except IDComponent and TagComponent)
        CopyComponent(AllComponents {}, dstSceneRegistry, srcSceneRegistry, enttMap);
        return newScene;
    }

    Entity Scene::CreateEntity(const std::string& name) { return CreateEntityWithUUID(UUID(), name); }

    Entity Scene::CreateEntityWithUUID(UUID uuid, const std::string& name)
    {
        Entity entity = {m_Registry.create(), this};
        entity.AddComponent<IDComponent>(uuid);
        entity.AddComponent<TransformComponent>();
        auto& tag = entity.AddComponent<TagComponent>();
        tag.Tag   = name.empty() ? "Entity" : name;

        m_EntityMap[uuid] = entity;

        return entity;
    }

    Entity Scene::DuplicateEntity(Entity entity)
    {
        // Copy name because we're going to modify component data structure
        std::string name      = entity.GetName();
        Entity      newEntity = CreateEntity(name);
        CopyComponentIfExists(AllComponents {}, newEntity, entity);
        return newEntity;
    }

    void Scene::DestroyEntity(Entity entity)
    {
        if (!entity)
            return;

        m_EntityMap.erase(entity.GetUUID());
        m_Registry.destroy(entity);

        if (m_IsRunning)
        {
            if (entity.HasComponent<RigidBody2DComponent>())
            {
                auto&   world = m_Registry.get<Box2DWorldComponent>(m_SceneEntity).World;
                b2Body* body  = (b2Body*)entity.GetComponent<RigidBody2DComponent>().RuntimeBody;
                world->DestroyBody(body);
            }
        }
    }

    void Scene::OnRuntimeStart()
    {
        m_IsRunning = true;

        OnPhysics2DStart();

        // Scripting
        {
            ScriptEngine::OnRuntimeStart(this);
            // Instantiate all script entities

            auto view = m_Registry.view<ScriptComponent>();
            for (auto e : view)
            {
                Entity entity = {e, this};
                ScriptEngine::OnCreateEntity(entity);
            }
        }
    }

    void Scene::OnRuntimeStop()
    {
        m_IsRunning = false;

        OnPhysics2DStop();

        ScriptEngine::OnRuntimeStop();
    }

    void Scene::OnSimulationStart() { OnPhysics2DStart(); }

    void Scene::OnSimulationStop() { OnPhysics2DStop(); }

    void Scene::OnUpdateRuntime(Timestep ts)
    {
        if (!m_IsPaused || m_StepFrames-- > 0)
        {
            // Update scripts
            { // C# Entity OnUpdate
                auto view = m_Registry.view<ScriptComponent>();
                for (auto e : view)
                {
                    Entity entity = {e, this};
                    ScriptEngine::OnUpdateEntity(entity, ts);
                }

                m_Registry.view<NativeScriptComponent>().each([=](auto entity, auto& nsc) {
                    // TODO: Move to Scene::OnScenePlay
                    if (!nsc.Instance)
                    {
                        nsc.Instance           = nsc.InstantiateScript();
                        nsc.Instance->m_Entity = Entity {entity, this};
                        nsc.Instance->OnCreate();
                    }

                    nsc.Instance->OnUpdate(ts);
                });
            }

            // Box2D physics
            {
                auto    sceneView          = m_Registry.view<Box2DWorldComponent>();
                auto&   box2DWorld         = m_Registry.get<Box2DWorldComponent>(sceneView.front()).World;
                int32_t velocityIterations = 6;
                int32_t positionIterations = 2;
                box2DWorld->Step(ts, velocityIterations, positionIterations);
            }
            // Retrieve transform from Box2D
            {
                auto view = m_Registry.view<RigidBody2DComponent>();
                for (auto entity : view)
                {
                    Entity e    = {entity, this};
                    auto&  rb2d = e.GetComponent<RigidBody2DComponent>();

                    if (rb2d.RuntimeBody == nullptr)
                        continue;

                    b2Body* body = static_cast<b2Body*>(rb2d.RuntimeBody);

                    auto& position          = body->GetPosition();
                    auto& transform         = e.GetComponent<TransformComponent>();
                    transform.Translation.x = position.x;
                    transform.Translation.y = position.y;
                    glm::vec3 rotation      = transform.GetRotationEuler();
                    rotation.z              = body->GetAngle();
                    transform.SetRotationEuler(rotation);
                }
            }

            // PhysX Physics
            auto            physxView  = m_Registry.view<PhysXSceneComponent>();
            physx::PxScene* physxScene = m_Registry.get<PhysXSceneComponent>(physxView.front()).World;
            constexpr float stepSize   = 0.016666660f;
            physxScene->simulate(stepSize);
            physxScene->fetchResults(true);

            {
                auto view = m_Registry.view<RigidBodyComponent>();
                for (auto entity : view)
                {
                    Entity               e                   = {entity, this};
                    RigidBodyComponent&  rb                  = e.GetComponent<RigidBodyComponent>();
                    physx::PxRigidActor* actor               = static_cast<physx::PxRigidActor*>(rb.RuntimeActor);
                    physx::PxVec3        position            = actor->getGlobalPose().p;
                    physx::PxQuat        physicsBodyRotation = actor->getGlobalPose().q;
                    auto&                transform           = e.GetComponent<TransformComponent>();
                    if (rb.BodyType == RigidBodyComponent::Type::Dynamic)
                    {
                        // If the rigidbody is dynamic, the position of the entity is determined by the rigidbody
                        // TODO: Get rotation from RigidActor
                        float         xAngle, yAngle, zAngle;
                        physx::PxVec3 axis;
                        physicsBodyRotation.toRadiansAndUnitAxis(xAngle, axis);
                        physicsBodyRotation.toRadiansAndUnitAxis(yAngle, axis);
                        physicsBodyRotation.toRadiansAndUnitAxis(zAngle, axis);

                        transform.Translation.x = position.x;
                        transform.Translation.y = position.y;
                        transform.Translation.z = position.z;
                        transform.SetRotation(glm::quat({xAngle, yAngle, zAngle}));
                    }
                    else if (rb.BodyType == RigidBodyComponent::Type::Static)
                    {
                        // If the rigidbody is static, make sure the actor is at the entitys position
                        actor->setGlobalPose(PhysicsScene::CreatePose(transform.GetTransform()));
                    }
                }
            }
        }

        // Render 2D
        Camera*   mainCamera = nullptr;
        glm::mat4 cameraTransform;
        {
            auto view = m_Registry.view<TransformComponent, CameraComponent>();
            for (auto entity : view)
            {
                auto [transform, camera] = view.get<TransformComponent, CameraComponent>(entity);

                if (camera.Primary)
                {
                    mainCamera      = &camera.Camera;
                    cameraTransform = transform.GetTransform();
                    break;
                }
            }
        }

        if (mainCamera)
        {
            Renderer2D::BeginScene(*mainCamera, cameraTransform);

            // Draw sprites
            {
                auto view = m_Registry.view<TransformComponent, SpriteRendererComponent>();
                for (auto entity : view)
                {
                    auto [transform, sprite] = view.get<TransformComponent, SpriteRendererComponent>(entity);

                    Renderer2D::DrawSprite(transform.GetTransform(), sprite, (int)entity);
                }
            }

            // Draw circles
            {
                auto view = m_Registry.view<TransformComponent, CircleRendererComponent>();
                for (auto entity : view)
                {
                    auto [transform, circle] = view.get<TransformComponent, CircleRendererComponent>(entity);

                    Renderer2D::DrawCircle(
                        transform.GetTransform(), circle.Color, circle.Thickness, circle.Fade, (int)entity);
                }
            }

            Renderer2D::EndScene();
        }
    }

    void Scene::OnUpdateSimulation(Gaze::Timestep ts, Gaze::EditorCamera& camera)
    {
        if (!m_IsPaused || m_StepFrames-- > 0)
        {
            // Box2D physics
            {
                auto    sceneView          = m_Registry.view<Box2DWorldComponent>();
                auto&   box2DWorld         = m_Registry.get<Box2DWorldComponent>(sceneView.front()).World;
                int32_t velocityIterations = 6;
                int32_t positionIterations = 2;
                box2DWorld->Step(ts, velocityIterations, positionIterations);
            }
            {
                auto view = m_Registry.view<RigidBody2DComponent>();
                for (auto entity : view)
                {
                    Entity e    = {entity, this};
                    auto&  rb2d = e.GetComponent<RigidBody2DComponent>();

                    if (rb2d.RuntimeBody == nullptr)
                        continue;

                    b2Body* body = static_cast<b2Body*>(rb2d.RuntimeBody);

                    auto& position          = body->GetPosition();
                    auto& transform         = e.GetComponent<TransformComponent>();
                    transform.Translation.x = position.x;
                    transform.Translation.y = position.y;
                    glm::vec3 rotation      = transform.GetRotationEuler();
                    rotation.z              = body->GetAngle();
                    transform.SetRotationEuler(rotation);
                }
            }

            // PhysX Physics
            auto            physxView  = m_Registry.view<PhysXSceneComponent>();
            physx::PxScene* physxScene = m_Registry.get<PhysXSceneComponent>(physxView.front()).World;
            constexpr float stepSize   = 0.016666660f;
            physxScene->simulate(stepSize);
            physxScene->fetchResults(true);

            {
                auto view = m_Registry.view<RigidBodyComponent>();
                for (auto entity : view)
                {
                    Entity               e                   = {entity, this};
                    RigidBodyComponent&  rb                  = e.GetComponent<RigidBodyComponent>();
                    physx::PxRigidActor* actor               = static_cast<physx::PxRigidActor*>(rb.RuntimeActor);
                    physx::PxVec3        position            = actor->getGlobalPose().p;
                    physx::PxQuat        physicsBodyRotation = actor->getGlobalPose().q;
                    auto&                transform           = e.GetComponent<TransformComponent>();
                    if (rb.BodyType == RigidBodyComponent::Type::Dynamic)
                    {
                        // If the rigidbody is dynamic, the position of the entity is determined by the rigidbody
                        // TODO: Get rotation from RigidActor
                        float         xAngle, yAngle, zAngle;
                        physx::PxVec3 axis;
                        physicsBodyRotation.toRadiansAndUnitAxis(xAngle, axis);
                        physicsBodyRotation.toRadiansAndUnitAxis(yAngle, axis);
                        physicsBodyRotation.toRadiansAndUnitAxis(zAngle, axis);

                        transform.Translation.x = position.x;
                        transform.Translation.y = position.y;
                        transform.Translation.z = position.z;
                        transform.SetRotation(glm::quat({xAngle, yAngle, zAngle}));
                    }
                    else if (rb.BodyType == RigidBodyComponent::Type::Static)
                    {
                        // If the rigidbody is static, make sure the actor is at the entitys position
                        actor->setGlobalPose(PhysicsScene::CreatePose(transform.GetTransform()));
                    }
                }
            }
        }

        // Render
        RenderScene(camera);
    }

    void Scene::OnUpdateEditor(Timestep ts, EditorCamera& camera)
    {
        // Render
        RenderScene(camera);
    }

    void Scene::Step(int frames) { m_StepFrames = frames; }

    Entity Scene::FindEntityByName(std::string_view name)
    {
        auto view = m_Registry.view<TagComponent>();
        for (auto entity : view)
        {
            const TagComponent& tc = view.get<TagComponent>(entity);
            if (tc.Tag == name)
                return Entity {entity, this};
        }
        return {};
    }

    Entity Scene::GetEntityByUUID(UUID uuid)
    {
        // TODO: Maybe should be assert
        if (m_EntityMap.find(uuid) != m_EntityMap.end())
            return {m_EntityMap.at(uuid), this};

        return {};
    }

    void Scene::OnPhysics2DStart()
    {
        // Box2D physics
        auto  sceneView = m_Registry.view<Box2DWorldComponent>();
        auto& world     = m_Registry.get<Box2DWorldComponent>(sceneView.front()).World;

        auto view = m_Registry.view<RigidBody2DComponent>();
        for (auto e : view)
        {
            Entity entity    = {e, this};
            UUID   entityID  = entity.GetComponent<IDComponent>().ID;
            auto&  transform = entity.GetComponent<TransformComponent>();
            auto&  rb2d      = entity.GetComponent<RigidBody2DComponent>();

            b2BodyDef bodyDef;
            bodyDef.type = Utils::Rigidbody2DTypeToBox2DBody(rb2d.Type);
            bodyDef.position.Set(transform.Translation.x, transform.Translation.y);
            bodyDef.angle = transform.GetRotationEuler().z;

            b2Body* body = world->CreateBody(&bodyDef);
            body->SetFixedRotation(rb2d.FixedRotation);
            b2MassData massData = body->GetMassData();
            massData.mass       = rb2d.Mass;
            body->SetMassData(&massData);
            body->SetGravityScale(rb2d.GravityScale);
            body->SetLinearDamping(rb2d.LinearDrag);
            body->SetAngularDamping(rb2d.AngularDrag);
            body->SetBullet(rb2d.IsBullet);
            body->GetUserData().pointer = (uintptr_t) new UUID(entityID);
            rb2d.RuntimeBody            = body;

            if (entity.HasComponent<BoxCollider2DComponent>())
            {
                auto& boxCollider2D = entity.GetComponent<BoxCollider2DComponent>();

                b2PolygonShape boxShape;
                boxShape.SetAsBox(boxCollider2D.Size.x * transform.Scale.x,
                                  boxCollider2D.Size.y * transform.Scale.y,
                                  b2Vec2(boxCollider2D.Offset.x, boxCollider2D.Offset.y),
                                  0.0f);

                b2FixtureDef fixtureDef;
                fixtureDef.shape                = &boxShape;
                fixtureDef.density              = boxCollider2D.Density;
                fixtureDef.friction             = boxCollider2D.Friction;
                fixtureDef.restitution          = boxCollider2D.Restitution;
                fixtureDef.restitutionThreshold = boxCollider2D.RestitutionThreshold;
                body->CreateFixture(&fixtureDef);
            }

            if (entity.HasComponent<CircleCollider2DComponent>())
            {
                auto& circleCollider2D = entity.GetComponent<CircleCollider2DComponent>();

                b2CircleShape circleShape;
                circleShape.m_p.Set(circleCollider2D.Offset.x, circleCollider2D.Offset.y);
                circleShape.m_radius = transform.Scale.x * circleCollider2D.Radius;

                b2FixtureDef fixtureDef;
                fixtureDef.shape                = &circleShape;
                fixtureDef.density              = circleCollider2D.Density;
                fixtureDef.friction             = circleCollider2D.Friction;
                fixtureDef.restitution          = circleCollider2D.Restitution;
                fixtureDef.restitutionThreshold = circleCollider2D.RestitutionThreshold;
                body->CreateFixture(&fixtureDef);
            }
        }

        // PhysX physics
        auto            physxView  = m_Registry.view<PhysXSceneComponent>();
        physx::PxScene* physxWorld = m_Registry.get<PhysXSceneComponent>(physxView.front()).World;

        auto rigidBodyComponentView = m_Registry.view<RigidBodyComponent>();
        for (auto e : rigidBodyComponentView)
        {
            Entity entity             = {e, this};
            UUID   entityID           = entity.GetComponent<IDComponent>().ID;
            auto&  transform          = entity.GetComponent<TransformComponent>();
            auto&  rigidBodyComponent = entity.GetComponent<RigidBodyComponent>();

            physx::PxRigidActor* actor =
                PhysicsScene::CreateAndAddActor(physxWorld, rigidBodyComponent, transform.GetTransform());
            GZ_CORE_ASSERT(actor);
            actor->userData                 = (void*)new UUID(entityID);
            rigidBodyComponent.RuntimeActor = actor;

            // Setup Collision Filters
            if (rigidBodyComponent.BodyType == RigidBodyComponent::Type::Static)
                PhysicsScene::SetCollisionFilters(actor, (uint32_t)FilterGroup::Static, (uint32_t)FilterGroup::All);
            else if (rigidBodyComponent.BodyType == RigidBodyComponent::Type::Dynamic)
                PhysicsScene::SetCollisionFilters(actor, (uint32_t)FilterGroup::Dynamic, (uint32_t)FilterGroup::All);

            if (entity.HasComponent<BoxColliderComponent>())
            {
                auto&                boxCollider     = entity.GetComponent<BoxColliderComponent>();
                auto&                physicsMaterial = entity.GetComponent<PhysicsMaterialComponent>();
                physx::PxBoxGeometry boxGeometry =
                    physx::PxBoxGeometry(boxCollider.HalfSize.x, boxCollider.HalfSize.y, boxCollider.HalfSize.z);
                physx::PxMaterial* material = PhysicsScene::CreateMaterial(
                    physicsMaterial.StaticFriction, physicsMaterial.DynamicFriction, physicsMaterial.Bounciness);
                physx::PxShape* shape = physx::PxRigidActorExt::createExclusiveShape(*actor, boxGeometry, *material);
                shape->setLocalPose(PhysicsScene::CreatePose(glm::translate(glm::mat4(1.0F), boxCollider.Offset)));
            }

            if (entity.HasComponent<SphereColliderComponent>())
            {
                auto&                   sphereCollider  = entity.GetComponent<SphereColliderComponent>();
                auto&                   physicsMaterial = entity.GetComponent<PhysicsMaterialComponent>();
                physx::PxSphereGeometry sphereGeometry  = physx::PxSphereGeometry(sphereCollider.Radius);
                physx::PxMaterial*      material        = PhysicsScene::CreateMaterial(
                    physicsMaterial.StaticFriction, physicsMaterial.DynamicFriction, physicsMaterial.Bounciness);
                physx::PxRigidActorExt::createExclusiveShape(*actor, sphereGeometry, *material);

                physx::PxRigidDynamic* rigidBodyActor = actor->is<physx::PxRigidDynamic>();
                if (rigidBodyActor)
                {
                    rigidBodyActor->setRigidDynamicLockFlag(physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_X, true);
                    rigidBodyActor->setRigidDynamicLockFlag(physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_Y, true);
                    rigidBodyActor->setRigidDynamicLockFlag(physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_Z, true);
                }
            }

            if (entity.HasComponent<CapsuleColliderComponent>())
            {
                auto&                    capsuleCollider = entity.GetComponent<CapsuleColliderComponent>();
                auto&                    physicsMaterial = entity.GetComponent<PhysicsMaterialComponent>();
                physx::PxCapsuleGeometry capsuleGeometry =
                    physx::PxCapsuleGeometry(capsuleCollider.Radius, capsuleCollider.Height / 2.0F);
                physx::PxMaterial* material = PhysicsScene::CreateMaterial(
                    physicsMaterial.StaticFriction, physicsMaterial.DynamicFriction, physicsMaterial.Bounciness);
                physx::PxShape* shape =
                    physx::PxRigidActorExt::createExclusiveShape(*actor, capsuleGeometry, *material);

                // Make sure that the capsule is facing up (+Y)
                shape->setLocalPose(physx::PxTransform(physx::PxQuat(physx::PxHalfPi, physx::PxVec3(0, 0, 1))));
            }
        }
    }

    void Scene::OnPhysics2DStop()
    {
        auto physxView = m_Registry.view<PhysXSceneComponent>();
        m_Registry.get<PhysXSceneComponent>(m_SceneEntity).World->release();
    }

    void Scene::RenderScene(EditorCamera& camera)
    {
        Renderer2D::BeginScene(camera);

        // Draw sprites
        {
            auto view = m_Registry.view<TransformComponent, SpriteRendererComponent>();
            for (auto entity : view)
            {
                auto [transform, sprite] = view.get<TransformComponent, SpriteRendererComponent>(entity);
                Renderer2D::DrawSprite(transform.GetTransform(), sprite, (int)entity);
            }
        }

        // Draw circles
        {
            auto view = m_Registry.view<TransformComponent, CircleRendererComponent>();
            for (auto entity : view)
            {
                auto [transform, circle] = view.get<TransformComponent, CircleRendererComponent>(entity);

                Renderer2D::DrawCircle(
                    transform.GetTransform(), circle.Color, circle.Thickness, circle.Fade, (int)entity);
            }
        }

        // Draw text
        {
            auto view = m_Registry.view<TransformComponent, TextComponent>();
            for (auto entity : view)
            {
                auto [transform, text] = view.get<TransformComponent, TextComponent>(entity);

                Renderer2D::DrawString(text.TextString, transform.GetTransform(), text, (int)entity);
            }
        }

        Renderer2D::EndScene();
    }

    template<typename T>
    void Scene::OnComponentAdded(Entity entity, T& component)
    {
        static_assert(sizeof(T) == 0);
    }

    template<>
    void Scene::OnComponentAdded<IDComponent>(Entity entity, IDComponent& component)
    {}

    template<>
    void Scene::OnComponentAdded<TransformComponent>(Entity entity, TransformComponent& component)
    {}

    template<>
    void Scene::OnComponentAdded<CameraComponent>(Entity entity, CameraComponent& component)
    {
        if (m_ViewportWidth > 0 && m_ViewportHeight > 0)
            component.Camera.SetViewportSize(m_ViewportWidth, m_ViewportHeight);
    }

    template<>
    void Scene::OnComponentAdded<ScriptComponent>(Entity entity, ScriptComponent& component)
    {}

    template<>
    void Scene::OnComponentAdded<SpriteRendererComponent>(Entity entity, SpriteRendererComponent& component)
    {}

    template<>
    void Scene::OnComponentAdded<TagComponent>(Entity entity, TagComponent& component)
    {}

    template<>
    void Scene::OnComponentAdded<NativeScriptComponent>(Entity entity, NativeScriptComponent& component)
    {}

    template<>
    void Scene::OnComponentAdded<RigidBody2DComponent>(Entity entity, RigidBody2DComponent& component)
    {}

    template<>
    void Scene::OnComponentAdded<BoxCollider2DComponent>(Entity entity, BoxCollider2DComponent& component)
    {}

    template<>
    void Scene::OnComponentAdded<CircleRendererComponent>(Entity entity, CircleRendererComponent& component)
    {}

    template<>
    void Scene::OnComponentAdded<CircleCollider2DComponent>(Entity entity, CircleCollider2DComponent& component)
    {}

    template<>
    void Scene::OnComponentAdded<RigidBodyComponent>(Entity entity, RigidBodyComponent& component)
    {}

    template<>
    void Scene::OnComponentAdded<PhysicsMaterialComponent>(Entity entity, PhysicsMaterialComponent& component)
    {}

    template<>
    void Scene::OnComponentAdded<BoxColliderComponent>(Entity entity, BoxColliderComponent& component)
    {}

    template<>
    void Scene::OnComponentAdded<SphereColliderComponent>(Entity entity, SphereColliderComponent& component)
    {}

    template<>
    void Scene::OnComponentAdded<CapsuleColliderComponent>(Entity entity, CapsuleColliderComponent& component)
    {}

    template<>
    void Scene::OnComponentAdded<TextComponent>(Entity entity, TextComponent& component)
    {}

    template<>
    void Scene::OnComponentAdded<SceneComponent>(Entity entity, SceneComponent& component)
    {}

    template<>
    void Scene::OnComponentAdded<PhysXSceneComponent>(Entity entity, PhysXSceneComponent& component)
    {}

    void Scene::OnViewportResize(uint32_t width, uint32_t height)
    {
        if (m_ViewportWidth == width && m_ViewportHeight == height)
            return;

        m_ViewportWidth  = width;
        m_ViewportHeight = height;

        // Resize our non-FixedAspectRatio cameras
        auto view = m_Registry.view<CameraComponent>();
        for (auto entity : view)
        {
            auto& cameraComponent = view.get<CameraComponent>(entity);
            if (!cameraComponent.FixedAspectRatio)
                cameraComponent.Camera.SetViewportSize(width, height);
        }
    }

    Entity Scene::GetPrimaryCameraEntity()
    {
        auto view = m_Registry.view<CameraComponent>();
        for (auto entity : view)
        {
            const auto& camera = view.get<CameraComponent>(entity);
            if (camera.Primary)
                return Entity {entity, this};
        }
        return {};
    }

} // namespace Gaze