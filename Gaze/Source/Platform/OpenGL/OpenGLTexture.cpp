#include "GazePCH.h"

#include "OpenGLImage.h"
#include "OpenGLTexture.h"

#include <stb_image.h>

namespace Gaze
{
    namespace Utils
    {
        static GLenum ImageFormatToOpenGLTextureFormat(ImageFormat format)
        {
            switch (format)
            {
                case ImageFormat::RGB:
                    return GL_RGB;
                case ImageFormat::RGBA:
                    return GL_RGBA;
                case ImageFormat::Float16:
                    return GL_RGBA16F;
            }
            GZ_CORE_ASSERT(false, "Unknown texture format!");
            return 0;
        }
    } // namespace Utils

    OpenGLTexture2D::OpenGLTexture2D(const TextureSpecification& specification, const void* data) :
        m_Specification(specification)
    {
        ImageSpecification imageSpecification;
        imageSpecification.Width  = specification.Width;
        imageSpecification.Height = specification.Height;
        imageSpecification.Format = specification.Format;
        m_Image                   = Image2D::Create(imageSpecification, data);
        m_Image->Invalidate();
        m_ImageData = m_Image->GetBuffer();
    }

    OpenGLTexture2D::OpenGLTexture2D(const std::string& path, bool srgb) : m_Path(path)
    {
        GZ_PROFILE_FUNCTION();

        int width, height, channels;
        stbi_set_flip_vertically_on_load(1);
        if (stbi_is_hdr(path.c_str()))
        {
            GZ_CORE_INFO("Loading HDR texture {0}, srgb={1}", path, srgb);
            float* imageData = stbi_loadf(path.c_str(), &width, &height, &channels, 0);
            GZ_CORE_ASSERT(imageData, "Could not read image!");
            Buffer             buffer(imageData, Utils::GetImageMemorySize(ImageFormat::RGBA32F, width, height));
            ImageSpecification imageSpecification;
            imageSpecification.Width  = width;
            imageSpecification.Height = height;
            imageSpecification.Format = ImageFormat::RGBA32F;

            m_Image                = Image2D::Create(imageSpecification, buffer);
            m_ImageData            = m_Image->GetBuffer();
            m_IsHDR                = true;
            m_Specification.Format = ImageFormat::RGBA32F;
        }
        else
        {
            GZ_CORE_INFO("Loading texture {0}, srgb={1}", path, srgb);
            stbi_uc* imageData = stbi_load(path.c_str(), &width, &height, &channels, srgb ? STBI_rgb : STBI_rgb_alpha);
            GZ_CORE_ASSERT(imageData, "Could not read image!");
            ImageFormat        format = srgb ? ImageFormat::RGB : ImageFormat::RGBA;
            ImageSpecification imageSpecification;
            imageSpecification.Width  = width;
            imageSpecification.Height = height;
            imageSpecification.Format = format;
            Buffer buffer(imageData, Utils::GetImageMemorySize(format, width, height));
            m_Image                = Image2D::Create(imageSpecification, buffer);
            m_ImageData            = m_Image->GetBuffer();
            m_Specification.Format = format;
        }

        if (!m_ImageData.Data)
            return;
        m_IsLoaded = true;

        m_Specification.Width  = width;
        m_Specification.Height = height;

        m_Image->Invalidate();

        Buffer& buffer = m_Image->GetBuffer();
        stbi_image_free(buffer.Data);
        buffer = Buffer();
    }

    OpenGLTexture2D::~OpenGLTexture2D() { m_Image->Release(); }

    void OpenGLTexture2D::Bind(uint32_t slot) const
    {
        Ref<OpenGLImage2D> image = m_Image.As<OpenGLImage2D>();
        glBindTextureUnit(slot, image->GetRendererID());
    }

    void OpenGLTexture2D::Lock() { m_Locked = true; }

    void OpenGLTexture2D::Unlock()
    {
        m_Locked                 = false;
        Ref<OpenGLImage2D> image = m_Image.As<OpenGLImage2D>();
        glTextureSubImage2D(image->GetRendererID(),
                            0,
                            0,
                            0,
                            m_Specification.Width,
                            m_Specification.Height,
                            Utils::OpenGLImageFormat(image->GetSpecification().Format),
                            GL_UNSIGNED_BYTE,
                            m_Image->GetBuffer().Data);
    }

    void OpenGLTexture2D::Resize(uint32_t width, uint32_t height)
    {
        GZ_CORE_ASSERT(m_Locked, "Texture must be locked!");

        m_ImageData.Allocate(width * height * Texture::GetBPP(m_Specification.Format));
#if GZ_DEBUG
        m_ImageData.ZeroInitialize();
#endif
    }

    Buffer OpenGLTexture2D::GetWriteableBuffer()
    {
        GZ_CORE_ASSERT(m_Locked, "Texture must be locked!");
        return m_Image->GetBuffer();
    }

    uint32_t OpenGLTexture2D::GetMipLevelCount() const
    {
        return Texture::CalculateMipMapCount(m_Specification.Width, m_Specification.Height);
    }

    //////////////////////////////////////////////////////////////////////////////////
    // TextureCube
    //////////////////////////////////////////////////////////////////////////////////

