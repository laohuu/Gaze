#ifndef GAZE_ENGINE_OPENGLIMAGE_H
#define GAZE_ENGINE_OPENGLIMAGE_H

#include "Renderer/Image.h"
#include "Renderer/RendererTypes.h"

#include <glad/glad.h>

namespace Gaze
{
    class OpenGLImage2D : public Image2D
    {
    public:
        OpenGLImage2D(ImageSpecification specification, Buffer buffer);
        OpenGLImage2D(ImageSpecification specification, const void* data = nullptr);
        ~OpenGLImage2D() override;

        void Resize(const glm::uvec2& size) override { Resize(size.x, size.y); }
        void Resize(const uint32_t width, const uint32_t height) override
        {
            m_Specification.Width  = width;
            m_Specification.Height = height;
            Invalidate();
        }
        void Invalidate() override;
        void Release() override;

        uint32_t   GetWidth() const override { return m_Specification.Width; }
        uint32_t   GetHeight() const override { return m_Specification.Height; }
        glm::uvec2 GetSize() const override { return {m_Specification.Width, m_Specification.Height}; }

        float GetAspectRatio() const override { return (float)m_Specification.Width / (float)m_Specification.Height; }

        ImageSpecification&       GetSpecification() override { return m_Specification; }
        const ImageSpecification& GetSpecification() const override { return m_Specification; }

        Buffer  GetBuffer() const override { return m_ImageData; }
        Buffer& GetBuffer() override { return m_ImageData; }

        void CreatePerLayerImageViews() override;

        RendererID& GetRendererID() { return m_RendererID; }
        RendererID  GetRendererID() const { return m_RendererID; }

        RendererID& GetSamplerRendererID() { return m_SamplerRendererID; }
        RendererID  GetSamplerRendererID() const { return m_SamplerRendererID; }

        uint64_t GetHash() const override { return (uint64_t)m_RendererID; }

    private:
        ImageSpecification m_Specification;

        RendererID m_RendererID        = 0;
        RendererID m_SamplerRendererID = 0;

        Buffer m_ImageData;
    };

    namespace Utils
    {
        inline GLenum OpenGLImageFormat(ImageFormat format)
        {
            switch (format)
            {
                case ImageFormat::RGB:
                    return GL_RGB;
                case ImageFormat::SRGB:
                    return GL_RGB;
                case ImageFormat::RGBA:
                case ImageFormat::RGBA16F:
                case ImageFormat::RGBA32F:
                    return GL_RGBA;
            }
            GZ_CORE_ASSERT(false, "Unknown image format");
            return 0;
        }

        inline GLenum OpenGLImageInternalFormat(ImageFormat format)
        {
            switch (format)
            {
                case ImageFormat::RGB:
                    return GL_RGB8;
                case ImageFormat::SRGB:
                    return GL_SRGB8;
                case ImageFormat::RGBA:
                    return GL_RGBA8;
                case ImageFormat::RGBA16F:
                    return GL_RGBA16F;
                case ImageFormat::RGBA32F:
                    return GL_RGBA32F;
                case ImageFormat::DEPTH24STENCIL8:
                    return GL_DEPTH24_STENCIL8;
                case ImageFormat::DEPTH32F:
                    return GL_DEPTH_COMPONENT32F;
            }
            GZ_CORE_ASSERT(false, "Unknown image format");
            return 0;
        }

        inline GLenum OpenGLFormatDataType(ImageFormat format)
        {
            switch (format)
            {
                case ImageFormat::RGB:
                case ImageFormat::SRGB:
                case ImageFormat::RGBA:
                    return GL_UNSIGNED_BYTE;
                case ImageFormat::RGBA16F:
                case ImageFormat::RGBA32F:
                    return GL_FLOAT;
            }
            GZ_CORE_ASSERT(false, "Unknown image format");
            return 0;
        }
    } // namespace Utils
} // namespace Gaze

#endif // GAZE_ENGINE_OPENGLIMAGE_H
