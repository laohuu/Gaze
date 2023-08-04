#include "RendererAPI.h"
#include "GazePCH.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Gaze
{
    RendererAPIType RendererAPI::s_CurrentRendererAPI = RendererAPIType::OpenGL;

    Gaze::Scope<RendererAPI> RendererAPI::Create()
    {
        switch (s_CurrentRendererAPI)
        {
            case RendererAPIType::None:
                GZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
                return nullptr;
            case RendererAPIType::OpenGL:
                return CreateScope<OpenGLRendererAPI>();
        }

        GZ_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
} // namespace Gaze