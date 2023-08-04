#include "Shader.h"
#include "GazePCH.h"

#include "Platform/OpenGL/OpenGLShader.h"
#include "Renderer.h"

namespace Gaze
{
    std::vector<Ref<Shader>> Shader::s_AllShaders;

    Ref<Shader> Shader::Create(const std::string& filepath, bool forceCompile)
    {
        Ref<Shader> result = nullptr;
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:
                GZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
                return nullptr;
            case RendererAPI::API::OpenGL:
                result = Ref<OpenGLShader>::Create(filepath, forceCompile);
                s_AllShaders.push_back(result);
                return result;
        }
        GZ_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

    Ref<Shader> Shader::CreateFromString(const std::string& source)
    {
        Ref<Shader> result = nullptr;
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:
                GZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
                return nullptr;
            case RendererAPI::API::OpenGL:
                result = OpenGLShader::CreateFromString(source);
                s_AllShaders.push_back(result);
                return result;
        }
        GZ_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

    ShaderLibrary::ShaderLibrary() {}

    ShaderLibrary::~ShaderLibrary() {}

    void ShaderLibrary::Add(const Ref<Shader>& shader)
    {
        auto& name = shader->GetName();
        GZ_CORE_ASSERT(m_Shaders.find(name) == m_Shaders.end());
        m_Shaders[name] = shader;
    }

    void ShaderLibrary::Load(const std::string& path, bool forceCompile)
    {
        auto  shader = Shader::Create(path, forceCompile);
        auto& name   = shader->GetName();
        GZ_CORE_ASSERT(m_Shaders.find(name) == m_Shaders.end());
        m_Shaders[name] = shader;
    }

    void ShaderLibrary::Load(const std::string& name, const std::string& path)
    {
        GZ_CORE_ASSERT(m_Shaders.find(name) == m_Shaders.end());
        m_Shaders[name] = Shader::Create(path);
    }

    const Ref<Shader>& ShaderLibrary::Get(const std::string& name) const
    {
        GZ_CORE_ASSERT(m_Shaders.find(name) != m_Shaders.end());
        return m_Shaders.at(name);
    }

    ShaderUniform::ShaderUniform(const std::string& name, ShaderUniformType type, uint32_t size, uint32_t offset) :
        m_Name(name), m_Type(type), m_Size(size), m_Offset(offset)
    {}

    const std::string ShaderUniform::UniformTypeToString(ShaderUniformType type)
    {
        if (type == ShaderUniformType::Bool)
        {
            return "Boolean";
        }
        else if (type == ShaderUniformType::Int)
        {
            return "Int";
        }
        else if (type == ShaderUniformType::Float)
        {
            return "Float";
        }

        return "None";
    }
} // namespace Gaze