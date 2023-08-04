#include "GazePCH.h"

#include "RenderPass.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLRenderPass.h"

namespace Gaze
{
    Ref<RenderPass> RenderPass::Create(const RenderPassSpecification& spec)
    {
        switch (RendererAPI::Current())
        {
            case RendererAPIType::None:
                GZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
                return nullptr;
            case RendererAPIType::OpenGL:
                return Ref<OpenGLRenderPass>::Create(spec);
        }

        GZ_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
} // namespace Gaze