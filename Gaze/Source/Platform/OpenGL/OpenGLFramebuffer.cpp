#include "GazePCH.h"

#include "OpenGLFramebuffer.h"

#include <glad/glad.h>

namespace Gaze
{
    namespace Utils
    {
        static GLenum TextureTarget(bool multisampled)
        {
            return multisampled ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D;
        }

        static void CreateTextures(bool multisampled, RendererID* outID, uint32_t count)
        {
            glCreateTextures(TextureTarget(multisampled), 1, outID);
        }

        static void BindTexture(bool multisampled, RendererID id) { glBindTexture(TextureTarget(multisampled), id); }

        static GLenum DataType(GLenum format)
        {
            switch (format)
            {
                case GL_RGBA8:
                    return GL_UNSIGNED_BYTE;
                case GL_RG16F:
                case GL_RG32F:
                case GL_RGBA16F:
                case GL_RGBA32F:
                    return GL_FLOAT;
                case GL_DEPTH24_STENCIL8:
                    return GL_UNSIGNED_INT_24_8;
            }

            GZ_CORE_ASSERT(false, "Unknown format!");
            return 0;
        }

        static void
        AttachColorTexture(RendererID id, int samples, GLenum format, uint32_t width, uint32_t height, int index)
        {
            bool multisampled = samples > 1;
            if (multisampled)
            {
                glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, format, width, height, GL_FALSE);
            }
            else
            {
                // Only RGBA access for now
                glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, GL_RGBA, DataType(format), nullptr);

                glTexParameteri(TextureTarget(multisampled), GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(TextureTarget(multisampled), GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                glTexParameteri(TextureTarget(multisampled), GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                glTexParameteri(TextureTarget(multisampled), GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            }

            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, TextureTarget(multisampled), id, 0);
        }

        static void AttachDepthTexture(RendererID id,
                                       int        samples,
                                       GLenum     format,
                                       GLenum     attachmentType,
                                       uint32_t   width,
                                       uint32_t   height)
        {
            bool multisampled = samples > 1;
            if (multisampled)
            {
                glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, format, width, height, GL_FALSE);
            }
            else
            {
                glTexStorage2D(GL_TEXTURE_2D, 1, format, width, height);

                glTexParameteri(TextureTarget(multisampled), GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(TextureTarget(multisampled), GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                glTexParameteri(TextureTarget(multisampled), GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                glTexParameteri(TextureTarget(multisampled), GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            }

            glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentType, TextureTarget(multisampled), id, 0);
        }

        static bool IsDepthFormat(FramebufferTextureFormat format)
        {
            switch (format)
            {
                case FramebufferTextureFormat::DEPTH24STENCIL8:
                case FramebufferTextureFormat::DEPTH32F:
                    return true;
            }
            return false;
        }

    } // namespace Utils

    OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferSpecification& spec) :
        m_Specification(spec), m_Width(spec.Width), m_Height(spec.Height)
    {
        for (auto format : m_Specification.Attachments.Attachments)
        {
            if (!Utils::IsDepthFormat(format.TextureFormat))
                m_ColorAttachmentFormats.emplace_back(format.TextureFormat);
            else
                m_DepthAttachmentFormat = format.TextureFormat;
        }

        Resize(spec.Width, spec.Height, true);
    }

    OpenGLFramebuffer::~OpenGLFramebuffer() { glDeleteFramebuffers(1, &m_RendererID); }

    void OpenGLFramebuffer::Resize(uint32_t width, uint32_t height, bool forceRecreate)
    {
        if (!forceRecreate && (m_Width == width && m_Height == height))
            return;

        m_Width  = width;
        m_Height = height;

        if (m_RendererID)
        {
            glDeleteFramebuffers(1, &m_RendererID);
            glDeleteTextures(m_ColorAttachments.size(), m_ColorAttachments.data());
            glDeleteTextures(1, &m_DepthAttachment);

            m_ColorAttachments.clear();
            m_DepthAttachment = 0;
        }

        glGenFramebuffers(1, &m_RendererID);
        glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);

        bool multisample = m_Specification.Samples > 1;

        if (m_ColorAttachmentFormats.size())
        {
            m_ColorAttachments.resize(m_ColorAttachmentFormats.size());
            Utils::CreateTextures(multisample, m_ColorAttachments.data(), m_ColorAttachments.size());

            // Create color attachments
            for (int i = 0; i < m_ColorAttachments.size(); i++)
            {
                Utils::BindTexture(multisample, m_ColorAttachments[i]);
                switch (m_ColorAttachmentFormats[i])
                {
                    case FramebufferTextureFormat::RGBA8:
                        Utils::AttachColorTexture(
                            m_ColorAttachments[i], m_Specification.Samples, GL_RGBA8, m_Width, m_Height, i);
                        break;
                    case FramebufferTextureFormat::RGBA16F:
                        Utils::AttachColorTexture(
                            m_ColorAttachments[i], m_Specification.Samples, GL_RGBA16F, m_Width, m_Height, i);
                        break;
                    case FramebufferTextureFormat::RGBA32F:
                        Utils::AttachColorTexture(
                            m_ColorAttachments[i], m_Specification.Samples, GL_RGBA32F, m_Width, m_Height, i);
                        break;
                    case FramebufferTextureFormat::RG32F:
                        Utils::AttachColorTexture(
                            m_ColorAttachments[i], m_Specification.Samples, GL_RG32F, m_Width, m_Height, i);
                        break;
                }
            }
        }

        if (m_DepthAttachmentFormat != FramebufferTextureFormat::None)
        {
            Utils::CreateTextures(multisample, &m_DepthAttachment, 1);
            Utils::BindTexture(multisample, m_DepthAttachment);
            switch (m_DepthAttachmentFormat)
            {
                case FramebufferTextureFormat::DEPTH24STENCIL8:
                    Utils::AttachDepthTexture(m_DepthAttachment,
                                              m_Specification.Samples,
                                              GL_DEPTH24_STENCIL8,
                                              GL_DEPTH_STENCIL_ATTACHMENT,
                                              m_Width,
                                              m_Height);
                    break;
                case FramebufferTextureFormat::DEPTH32F:
                    Utils::AttachDepthTexture(m_DepthAttachment,
                                              m_Specification.Samples,
                                              GL_DEPTH_COMPONENT32F,
                                              GL_DEPTH_ATTACHMENT,
                                              m_Width,
                                              m_Height);
                    break;
            }
        }

        if (m_ColorAttachments.size() > 1)
        {
            GZ_CORE_ASSERT(m_ColorAttachments.size() <= 4);
            GLenum buffers[4] = {
                GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3};
            glDrawBuffers(m_ColorAttachments.size(), buffers);
        }
        else if (m_ColorAttachments.size() == 0)
        {
            // Only depth-pass
            glDrawBuffer(GL_NONE);
        }

        GZ_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE,
                       "Framebuffer is incomplete!");

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void OpenGLFramebuffer::Bind() const
    {
        glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
        glViewport(0, 0, m_Width, m_Height);
    }

    void OpenGLFramebuffer::Unbind() const { glBindFramebuffer(GL_FRAMEBUFFER, 0); }

    void OpenGLFramebuffer::BindTexture(uint32_t attachmentIndex, uint32_t slot) const
    {
        glBindTextureUnit(slot, m_ColorAttachments[attachmentIndex]);
    }
} // namespace Gaze