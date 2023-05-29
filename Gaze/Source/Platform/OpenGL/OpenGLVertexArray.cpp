#include "GazePCH.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Gaze {

    static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
        switch (type) {
            case Gaze::ShaderDataType::Float:
                return GL_FLOAT;
            case Gaze::ShaderDataType::Float2:
                return GL_FLOAT;
            case Gaze::ShaderDataType::Float3:
                return GL_FLOAT;
            case Gaze::ShaderDataType::Float4:
                return GL_FLOAT;
            case Gaze::ShaderDataType::Mat3:
                return GL_FLOAT;
            case Gaze::ShaderDataType::Mat4:
                return GL_FLOAT;
            case Gaze::ShaderDataType::Int:
                return GL_INT;
            case Gaze::ShaderDataType::Int2:
                return GL_INT;
            case Gaze::ShaderDataType::Int3:
                return GL_INT;
            case Gaze::ShaderDataType::Int4:
                return GL_INT;
            case Gaze::ShaderDataType::Bool:
                return GL_BOOL;
            case ShaderDataType::None: GZ_CORE_ASSERT(false, "None ShaderDataType!");
                break;
        }

        GZ_CORE_ASSERT(false, "Unknown ShaderDataType!");
        return 0;
    }

    OpenGLVertexArray::OpenGLVertexArray() {
        m_VertexBufferIndex = 0;
        glCreateVertexArrays(1, &m_RendererID);
    }

    OpenGLVertexArray::~OpenGLVertexArray() {
        glDeleteVertexArrays(1, &m_RendererID);
    }

    void OpenGLVertexArray::Bind() const {
        glBindVertexArray(m_RendererID);
    }

    void OpenGLVertexArray::Unbind() const {
        glBindVertexArray(0);
    }

    void OpenGLVertexArray::AddVertexBuffer(const Gaze::Ref<VertexBuffer> &vertexBuffer) {
        GZ_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

        glBindVertexArray(m_RendererID);
        vertexBuffer->Bind();

        const auto &layout = vertexBuffer->GetLayout();
        for (const auto &element: layout) {
            glEnableVertexAttribArray(m_VertexBufferIndex);
            glVertexAttribPointer(m_VertexBufferIndex,
                                  element.GetComponentCount(),
                                  ShaderDataTypeToOpenGLBaseType(element.Type),
                                  element.Normalized ? GL_TRUE : GL_FALSE,
                                  layout.GetStride(),
                                  (const void *) (intptr_t) element.Offset);
            m_VertexBufferIndex++;
        }
        m_VertexBuffers.push_back(vertexBuffer);
    }

    void OpenGLVertexArray::SetIndexBuffer(const Gaze::Ref<IndexBuffer> &indexBuffer) {
        glBindVertexArray(m_RendererID);
        indexBuffer->Bind();

        m_IndexBuffer = indexBuffer;
    }
} // Gaze