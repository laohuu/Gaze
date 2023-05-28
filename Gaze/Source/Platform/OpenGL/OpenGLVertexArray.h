#ifndef GAZE_ENGINE_OPENGLVERTEXARRAY_H
#define GAZE_ENGINE_OPENGLVERTEXARRAY_H

#include "Renderer/VertexArray.h"

namespace Gaze {


    class OpenGLVertexArray : public VertexArray {
    public:
        OpenGLVertexArray();

        virtual ~OpenGLVertexArray();

        virtual void Bind() const override;

        virtual void Unbind() const override;

        virtual void AddVertexBuffer(const Gaze::Ref<VertexBuffer> &vertexBuffer) override;

        virtual void SetIndexBuffer(const Gaze::Ref<IndexBuffer> &indexBuffer) override;

        virtual const std::vector<Gaze::Ref<VertexBuffer>> &GetVertexBuffers() const { return m_VertexBuffers; }

        virtual const Gaze::Ref<IndexBuffer> &GetIndexBuffer() const { return m_IndexBuffer; }

    private:
        uint32_t m_RendererID;
        std::vector<Gaze::Ref<VertexBuffer>> m_VertexBuffers;
        Gaze::Ref<IndexBuffer> m_IndexBuffer;
    };

} // Gaze

#endif //GAZE_ENGINE_OPENGLVERTEXARRAY_H
