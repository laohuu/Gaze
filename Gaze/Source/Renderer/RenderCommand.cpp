#include "GazePCH.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Gaze {

    RendererAPI *RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

} // Gaze