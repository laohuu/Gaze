#include "GazePCH.h"
#include "Entity.h"

namespace Gaze {

    Entity::Entity(entt::entity handle, Scene *scene) : m_EntityHandle(handle), m_Scene(scene) {

    }

} // Gaze