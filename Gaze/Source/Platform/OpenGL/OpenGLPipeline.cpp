#include "GazePCH.h"

#include "OpenGLPipeline.h"
#include "Renderer/Renderer.h"

#include <glad/glad.h>

namespace Gaze
{
    static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
    {
        switch (type)
        {
            case ShaderDataType::Float:
                return GL_FLOAT;
            case ShaderDataType::Float2:
                return GL_FLOAT;
            case ShaderDataType::Float3:
                return GL_FLOAT;
            case ShaderDataType::Float4:
                return GL_FLOAT;
            case ShaderDataType::Mat3:
                return GL_FLOAT;
            case ShaderDataType::Mat4:
                return GL_FLOAT;
            case ShaderDataType::Int:
                return GL_INT;
            case ShaderDataType::Int2:
                return GL_INT;
            case ShaderDataType::Int3:
                return GL_INT;
            case ShaderDataType::Int4:
                return GL_INT;
            case ShaderDataType::Bool:
                return GL_BOOL;
        }

        GZ_CORE_ASSERT(false, "Unknown ShaderDataType!");
        return 0;
    }

    OpenGLPipeline::OpenGLPipeline(const PipelineSpecification& spec) : m_Specification(spec)
    {
        GZ_CORE_ASSERT(spec.Shader);
        GZ_CORE_ASSERT(spec.RenderPass);
        Invalidate();
    }

    OpenGLPipeline::~OpenGLPipeline()
    {
        GLuint rendererID = m_VertexArrayRendererID;
        glDeleteVertexArrays(1, &rendererID);
    }

    void OpenGLPipeline::Invalidate()
    {
        GZ_CORE_ASSERT(m_Specification.Layout.GetElements().size(), "Layout is empty!");

        auto& vertexArrayRendererID = m_VertexArrayRendererID;

        if (vertexArrayRendererID)
            glDeleteVertexArrays(1, &vertexArrayRendererID);

        glGenVertexArrays(1, &vertexArrayRendererID);
        glBindVertexArray(vertexArrayRendererID);

        glBindVertexArray(0);
    }

    void OpenGLPipeline::Bind()
    {
        glBindVertexArray(m_VertexArrayRendererID);

        const auto& layout      = m_Specification.Layout;
        uint32_t    attribIndex = 0;
        for (const auto& element : layout)
        {
            auto glBaseType = ShaderDataTypeToOpenGLBaseType(element.Type);
            glEnableVertexAttribArray(attribIndex);
            if (glBaseType == GL_INT)
            {
                glVertexAttribIPointer(attribIndex,
                                       element.GetComponentCount(),
                                       glBaseType,
                                       layout.GetStride(),
                                       (const void*)(intptr_t)element.Offset);
            }
            else
            {
                glVertexAttribPointer(attribIndex,
                                      element.GetComponentCount(),
                                      glBaseType,
                                      element.Normalized ? GL_TRUE : GL_FALSE,
                                      layout.GetStride(),
                                      (const void*)(intptr_t)element.Offset);
            }
            attribIndex++;
        }
    }
} // namespace Gaze