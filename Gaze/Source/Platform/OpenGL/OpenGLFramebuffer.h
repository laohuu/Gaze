#ifndef GAZE_ENGINE_OPENGLFRAMEBUFFER_H
#define GAZE_ENGINE_OPENGLFRAMEBUFFER_H

#include "Renderer/Framebuffer.h"

namespace Gaze
{
    class OpenGLFramebuffer : public Framebuffer
    {
    public:
        OpenGLFramebuffer(const FramebufferSpecification& spec);
        ~OpenGLFramebuffer() override;

        void Resize(uint32_t width, uint32_t height, bool forceRecreate = false) override;

        void Bind() const override;
        void Unbind() const override;

        void BindTexture(uint32_t attachmentIndex = 0, uint32_t slot = 0) const override;

        uint32_t GetWidth() const override { return m_Specification.Width; }
        uint32_t GetHeight() const override { return m_Specification.Height; }

        RendererID GetRendererID() const override { return m_RendererID; }
        RendererID GetColorAttachmentRendererID(int index = 0) const override { return m_ColorAttachments[index]; }
        RendererID GetDepthAttachmentRendererID() const override { return m_DepthAttachment; }

        const FramebufferSpecification& GetSpecification() const override { return m_Specification; }

    private:
        FramebufferSpecification m_Specification;
        RendererID               m_RendererID = 0;

        std::vector<RendererID> m_ColorAttachments;
        RendererID              m_DepthAttachment;

        std::vector<FramebufferTextureFormat> m_ColorAttachmentFormats;
        FramebufferTextureFormat              m_DepthAttachmentFormat = FramebufferTextureFormat::None;

        uint32_t m_Width = 0, m_Height = 0;
    };
} // namespace Gaze

#endif // GAZE_ENGINE_OPENGLFRAMEBUFFER_H
