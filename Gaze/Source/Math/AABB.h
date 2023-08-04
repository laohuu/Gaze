#ifndef GAZE_ENGINE_AABB_H
#define GAZE_ENGINE_AABB_H

#include <glm/glm.hpp>

namespace Gaze
{
    struct AABB
    {
        glm::vec3 Min, Max;

        AABB() : Min(0.0f), Max(0.0f) {}

        AABB(const glm::vec3& min, const glm::vec3& max) : Min(min), Max(max) {}
    };
} // namespace Gaze

#endif // GAZE_ENGINE_AABB_H
