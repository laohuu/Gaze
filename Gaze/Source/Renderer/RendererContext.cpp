#include "GazePCH.h"

#include "RendererContext.h"
#include "Renderer/RendererAPI.h"

#include "Platform/OpenGL/OpenGLContext.h"

namespace Gaze
{
    Ref<RendererContext> RendererContext::Create(GLFWwindow* windowHandle)
    {
        switch (RendererAPI::Current())
        {
            case RendererAPIType::None:
                return nullptr;
            case RendererAPIType::OpenGL:
                return Ref<OpenGLContext>::Create(windowHandle);
        }
        GZ_CORE_ASSERT(false, "Unknown RendererAPI");
        return nullptr;
    }
} // namespace Gaze