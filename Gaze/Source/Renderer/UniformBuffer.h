#ifndef GAZE_ENGINE_UNIFORMBUFFER_H
#define GAZE_ENGINE_UNIFORMBUFFER_H

#include "Core/Base.h"

namespace Gaze
{

    class UniformBuffer : public RefCounted
    {
    public:
        virtual ~UniformBuffer() {}

        virtual void SetData(const void* data, uint32_t size, uint32_t offset = 0) = 0;

        static Ref<UniformBuffer> Create(uint32_t size, uint32_t binding);
    };

} // namespace Gaze

#endif // GAZE_ENGINE_UNIFORMBUFFER_H
