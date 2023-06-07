#ifndef GAZE_ENGINE_OPENGLUNIFORMBUFFER_H
#define GAZE_ENGINE_OPENGLUNIFORMBUFFER_H

#include "Renderer/UniformBuffer.h"

namespace Gaze {

    class OpenGLUniformBuffer : public UniformBuffer {
    public:
        OpenGLUniformBuffer(uint32_t size, uint32_t binding);

        virtual ~OpenGLUniformBuffer();

        virtual void SetData(const void *data, uint32_t size, uint32_t offset = 0) override;

    private:
        uint32_t m_RendererID = 0;
    };

} // Gaze

#endif //GAZE_ENGINE_OPENGLUNIFORMBUFFER_H
