#include "GazePCH.h"

#include "Image.h"

#include "Renderer/Renderer.h"

namespace Gaze
{

    Ref<Image2D> Image2D::Create(ImageSpecification specification, Buffer buffer)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:
                GZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
                return nullptr;
            case RendererAPI::API::OpenGL:
                return nullptr;
        }

        GZ_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

    Ref<Image2D> Image2D::Create(ImageSpecification specification, const void* data)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:
                GZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
                return nullptr;
            case RendererAPI::API::OpenGL:
                return nullptr;
        }
        GZ_CORE_ASSERT(false, "Unknown RendererAPI");
        return nullptr;
    }

} // namespace Gaze