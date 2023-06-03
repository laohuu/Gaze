#ifndef GAZE_ENGINE_CAMERA_H
#define GAZE_ENGINE_CAMERA_H

#include <glm/glm.hpp>

namespace Gaze {

    class Camera {
    public:
        Camera() = default;

        Camera(const glm::mat4 &projection)
                : m_Projection(projection) {}

        const glm::mat4 &GetProjection() const { return m_Projection; }

    private:
        glm::mat4 m_Projection;
    };

}
#endif //GAZE_ENGINE_CAMERA_H
