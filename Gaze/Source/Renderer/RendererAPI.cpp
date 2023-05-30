#include "GazePCH.h"
#include "RendererAPI.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Gaze {
    RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

    Gaze::Scope<RendererAPI> RendererAPI::Create() {
        switch (s_API) {
            case RendererAPI::API::None: GZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
                return nullptr;
            case RendererAPI::API::OpenGL:
                return CreateScope<OpenGLRendererAPI>();
        }

        GZ_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

} // Gaze