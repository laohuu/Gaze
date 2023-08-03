#ifndef GAZE_ENGINE_TEXTUREIMPORTER_H
#define GAZE_ENGINE_TEXTUREIMPORTER_H

#include "Renderer/Texture.h"

#include <filesystem>

namespace Gaze
{
    class TextureImporter
    {
    public:
        static Buffer ToBufferFromFile(const std::filesystem::path& path,
                                       ImageFormat&                 outFormat,
                                       uint32_t&                    outWidth,
                                       uint32_t&                    outHeight);
        static Buffer
        ToBufferFromMemory(Buffer buffer, ImageFormat& outFormat, uint32_t& outWidth, uint32_t& outHeight);

    private:
        const std::filesystem::path m_Path;
    };
} // namespace Gaze

#endif // GAZE_ENGINE_TEXTUREIMPORTER_H
