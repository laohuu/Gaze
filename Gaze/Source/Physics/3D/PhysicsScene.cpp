#include "GazePCH.h"

#include "PhysXUtils.h"
#include "PhysicsScene.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/matrix_decompose.hpp>

namespace Gaze
{
    static physx::PxSimulationFilterShader s_DefaultFilterShader = physx::PxDefaultSimulationFilterShader;

    static std::tuple<glm::vec3, glm::quat, glm::vec3> GetTransformDecomposition(const glm::mat4& transform)
    {
        glm::vec3 scale, translation, skew;
        glm::vec4 perspective;
        glm::quat orientation;
        glm::decompose(transform, scale, orientation, translation, skew, perspective);

        return {translation, orientation, scale};
    }

    static physx::PxFilterFlags EngineFilterShader(physx::PxFilterObjectAttributes attributes0,
                                                   physx::PxFilterData             filterData0,
                                                   physx::PxFilterObjectAttributes attributes1,
                                                   physx::PxFilterData             filterData1,
                                                   physx::PxPairFlags&             pairFlags,
                                                   const void*                     constantBlock,
                                                   physx::PxU32                    constantBlockSize)
    {
        if (physx::PxFilterObjectIsTrigger(attributes0) || physx::PxFilterObjectIsTrigger(attributes1))
        {
            pairFlags = physx::PxPairFlag::eTRIGGER_DEFAULT;
            return physx::PxFilterFlag::eDEFAULT;
        }

        pairFlags = physx::PxPairFlag::eCONTACT_DEFAULT;

        if ((filterData0.word0 & filterData1.word1) || (filterData1.word0 & filterData0.word1))
        {
            pairFlags |= physx::PxPairFlag::eNOTIFY_TOUCH_FOUND;
            pairFlags |= physx::PxPairFlag::eNOTIFY_TOUCH_LOST;
        }

        return physx::PxFilterFlag::eDEFAULT;
    }

