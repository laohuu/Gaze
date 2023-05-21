#ifndef GAZE_WINDOWSINPUT_H
#define GAZE_WINDOWSINPUT_H


#include "Core/Input.h"

namespace Gaze {

    class WindowsInput : public Input {
    protected:
        virtual bool IsKeyPressedImpl(int keycode) override;

        virtual bool IsMouseButtonPressedImpl(int button) override;

        virtual std::pair<float, float> GetMousePositionImpl() override;

        virtual float GetMouseXImpl() override;

        virtual float GetMouseYImpl() override;
    };
}

#endif //GAZE_WINDOWSINPUT_H
