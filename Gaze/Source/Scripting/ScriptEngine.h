#ifndef GAZE_ENGINE_SCRIPTENGINE_H
#define GAZE_ENGINE_SCRIPTENGINE_H

namespace Gaze {

    class ScriptEngine {
    public:
        static void Init();

        static void Shutdown();

    private:
        static void InitMono();

        static void ShutdownMono();
    };

} // Gaze

#endif //GAZE_ENGINE_SCRIPTENGINE_H
