#ifndef GAZE_ENGINE_TIMESTEP_H
#define GAZE_ENGINE_TIMESTEP_H

namespace Gaze {
    class Timestep {
    public:
        Timestep(float time = 0.0f)
                : m_Time(time) {
        }

        operator float() const { return m_Time; }

        float GetSeconds() const { return m_Time; }

        float GetMilliseconds() const { return m_Time * 1000.0f; }

    private:
        float m_Time;
    };
}

#endif //GAZE_ENGINE_TIMESTEP_H