    OpenGLTextureCube::OpenGLTextureCube(const TextureSpecification& specification, const void* data) :
        m_Specification(specification)
    {
        if (data)
        {
            uint32_t size = specification.Width * specification.Height * 4 * 6; // six layers
            m_ImageData   = Buffer::Copy(data, size);
        }

        uint32_t levels = Texture::CalculateMipMapCount(m_Specification.Width, m_Specification.Height);

        glCreateTextures(GL_TEXTURE_CUBE_MAP, 1, &m_RendererID);
        glTextureStorage2D(m_RendererID,
                           levels,
                           Utils::ImageFormatToOpenGLTextureFormat(m_Specification.Format),
                           m_Specification.Width,
                           m_Specification.Height);
        glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, levels > 1 ? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR);
        glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    }

    // TODO: Revisit this, as currently env maps are being loaded as equirectangular 2D images
    //       so this is an old path
    OpenGLTextureCube::OpenGLTextureCube(const std::string& path) : m_FilePath(path)
    {
        int width, height, channels;
        stbi_set_flip_vertically_on_load(false);
        m_ImageData = stbi_load(path.c_str(), &width, &height, &channels, STBI_rgb);

        m_Specification.Width  = width;
        m_Specification.Height = height;
        m_Specification.Format = ImageFormat::RGB;

        uint32_t faceWidth  = width / 4;
        uint32_t faceHeight = height / 3;
        GZ_CORE_ASSERT(faceWidth == faceHeight, "Non-square faces!");

        std::array<uint8_t*, 6> faces;
        for (size_t i = 0; i < faces.size(); i++)
            faces[i] = new uint8_t[faceWidth * faceHeight * 3]; // 3 BPP

        int faceIndex = 0;

        for (size_t i = 0; i < 4; i++)
        {
            for (size_t y = 0; y < faceHeight; y++)
            {
                size_t yOffset = y + faceHeight;
                for (size_t x = 0; x < faceWidth; x++)
                {
                    size_t xOffset                                = x + i * faceWidth;
                    faces[faceIndex][(x + y * faceWidth) * 3 + 0] = m_ImageData[(xOffset + yOffset * width) * 3 + 0];
                    faces[faceIndex][(x + y * faceWidth) * 3 + 1] = m_ImageData[(xOffset + yOffset * width) * 3 + 1];
                    faces[faceIndex][(x + y * faceWidth) * 3 + 2] = m_ImageData[(xOffset + yOffset * width) * 3 + 2];
                }
            }
            faceIndex++;
        }

        for (size_t i = 0; i < 3; i++)
        {
            // Skip the middle one
            if (i == 1)
                continue;

            for (size_t y = 0; y < faceHeight; y++)
            {
                size_t yOffset = y + i * faceHeight;
                for (size_t x = 0; x < faceWidth; x++)
                {
                    size_t xOffset                                = x + faceWidth;
                    faces[faceIndex][(x + y * faceWidth) * 3 + 0] = m_ImageData[(xOffset + yOffset * width) * 3 + 0];
                    faces[faceIndex][(x + y * faceWidth) * 3 + 1] = m_ImageData[(xOffset + yOffset * width) * 3 + 1];
                    faces[faceIndex][(x + y * faceWidth) * 3 + 2] = m_ImageData[(xOffset + yOffset * width) * 3 + 2];
                }
            }
            faceIndex++;
        }

        glGenTextures(1, &m_RendererID);
        glBindTexture(GL_TEXTURE_CUBE_MAP, m_RendererID);

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

        auto format = Utils::ImageFormatToOpenGLTextureFormat(m_Specification.Format);
        glTexImage2D(
            GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, format, faceWidth, faceHeight, 0, format, GL_UNSIGNED_BYTE, faces[2]);
        glTexImage2D(
            GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, format, faceWidth, faceHeight, 0, format, GL_UNSIGNED_BYTE, faces[0]);

        glTexImage2D(
            GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, format, faceWidth, faceHeight, 0, format, GL_UNSIGNED_BYTE, faces[4]);
        glTexImage2D(
            GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, format, faceWidth, faceHeight, 0, format, GL_UNSIGNED_BYTE, faces[5]);

        glTexImage2D(
            GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, format, faceWidth, faceHeight, 0, format, GL_UNSIGNED_BYTE, faces[1]);
        glTexImage2D(
            GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, format, faceWidth, faceHeight, 0, format, GL_UNSIGNED_BYTE, faces[3]);

        glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

        glBindTexture(GL_TEXTURE_2D, 0);

        for (size_t i = 0; i < faces.size(); i++)
            delete[] faces[i];

        stbi_image_free(m_ImageData.Data);
    }

    OpenGLTextureCube::~OpenGLTextureCube() { glDeleteTextures(1, &m_RendererID); }

    void OpenGLTextureCube::Bind(uint32_t slot) const { glBindTextureUnit(slot, m_RendererID); }

    uint32_t OpenGLTextureCube::GetMipLevelCount() const
    {
        return Texture::CalculateMipMapCount(m_Specification.Width, m_Specification.Height);
    }
} // namespace Gaze