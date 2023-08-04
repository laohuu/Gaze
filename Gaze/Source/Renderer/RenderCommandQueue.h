#ifndef GAZE_ENGINE_RENDERCOMMANDQUEUE_H
#define GAZE_ENGINE_RENDERCOMMANDQUEUE_H

#include <cstdint>

namespace Gaze
{
    class RenderCommandQueue
    {
    public:
        typedef void (*RenderCommandFn)(void*);

        RenderCommandQueue();
        ~RenderCommandQueue();

        void* Allocate(RenderCommandFn func, uint32_t size);

        void Execute();

    private:
        uint8_t* m_CommandBuffer;
        uint8_t* m_CommandBufferPtr;
        uint32_t m_CommandCount = 0;
    };
} // namespace Gaze

#endif // GAZE_ENGINE_RENDERCOMMANDQUEUE_H
