#ifndef GAZE_ENGINE_CORE_FILESYSTEM_H
#define GAZE_ENGINE_CORE_FILESYSTEM_H

#include "Core/Buffer.h"

namespace Gaze
{

    class FileSystem
    {
    public:
        static Buffer ReadBytes(const std::filesystem::path& filepath);
    };

} // namespace Gaze

#endif // GAZE_ENGINE_CORE_FILESYSTEM_H
