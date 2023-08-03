#ifndef GAZE_ENGINE_OPENGLBUFFER_H
#define GAZE_ENGINE_OPENGLBUFFER_H

#include "Core/Buffer.h"
#include "Renderer/Buffer.h"

namespace Gaze
{

    class OpenGLVertexBuffer : public VertexBuffer
    {
    public:
        OpenGLVertexBuffer(void* data, uint32_t size, VertexBufferUsage usage = VertexBufferUsage::Static);
        OpenGLVertexBuffer(uint32_t size, VertexBufferUsage usage = VertexBufferUsage::Dynamic);
        ~OpenGLVertexBuffer() override;

        void Bind() const override;
        void Unbind() const override;

        void SetData(const void* data, uint32_t size, uint32_t offset = 0) override;

        const BufferLayout& GetLayout() const override { return m_Layout; }
        void                SetLayout(const BufferLayout& layout) override { m_Layout = layout; }

        uint32_t   GetSize() const override { return m_Size; }
        RendererID GetRendererID() const override { return m_RendererID; }

    private:
        RendererID        m_RendererID = 0;
        uint32_t          m_Size;
        VertexBufferUsage m_Usage;
        BufferLayout      m_Layout;

        Buffer m_LocalData;
    };

    class OpenGLIndexBuffer : public IndexBuffer
    {
    public:
        OpenGLIndexBuffer(uint32_t size);
        OpenGLIndexBuffer(void* data, uint32_t size);
        ~OpenGLIndexBuffer() override;

        void Bind() const override;
        void Unbind() const override;

        void SetData(const void* data, uint32_t size, uint32_t offset = 0) override;

        uint32_t GetCount() const override { return m_Size / sizeof(uint32_t); }

        uint32_t   GetSize() const override { return m_Size; }
        RendererID GetRendererID() const override { return m_RendererID; }

    private:
        RendererID m_RendererID = 0;
        uint32_t   m_Size;

        Buffer m_LocalData;
    };

} // namespace Gaze

#endif // GAZE_ENGINE_OPENGLBUFFER_H
