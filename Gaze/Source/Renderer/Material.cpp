#include "GazePCH.h"

#include "Material.h"
#include "Platform/OpenGL/OpenGLMaterial.h"

namespace Gaze
{
    Ref<Material> Material::Create(const Ref<Shader>& shader, const std::string& name)
    {
        switch (RendererAPI::Current())
        {
            case RendererAPIType::None:
                return nullptr;
            case RendererAPIType::OpenGL:
                return Ref<OpenGLMaterial>::Create(shader, name);
        }
        GZ_CORE_ASSERT(false, "Unknown RendererAPI");
        return nullptr;
    }
} // namespace Gaze