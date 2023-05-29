#include "GazePCH.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Gaze {

    Scope <RendererAPI> RenderCommand::s_RendererAPI = CreateScope<OpenGLRendererAPI>();

} // Gaze