#ifndef GAZE_ENGINE_PHYSICS2D_H
#define GAZE_ENGINE_PHYSICS2D_H

#include "Scene/Components.h"

#include "box2d/b2_body.h"

namespace Gaze::Utils
{

    inline b2BodyType Rigidbody2DTypeToBox2DBody(RigidBody2DComponent::BodyType bodyType)
    {
        switch (bodyType)
        {
            case RigidBody2DComponent::BodyType::Static:
                return b2_staticBody;
            case RigidBody2DComponent::BodyType::Dynamic:
                return b2_dynamicBody;
            case RigidBody2DComponent::BodyType::Kinematic:
                return b2_kinematicBody;
        }

        GZ_CORE_ASSERT(false, "Unknown body type");
        return b2_staticBody;
    }

    inline RigidBody2DComponent::BodyType Rigidbody2DTypeFromBox2DBody(b2BodyType bodyType)
    {
        switch (bodyType)
        {
            case b2_staticBody:
                return RigidBody2DComponent::BodyType::Static;
            case b2_dynamicBody:
                return RigidBody2DComponent::BodyType::Dynamic;
            case b2_kinematicBody:
                return RigidBody2DComponent::BodyType::Kinematic;
        }

        GZ_CORE_ASSERT(false, "Unknown body type");
        return RigidBody2DComponent::BodyType::Static;
    }

} // namespace Gaze::Utils

namespace Gaze
{
    struct Box2DWorldComponent
    {
        std::unique_ptr<b2World> World;
    };
} // namespace Gaze

#endif // GAZE_ENGINE_PHYSICS2D_H
