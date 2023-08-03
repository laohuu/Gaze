#include "GazePCH.h"

#include "Core/FileSystem.h"

namespace Gaze
{
    Buffer FileSystem::ReadBytes(const std::filesystem::path& filepath)
    {
        Buffer buffer;

        std::ifstream stream(filepath, std::ios::binary | std::ios::ate);
        GZ_CORE_ASSERT(stream);

        auto end = stream.tellg();
        stream.seekg(0, std::ios::beg);
        auto size = end - stream.tellg();
        GZ_CORE_ASSERT(size != 0);

        buffer.Allocate((uint32_t)size);
        stream.read((char*)buffer.Data, buffer.Size);
        stream.close();

        return buffer;
    }
} // namespace Gaze