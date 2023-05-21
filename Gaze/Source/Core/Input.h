#ifndef GAZE_ENGINE_INPUT_H
#define GAZE_ENGINE_INPUT_H

#include "Core.h"
#include "KeyCodes.h"
#include "MouseCodes.h"

#include <glm/glm.hpp>

namespace Gaze {

    class Input {
    public:
        static bool IsKeyPressed(KeyCode key);

        static bool IsMouseButtonPressed(MouseCode button);

        static glm::vec2 GetMousePosition();

        static float GetMouseX();

        static float GetMouseY();
    };
}

#endif //GAZE_ENGINE_INPUT_H
