#ifndef GAZE_ENGINE_OPENGLFRAMEBUFFER_H
#define GAZE_ENGINE_OPENGLFRAMEBUFFER_H

#include "Renderer/Framebuffer.h"

namespace Gaze {

    class OpenGLFramebuffer : public Framebuffer {
    public:
        OpenGLFramebuffer(const FramebufferSpecification &spec);

        ~OpenGLFramebuffer() override;

        void Invalidate();

        void Bind() override;

        void Unbind() override;

        uint32_t GetColorAttachmentRendererID() const override { return m_ColorAttachment; }

        const FramebufferSpecification &GetSpecification() const override { return m_Specification; }

    private:
        uint32_t m_RendererID;
        uint32_t m_ColorAttachment, m_DepthAttachment;
        FramebufferSpecification m_Specification;
    };

} // Gaze

#endif //GAZE_ENGINE_OPENGLFRAMEBUFFER_H
