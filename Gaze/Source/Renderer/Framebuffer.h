#ifndef GAZE_ENGINE_FRAMEBUFFER_H
#define GAZE_ENGINE_FRAMEBUFFER_H

#include "Core/Base.h"

namespace Gaze {

    struct FramebufferSpecification {
        uint32_t Width = 0, Height = 0;
        // FramebufferFormat Format =
        uint32_t Samples = 1;

        bool SwapChainTarget = false;
    };

    class Framebuffer {
    public:
        virtual ~Framebuffer() = default;

        virtual void Bind() = 0;

        virtual void Unbind() = 0;

        virtual uint32_t GetColorAttachmentRendererID() const = 0;

        virtual const FramebufferSpecification &GetSpecification() const = 0;

        static Gaze::Ref<Framebuffer> Create(const FramebufferSpecification &spec);
    };

} // Gaze

#endif //GAZE_ENGINE_FRAMEBUFFER_H
