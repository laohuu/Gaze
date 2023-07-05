#ifndef GAZE_ENGINE_PHYSXMANAGER_H
#define GAZE_ENGINE_PHYSXMANAGER_H

#include "Core/Base.h"
#include <PhysX/PxPhysicsAPI.h>

namespace Gaze
{

    class PhysXManager
    {
    public:
        static void Init();
        static void Shutdown();

        static physx::PxSceneDesc CreateSceneDesc();
        static physx::PxScene*    CreateScene(const physx::PxSceneDesc& sceneDesc);

    private:
        static physx::PxDefaultErrorCallback s_PXErrorCallback;
        static physx::PxDefaultAllocator     s_PXAllocator;
        static physx::PxFoundation*          s_PXFoundation;
        static physx::PxPhysics*             s_PXPhysicsFactory;
    };

} // namespace Gaze

#endif // GAZE_ENGINE_PHYSXMANAGER_H
