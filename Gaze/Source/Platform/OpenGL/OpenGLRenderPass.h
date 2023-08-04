#ifndef GAZE_ENGINE_OPENGLRENDERPASS_H
#define GAZE_ENGINE_OPENGLRENDERPASS_H

#include "Renderer/RenderPass.h"

namespace Gaze
{
    class OpenGLRenderPass : public RenderPass
    {
    public:
        OpenGLRenderPass(const RenderPassSpecification& spec);
        virtual ~OpenGLRenderPass();

        virtual RenderPassSpecification&       GetSpecification() override { return m_Specification; }
        virtual const RenderPassSpecification& GetSpecification() const override { return m_Specification; }

    private:
        RenderPassSpecification m_Specification;
    };
} // namespace Gaze

#endif // GAZE_ENGINE_OPENGLRENDERPASS_H
