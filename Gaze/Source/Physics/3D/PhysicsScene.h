#ifndef GAZE_ENGINE_PHYSICSSCENE_H
#define GAZE_ENGINE_PHYSICSSCENE_H

#include "Core/Base.h"
#include "PhysicsTypes.h"
#include "Scene/Components.h"

#include <PhysX/PxPhysicsAPI.h>

namespace Gaze
{
    enum class FilterGroup : uint32_t
    {
        Static    = BIT(0),
        Dynamic   = BIT(1),
        Kinematic = BIT(2),
        All       = Static | Dynamic | Kinematic
    };

    class PhysicsScene
    {
    public:
        PhysicsScene();
        ~PhysicsScene();

        static void Init();
        static void Shutdown();

        static physx::PxSceneDesc CreateSceneDesc();
        static physx::PxScene*    CreateScene(const physx::PxSceneDesc& sceneDesc);
        static physx::PxRigidActor*
        CreateAndAddActor(physx::PxScene* scene, const RigidBodyComponent& rigidbody, const glm::mat4& transform);
        static physx::PxMaterial* CreateMaterial(float staticFriction, float dynamicFriction, float restitution);

        static physx::PxTransform CreatePose(const glm::mat4& transform);

        static void SetCollisionFilters(physx::PxRigidActor* actor, uint32_t filterGroup, uint32_t filterMask);

    private:
        static physx::PxDefaultErrorCallback s_PXErrorCallback;
        static physx::PxDefaultAllocator     s_PXAllocator;
        static physx::PxFoundation*          s_PXFoundation;
        static physx::PxPhysics*             s_PXPhysicsFactory;
        static physx::PxPvd*                 s_PXPvd;
    };
} // namespace Gaze

#endif // GAZE_ENGINE_PHYSICSSCENE_H
