#include "GazePCH.h"

#include "PhysicsSystem.h"

namespace Gaze
{
    void PhysicsSystem::Init() {}
    void PhysicsSystem::Shutdown() {}

    void PhysicsSystem::OnEvent(Event& event) { EventDispatcher dispatcher(event); }
} // namespace Gaze