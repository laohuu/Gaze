#include "Texture.h"
#include "GazePCH.h"

#include "Platform/OpenGL/OpenGLTexture.h"
#include "Renderer/Renderer.h"

namespace Gaze
{

    Ref<Texture2D> Texture2D::Create(const TextureSpecification& specification)
    {
        switch (RendererAPI::Current())
        {
            case RendererAPIType::None:
                GZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
                return nullptr;
            case RendererAPIType::OpenGL:
                return Ref<OpenGLTexture2D>::Create(specification);
        }

        GZ_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

    Ref<Texture2D> Texture2D::Create(const std::string& path, bool srgb)
    {
        switch (RendererAPI::Current())
        {
            case RendererAPIType::None:
                GZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
                return nullptr;
            case RendererAPIType::OpenGL:
                return Ref<OpenGLTexture2D>::Create(path, srgb);
        }

        GZ_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

    Ref<TextureCube> TextureCube::Create(const TextureSpecification& specification)
    {
        switch (RendererAPI::Current())
        {
            case RendererAPIType::None:
                GZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
                return nullptr;
            case RendererAPIType::OpenGL:
                return nullptr;
        }

        GZ_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

    Ref<TextureCube> TextureCube::Create(const std::string& path)
    {
        switch (RendererAPI::Current())
        {
            case RendererAPIType::None:
                GZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
                return nullptr;
            case RendererAPIType::OpenGL:
                return nullptr;
        }

        GZ_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

    uint32_t Texture::GetBPP(ImageFormat format)
    {
        switch (format)
        {
            case ImageFormat::RGB:
                return 3;
            case ImageFormat::RGBA:
                return 4;
        }
        return 0;
    }

    uint32_t Texture::CalculateMipMapCount(uint32_t width, uint32_t height)
    {
        uint32_t levels = 1;
        while ((width | height) >> levels)
            levels++;

        return levels;
    }

} // namespace Gaze