#include "GazePCH.h"

#include "Image.h"
#include "Platform/OpenGL/OpenGLImage.h"
#include "Renderer/Renderer.h"

namespace Gaze
{

    Ref<Image2D> Image2D::Create(ImageSpecification specification, Buffer buffer)
    {
        switch (RendererAPI::Current())
        {
            case RendererAPIType::None:
                GZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
                return nullptr;
            case RendererAPIType::OpenGL:
                return Ref<OpenGLImage2D>::Create(specification, buffer);
        }

        GZ_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

    Ref<Image2D> Image2D::Create(ImageSpecification specification, const void* data)
    {
        switch (RendererAPI::Current())
        {
            case RendererAPIType::None:
                GZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
                return nullptr;
            case RendererAPIType::OpenGL:
                return Ref<OpenGLImage2D>::Create(specification, data);
        }
        GZ_CORE_ASSERT(false, "Unknown RendererAPI");
        return nullptr;
    }

} // namespace Gaze