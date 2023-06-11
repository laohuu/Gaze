#ifndef GAZE_ENGINE_PLATFORMUTILS_H
#define GAZE_ENGINE_PLATFORMUTILS_H

#include <string>

namespace Gaze {

    class FileDialogs {
    public:
        // These return empty strings if cancelled
        static std::string OpenFile(const char *filter);

        static std::string SaveFile(const char *filter);
    };

    class Time {
    public:
        static float GetTime();
    };
}

#endif //GAZE_ENGINE_PLATFORMUTILS_H
