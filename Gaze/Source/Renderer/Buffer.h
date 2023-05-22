#ifndef GAZE_ENGINE_BUFFER_H
#define GAZE_ENGINE_BUFFER_H

#include <cstdint>

namespace Gaze {

    class VertexBuffer
    {
    public:
        virtual ~VertexBuffer() {}

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        static VertexBuffer* Create(float* vertices, uint32_t size);
    };

    class IndexBuffer
    {
    public:
        virtual ~IndexBuffer() {}

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual uint32_t GetCount() const = 0;

        static IndexBuffer* Create(uint32_t* indices, uint32_t size);
    };

} // Gaze

#endif //GAZE_ENGINE_BUFFER_H
