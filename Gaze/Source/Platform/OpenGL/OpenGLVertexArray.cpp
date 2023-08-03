#include "OpenGLVertexArray.h"
#include "GazePCH.h"

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

    OpenGLVertexArray::OpenGLVertexArray()
    {
        GZ_PROFILE_FUNCTION();

        m_VertexBufferIndex = 0;
        glCreateVertexArrays(1, &m_RendererID);
    }

    OpenGLVertexArray::~OpenGLVertexArray()
    {
        GZ_PROFILE_FUNCTION();

        glDeleteVertexArrays(1, &m_RendererID);
    }

    void OpenGLVertexArray::Bind() const
    {
        GZ_PROFILE_FUNCTION();

        glBindVertexArray(m_RendererID);
    }

    void OpenGLVertexArray::Unbind() const
    {
        GZ_PROFILE_FUNCTION();

        glBindVertexArray(0);
    }

    void OpenGLVertexArray::AddVertexBuffer(const Gaze::Ref<VertexBuffer>& vertexBuffer)
    {
        GZ_PROFILE_FUNCTION();

        GZ_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

        glBindVertexArray(m_RendererID);
        vertexBuffer->Bind();

        const auto& layout      = vertexBuffer->GetLayout();
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
        m_VertexBuffers.push_back(vertexBuffer);
    }

    void OpenGLVertexArray::SetIndexBuffer(const Gaze::Ref<IndexBuffer>& indexBuffer)
    {
        GZ_PROFILE_FUNCTION();

        glBindVertexArray(m_RendererID);
        indexBuffer->Bind();

        m_IndexBuffer = indexBuffer;
    }
} // namespace Gaze