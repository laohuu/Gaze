#ifndef GAZE_ENGINE_COMPONENTS_H
#define GAZE_ENGINE_COMPONENTS_H

#include "Core/UUID.h"
#include "Math/Math.h"
#include "Physics/3D/PhysicsTypes.h"
#include "Renderer/Camera.h"
#include "Renderer/Font.h"
#include "Renderer/Texture.h"
#include "SceneCamera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

namespace Gaze
{

    struct IDComponent
    {
        UUID ID;

        IDComponent()                   = default;
        IDComponent(const IDComponent&) = default;
    };

    struct TagComponent
    {
        std::string Tag;

        TagComponent()                    = default;
        TagComponent(const TagComponent&) = default;
        TagComponent(const std::string& tag) : Tag(tag) {}
    };

    struct TransformComponent
    {
        glm::vec3 Translation = {0.0f, 0.0f, 0.0f};
        glm::vec3 Scale       = {1.0f, 1.0f, 1.0f};

    private:
        // These are private so that you are forced to set them via
        // SetRotation() or SetRotationEuler()
        // This avoids situation where one of them gets set and the other is forgotten.
        glm::vec3 RotationEuler = {0.0f, 0.0f, 0.0f};
        glm::quat Rotation      = {1.0f, 0.0f, 0.0f, 0.0f};

    public:
        TransformComponent()                          = default;
        TransformComponent(const TransformComponent&) = default;
        TransformComponent(const glm::vec3& translation) : Translation(translation) {}

        glm::mat4 GetTransform() const
        {
            return glm::translate(glm::mat4(1.0f), Translation) * glm::toMat4(Rotation) *
                   glm::scale(glm::mat4(1.0f), Scale);
        }

        void SetTransform(const glm::mat4& transform)
        {
            Math::DecomposeTransform(transform, Translation, Rotation, Scale);
            RotationEuler = glm::eulerAngles(Rotation);
        }

        glm::vec3 GetRotationEuler() const { return RotationEuler; }

        void SetRotationEuler(const glm::vec3& euler)
        {
            RotationEuler = euler;
            Rotation      = glm::quat(RotationEuler);
        }

        glm::quat GetRotation() const { return Rotation; }

        void SetRotation(const glm::quat& quat)
        {
            Rotation      = quat;
            RotationEuler = glm::eulerAngles(Rotation);
        }

        friend class SceneSerializer;
    };

    struct SpriteRendererComponent
    {
        glm::vec4      Color {1.0f, 1.0f, 1.0f, 1.0f};
        Ref<Texture2D> Texture;
        float          TilingFactor = 1.0f;

        SpriteRendererComponent()                               = default;
        SpriteRendererComponent(const SpriteRendererComponent&) = default;
        SpriteRendererComponent(const glm::vec4& color) : Color(color) {}
    };

    struct CircleRendererComponent
    {
        glm::vec4 Color {1.0f, 1.0f, 1.0f, 1.0f};
        float     Thickness = 1.0f;
        float     Fade      = 0.005f;

        CircleRendererComponent()                               = default;
        CircleRendererComponent(const CircleRendererComponent&) = default;
    };

    struct CameraComponent
    {
        SceneCamera Camera;
        bool        Primary          = true; // TODO: think about moving to Scene
        bool        FixedAspectRatio = false;

        CameraComponent()                       = default;
        CameraComponent(const CameraComponent&) = default;
    };

    struct ScriptComponent
    {
        std::string ClassName;

        ScriptComponent()                       = default;
        ScriptComponent(const ScriptComponent&) = default;
    };

    // Forward declaration
    class ScriptableEntity;

    struct NativeScriptComponent
    {
        ScriptableEntity* Instance = nullptr;

        ScriptableEntity* (*InstantiateScript)();
        void (*DestroyScript)(NativeScriptComponent*);

        template<typename T>
        void Bind()
        {
            InstantiateScript = []() { return static_cast<ScriptableEntity*>(new T()); };
            DestroyScript     = [](NativeScriptComponent* nsc) {
                delete nsc->Instance;
                nsc->Instance = nullptr;
            };
        }
    };

    // Physics

    struct RigidBody2DComponent
    {
        enum class BodyType
        {
            Static = 0,
            Dynamic,
            Kinematic
        };
        BodyType Type          = BodyType::Static;
        bool     FixedRotation = false;
        float    Mass          = 1.0f;
        float    LinearDrag    = 0.01f;
        float    AngularDrag   = 0.05f;
        float    GravityScale  = 1.0f;
        bool     IsBullet      = false;

