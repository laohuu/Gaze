#ifndef GAZE_ENGINE_VERTEXARRAY_H
#define GAZE_ENGINE_VERTEXARRAY_H

#include "Renderer/Buffer.h"

#include <memory>

namespace Gaze
{

    class VertexArray : public RefCounted
    {
    public:
        virtual ~VertexArray() = default;

        virtual void Bind() const = 0;

        virtual void Unbind() const = 0;

        virtual void AddVertexBuffer(const Gaze::Ref<VertexBuffer>& vertexBuffer) = 0;

        virtual void SetIndexBuffer(const Gaze::Ref<IndexBuffer>& indexBuffer) = 0;

        virtual const std::vector<Gaze::Ref<VertexBuffer>>& GetVertexBuffers() const = 0;

        virtual const Gaze::Ref<IndexBuffer>& GetIndexBuffer() const = 0;

        static Gaze::Ref<VertexArray> Create();
    };

} // namespace Gaze

#endif // GAZE_ENGINE_VERTEXARRAY_H
