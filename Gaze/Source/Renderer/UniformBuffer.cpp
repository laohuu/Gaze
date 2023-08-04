#include "UniformBuffer.h"
#include "GazePCH.h"

#include "Platform/OpenGL/OpenGLUniformBuffer.h"
#include "Renderer/Renderer.h"

namespace Gaze
{
    Ref<UniformBuffer> UniformBuffer::Create(uint32_t size, uint32_t binding)
    {
        switch (RendererAPI::Current())
        {
            case RendererAPIType::None:
                GZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
                return nullptr;
            case RendererAPIType::OpenGL:
                return Ref<OpenGLUniformBuffer>::Create(size, binding);
        }

        GZ_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
} // namespace Gaze