        // Storage for runtime
        void* RuntimeBody = nullptr;

        RigidBody2DComponent()                            = default;
        RigidBody2DComponent(const RigidBody2DComponent&) = default;
    };

    struct BoxCollider2DComponent
    {
        glm::vec2 Offset = {0.0f, 0.0f};
        glm::vec2 Size   = {0.5f, 0.5f};

        float Density              = 1.0f;
        float Friction             = 0.5f;
        float Restitution          = 0.0f;
        float RestitutionThreshold = 0.5f;

        // Storage for runtime
        void* RuntimeFixture = nullptr;

        BoxCollider2DComponent()                              = default;
        BoxCollider2DComponent(const BoxCollider2DComponent&) = default;
    };

    struct CircleCollider2DComponent
    {
        glm::vec2 Offset = {0.0f, 0.0f};
        float     Radius = 0.5f;

        float Density              = 1.0f;
        float Friction             = 0.5f;
        float Restitution          = 0.0f;
        float RestitutionThreshold = 0.5f;

        // Storage for runtime
        void* RuntimeFixture = nullptr;

        CircleCollider2DComponent()                                 = default;
        CircleCollider2DComponent(const CircleCollider2DComponent&) = default;
    };

    struct TextComponent
    {
        std::string TextString;
        Ref<Font>   FontAsset = Font::GetDefault();
        glm::vec4   Color {1.0f};
        float       Kerning     = 0.0f;
        float       LineSpacing = 0.0f;
    };

    struct RigidBodyComponent
    {
        enum class Type
        {
            None   = 0,
            Static = 1,
            Dynamic
        };

        Type     BodyType     = Type::Static;
        void*    RuntimeActor = nullptr;

        float                  Mass               = 1.0f;
        float                  LinearDrag         = 0.01f;
        float                  AngularDrag        = 0.05f;
        bool                   DisableGravity     = false;
        bool                   IsKinematic        = false;
        CollisionDetectionType CollisionDetection = CollisionDetectionType::Discrete;

        uint8_t LockFlags = 0;

        RigidBodyComponent()                                = default;
        RigidBodyComponent(const RigidBodyComponent& other) = default;
    };

    // TODO: This will eventually be a resource, but that requires object referencing through the editor
    struct PhysicsMaterialComponent
    {
        float StaticFriction  = 1.0F;
        float DynamicFriction = 1.0F;
        float Bounciness      = 1.0F;

        PhysicsMaterialComponent()                                      = default;
        PhysicsMaterialComponent(const PhysicsMaterialComponent& other) = default;
    };

    struct BoxColliderComponent
    {
        glm::vec3 HalfSize  = {0.5f, 0.5f, 0.5f};
        glm::vec3 Offset    = {0.0f, 0.0f, 0.0f};
        bool      IsTrigger = false;

        BoxColliderComponent()                                  = default;
        BoxColliderComponent(const BoxColliderComponent& other) = default;
    };

    struct SphereColliderComponent
    {
        float     Radius    = 0.5f;
        glm::vec3 Offset    = {0.0f, 0.0f, 0.0f};
        bool      IsTrigger = false;

        SphereColliderComponent()                                     = default;
        SphereColliderComponent(const SphereColliderComponent& other) = default;
    };

    struct CapsuleColliderComponent
    {
        float     Radius    = 0.5f;
        float     Height    = 1.0f;
        glm::vec3 Offset    = {0.0f, 0.0f, 0.0f};
        bool      IsTrigger = false;

        CapsuleColliderComponent()                                      = default;
        CapsuleColliderComponent(const CapsuleColliderComponent& other) = default;
    };

    template<typename... Component>
    struct ComponentGroup
    {};

    using AllComponents = ComponentGroup<TransformComponent,
                                         SpriteRendererComponent,
                                         CircleRendererComponent,
                                         CameraComponent,
                                         ScriptComponent,
                                         NativeScriptComponent,
                                         RigidBody2DComponent,
                                         BoxCollider2DComponent,
                                         CircleCollider2DComponent,
                                         RigidBodyComponent,
                                         PhysicsMaterialComponent,
                                         BoxColliderComponent,
                                         SphereColliderComponent,
                                         CapsuleColliderComponent,
                                         TextComponent>;

} // namespace Gaze
#endif // GAZE_ENGINE_COMPONENTS_H
