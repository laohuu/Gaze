#include "GazePCH.h"

#include "OpenGLImage.h"

namespace Gaze
{
    OpenGLImage2D::OpenGLImage2D(ImageSpecification specification, Buffer buffer) :
        m_Specification(specification), m_ImageData(buffer)
    {}
    OpenGLImage2D::OpenGLImage2D(ImageSpecification specification, const void* data) : m_Specification(specification)
    {
        // TODO: Local storage should be optional
        if (data)
            m_ImageData = Buffer::Copy(
                data, Utils::GetImageMemorySize(specification.Format, specification.Width, specification.Height));
    }
    OpenGLImage2D::~OpenGLImage2D()
    { // Should this be submitted?
        m_ImageData.Release();
        if (m_RendererID)
        {
            glDeleteTextures(1, &m_RendererID);
        }
    }
    void OpenGLImage2D::Invalidate()
    {
        if (m_RendererID)
            Release();

        glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);

        GLenum   internalFormat = Utils::OpenGLImageInternalFormat(m_Specification.Format);
        uint32_t mipCount       = Utils::CalculateMipCount(m_Specification.Width, m_Specification.Height);
        glTextureStorage2D(m_RendererID, mipCount, internalFormat, m_Specification.Width, m_Specification.Height);
        if (m_ImageData)
        {
            GLenum format   = Utils::OpenGLImageFormat(m_Specification.Format);
            GLenum dataType = Utils::OpenGLFormatDataType(m_Specification.Format);
            glTextureSubImage2D(m_RendererID,
                                0,
                                0,
                                0,
                                m_Specification.Width,
                                m_Specification.Height,
                                format,
                                dataType,
                                m_ImageData.Data);
            glGenerateTextureMipmap(m_RendererID); // TODO: optional
        }

        // Sampler
        // TODO: should be separate from Image2D
        glCreateSamplers(1, &m_SamplerRendererID);
        glSamplerParameteri(
            m_SamplerRendererID, GL_TEXTURE_MIN_FILTER, m_ImageData ? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR);
        glSamplerParameteri(m_SamplerRendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glSamplerParameteri(m_SamplerRendererID, GL_TEXTURE_WRAP_R, GL_REPEAT);
        glSamplerParameteri(m_SamplerRendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glSamplerParameteri(m_SamplerRendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }
    void OpenGLImage2D::Release()
    {
        if (m_RendererID)
        {
            glDeleteTextures(1, &m_RendererID);
            m_RendererID = 0;
        }
        m_ImageData.Release();
    }
    void OpenGLImage2D::CreatePerLayerImageViews() {}
} // namespace Gaze