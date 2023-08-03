#include "OpenGLBuffer.h"
#include "GazePCH.h"

#include <glad/glad.h>

namespace Gaze
{

    /////////////////////////////////////////////////////////////////////////////
    // VertexBuffer /////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////

    static GLenum OpenGLUsage(VertexBufferUsage usage)
    {
        switch (usage)
        {
            case VertexBufferUsage::Static:
                return GL_STATIC_DRAW;
            case VertexBufferUsage::Dynamic:
                return GL_DYNAMIC_DRAW;
        }
        GZ_CORE_ASSERT(false, "Unknown vertex buffer usage");
        return 0;
    }

    OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size, VertexBufferUsage usage) : m_Size(size), m_Usage(usage)
    {
        glCreateBuffers(1, &m_RendererID);
        glNamedBufferData(m_RendererID, m_Size, nullptr, OpenGLUsage(m_Usage));
    }

    OpenGLVertexBuffer::OpenGLVertexBuffer(void* data, uint32_t size, VertexBufferUsage usage) :
        m_Size(size), m_Usage(usage)
    {
        m_LocalData = Buffer::Copy(data, size);

        glCreateBuffers(1, &m_RendererID);
        glNamedBufferData(m_RendererID, m_Size, data, OpenGLUsage(m_Usage));
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer()
    {
        GZ_PROFILE_FUNCTION();

        GLuint rendererID = m_RendererID;
        glDeleteBuffers(1, &rendererID);
    }

    void OpenGLVertexBuffer::Bind() const
    {
        GZ_PROFILE_FUNCTION();

        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    }

    void OpenGLVertexBuffer::Unbind() const
    {
        GZ_PROFILE_FUNCTION();

        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void OpenGLVertexBuffer::SetData(const void* data, uint32_t size, uint32_t offset)
    {
        m_LocalData = Buffer::Copy(data, size);
        m_Size      = size;

        glNamedBufferSubData(m_RendererID, offset, m_Size, m_LocalData.Data);
    }

    /////////////////////////////////////////////////////////////////////////////
    // IndexBuffer //////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////

    OpenGLIndexBuffer::OpenGLIndexBuffer(void* data, uint32_t size) : m_RendererID(0), m_Size(size)
    {
        m_LocalData = Buffer::Copy(data, size);

        glCreateBuffers(1, &m_RendererID);
        // GL_ELEMENT_ARRAY_BUFFER is not valid without an actively bound VAO
        // Binding with GL_ARRAY_BUFFER allows the data to be loaded regardless of VAO state.
        glNamedBufferData(m_RendererID, m_Size, m_LocalData.Data, GL_STATIC_DRAW);
    }

    OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t size) : m_RendererID(0), m_Size(size)
    {

        glCreateBuffers(1, &m_RendererID);
        // GL_ELEMENT_ARRAY_BUFFER is not valid without an actively bound VAO
        // Binding with GL_ARRAY_BUFFER allows the data to be loaded regardless of VAO state.
        glNamedBufferData(m_RendererID, m_Size, nullptr, GL_STATIC_DRAW);
    }

    OpenGLIndexBuffer::~OpenGLIndexBuffer()
    {
        GZ_PROFILE_FUNCTION();

        glDeleteBuffers(1, &m_RendererID);
    }

    void OpenGLIndexBuffer::Bind() const
    {
        GZ_PROFILE_FUNCTION();

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    }

    void OpenGLIndexBuffer::Unbind() const
    {
        GZ_PROFILE_FUNCTION();

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void OpenGLIndexBuffer::SetData(const void* data, uint32_t size, uint32_t offset)
    {
        m_LocalData = Buffer::Copy(data, size);
        m_Size      = size;

        glNamedBufferSubData(m_RendererID, offset, m_Size, m_LocalData.Data);
    }

} // namespace Gaze