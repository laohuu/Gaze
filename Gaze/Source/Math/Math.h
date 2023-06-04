#ifndef GAZE_ENGINE_MATH_H
#define GAZE_ENGINE_MATH_H

#include <glm/glm.hpp>

namespace Gaze::Math {

    bool DecomposeTransform(const glm::mat4 &transform, glm::vec3 &translation, glm::vec3 &rotation, glm::vec3 &scale);

}
#endif //GAZE_ENGINE_MATH_H
