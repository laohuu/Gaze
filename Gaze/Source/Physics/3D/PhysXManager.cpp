#include "GazePCH.h"

#include "PhysXManager.h"

namespace Gaze
{
    void PhysXManager::Init()
    {
        GZ_CORE_ASSERT(!s_PXFoundation, "PhysXManager::Init shouldn't be called more than once!");

        s_PXFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, s_PXAllocator, s_PXErrorCallback);
        GZ_CORE_ASSERT(s_PXFoundation, "PxCreateFoundation Failed!");

        s_PXPhysicsFactory = PxCreatePhysics(PX_PHYSICS_VERSION, *s_PXFoundation, physx::PxTolerancesScale(), true);
        GZ_CORE_ASSERT(s_PXPhysicsFactory, "PxCreatePhysics Failed!");
    }

    void PhysXManager::Shutdown()
    {
        s_PXPhysicsFactory->release();
        s_PXFoundation->release();
    }

    physx::PxSceneDesc PhysXManager::CreateSceneDesc()
    {
        return physx::PxSceneDesc(s_PXPhysicsFactory->getTolerancesScale());
    }

    physx::PxScene* PhysXManager::CreateScene(const physx::PxSceneDesc& sceneDesc)
    {
        return s_PXPhysicsFactory->createScene(sceneDesc);
    }

    physx::PxDefaultErrorCallback PhysXManager::s_PXErrorCallback;
    physx::PxDefaultAllocator     PhysXManager::s_PXAllocator;
    physx::PxFoundation*          PhysXManager::s_PXFoundation;
    physx::PxPhysics*             PhysXManager::s_PXPhysicsFactory;
} // namespace Gaze