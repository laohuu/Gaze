#include "GazePCH.h"

#include "OpenGLRenderPass.h"

namespace Gaze
{
    OpenGLRenderPass::OpenGLRenderPass(const RenderPassSpecification& spec) : m_Specification(spec) {}

    OpenGLRenderPass::~OpenGLRenderPass() {}
} // namespace Gaze