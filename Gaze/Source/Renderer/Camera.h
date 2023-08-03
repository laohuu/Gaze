#ifndef GAZE_ENGINE_CAMERA_H
#define GAZE_ENGINE_CAMERA_H

#include <glm/glm.hpp>

namespace Gaze
{

    class Camera
    {
    public:
        Camera() = default;
        Camera(const glm::mat4& projectionMatrix) : m_ProjectionMatrix(projectionMatrix) {}
        virtual ~Camera() = default;

        const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
        void SetProjectionMatrix(const glm::mat4& projectionMatrix) { m_ProjectionMatrix = projectionMatrix; }

        float  GetExposure() const { return m_Exposure; }
        float& GetExposure() { return m_Exposure; }

    protected:
        glm::mat4 m_ProjectionMatrix = glm::mat4(1.0f);
        float     m_Exposure         = 0.8f;
    };

} // namespace Gaze
#endif // GAZE_ENGINE_CAMERA_H
