#include "GazePCH.h"

#include "Pipeline.h"
#include "Platform/OpenGL/OpenGLPipeline.h"
#include "Renderer/RendererAPI.h"

namespace Gaze
{
    Ref<Pipeline> Pipeline::Create(const PipelineSpecification& spec)
    {
        switch (RendererAPI::Current())
        {
            case RendererAPIType::None:
                return nullptr;
            case RendererAPIType::OpenGL:
                return Ref<OpenGLPipeline>::Create(spec);
        }
        GZ_CORE_ASSERT(false, "Unknown RendererAPI");
        return nullptr;
    }
} // namespace Gaze