    void PhysicsScene::Init()
    {
        GZ_CORE_ASSERT(!s_PXFoundation, "PhysXManager::Init shouldn't be called more than once!");

        s_PXFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, s_PXAllocator, s_PXErrorCallback);
        GZ_CORE_ASSERT(s_PXFoundation, "PxCreateFoundation Failed!");

#if PHYSX_DEBUGGER
        s_PXPvd                          = PxCreatePvd(*s_PXFoundation);
        physx::PxPvdTransport* transport = physx::PxDefaultPvdSocketTransportCreate("localhost", 5425, 10);
        s_PXPvd->connect(*transport, physx::PxPvdInstrumentationFlag::eALL);
#endif
        s_PXPhysicsFactory =
            PxCreatePhysics(PX_PHYSICS_VERSION, *s_PXFoundation, physx::PxTolerancesScale(), true, s_PXPvd);
        GZ_CORE_ASSERT(s_PXPhysicsFactory, "PxCreatePhysics Failed!");
    }

    void PhysicsScene::Shutdown()
    {
        s_PXPhysicsFactory->release();
        s_PXFoundation->release();
    }

    physx::PxSceneDesc PhysicsScene::CreateSceneDesc()
    {
        physx::PxSceneDesc sceneDesc(s_PXPhysicsFactory->getTolerancesScale());
        if (!sceneDesc.cpuDispatcher)
        {
            physx::PxDefaultCpuDispatcher* mCpuDispatcher = physx::PxDefaultCpuDispatcherCreate(1);
            if (!mCpuDispatcher)
                GZ_CORE_ASSERT(false);
            sceneDesc.cpuDispatcher = mCpuDispatcher;
        }

        if (!sceneDesc.filterShader)
            sceneDesc.filterShader = EngineFilterShader;

        return sceneDesc;
    }

    physx::PxScene* PhysicsScene::CreateScene(const physx::PxSceneDesc& sceneDesc)
    {
        return s_PXPhysicsFactory->createScene(sceneDesc);
    }

    physx::PxRigidActor* PhysicsScene::CreateAndAddActor(physx::PxScene*           scene,
                                                         const RigidBodyComponent& rigidbody,
                                                         const glm::mat4&          transform)
    {
        physx::PxRigidActor* actor = nullptr;

        if (rigidbody.BodyType == RigidBodyComponent::Type::Static)
        {
            actor = s_PXPhysicsFactory->createRigidStatic(CreatePose(transform));
        }
        else if (rigidbody.BodyType == RigidBodyComponent::Type::Dynamic)
        {
            physx::PxRigidDynamic* dynamicActor = s_PXPhysicsFactory->createRigidDynamic(CreatePose(transform));
            physx::PxRigidBodyExt::updateMassAndInertia(*dynamicActor, rigidbody.Mass);

            dynamicActor->setRigidDynamicLockFlag(physx::PxRigidDynamicLockFlag::eLOCK_LINEAR_X,
                                                  rigidbody.LockFlags & (uint8_t)ActorLockFlag::TranslationX);
            dynamicActor->setRigidDynamicLockFlag(physx::PxRigidDynamicLockFlag::eLOCK_LINEAR_Y,
                                                  rigidbody.LockFlags & (uint8_t)ActorLockFlag::TranslationY);
            dynamicActor->setRigidDynamicLockFlag(physx::PxRigidDynamicLockFlag::eLOCK_LINEAR_Z,
                                                  rigidbody.LockFlags & (uint8_t)ActorLockFlag::TranslationZ);
            dynamicActor->setRigidDynamicLockFlag(physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_X,
                                                  rigidbody.LockFlags & (uint8_t)ActorLockFlag::RotationX);
            dynamicActor->setRigidDynamicLockFlag(physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_Y,
                                                  rigidbody.LockFlags & (uint8_t)ActorLockFlag::RotationY);
            dynamicActor->setRigidDynamicLockFlag(physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_Z,
                                                  rigidbody.LockFlags & (uint8_t)ActorLockFlag::RotationZ);

            actor = dynamicActor;
        }

        scene->addActor(*actor);

        return actor;
    }

    physx::PxMaterial* PhysicsScene::CreateMaterial(float staticFriction, float dynamicFriction, float restitution)
    {
        return s_PXPhysicsFactory->createMaterial(staticFriction, dynamicFriction, restitution);
    }

    physx::PxTransform PhysicsScene::CreatePose(const glm::mat4& transform)
    {
        auto [translation, rotationQuat, scale] = GetTransformDecomposition(transform);
        glm::vec3 rotation                      = glm::eulerAngles(rotationQuat);

        physx::PxTransform physxTransform(physx::PxVec3(translation.x, translation.y, translation.z));
        physxTransform.rotate(physx::PxVec3(rotation.x, rotation.y, rotation.z));
        return physxTransform;
    }

    void PhysicsScene::SetCollisionFilters(physx::PxRigidActor* actor, uint32_t filterGroup, uint32_t filterMask)
    {
        physx::PxFilterData filterData;
        filterData.word0 = filterGroup; // word0 = own ID
        filterData.word1 = filterMask;  // word1 = ID mask to filter pairs that trigger a
                                        // contact callback;
        const physx::PxU32 numShapes = actor->getNbShapes();
        physx::PxShape**   shapes =
            (physx::PxShape**)s_PXAllocator.allocate(sizeof(physx::PxShape*) * numShapes, "", "", 0);
        actor->getShapes(shapes, numShapes);
        for (physx::PxU32 i = 0; i < numShapes; i++)
        {
            physx::PxShape* shape = shapes[i];
            shape->setSimulationFilterData(filterData);
        }
        s_PXAllocator.deallocate(shapes);
    }

    physx::PxDefaultErrorCallback PhysicsScene::s_PXErrorCallback;
    physx::PxDefaultAllocator     PhysicsScene::s_PXAllocator;
    physx::PxFoundation*          PhysicsScene::s_PXFoundation;
    physx::PxPhysics*             PhysicsScene::s_PXPhysicsFactory;
    physx::PxPvd*                 PhysicsScene::s_PXPvd;

} // namespace Gaze