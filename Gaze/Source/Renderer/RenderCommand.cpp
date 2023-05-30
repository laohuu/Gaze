#include "GazePCH.h"
#include "RenderCommand.h"

namespace Gaze {

    Gaze::Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();

} // Gaze