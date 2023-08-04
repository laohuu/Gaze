#ifndef GAZE_ENGINE_RENDERPASS_H
#define GAZE_ENGINE_RENDERPASS_H

#include "Core/Base.h"

#include "Framebuffer.h"

namespace Gaze
{
    struct RenderPassSpecification
    {
        Ref<Framebuffer> TargetFramebuffer;
    };

    class RenderPass : public RefCounted
    {
    public:
        virtual ~RenderPass() = default;

        virtual RenderPassSpecification&       GetSpecification()       = 0;
        virtual const RenderPassSpecification& GetSpecification() const = 0;

        static Ref<RenderPass> Create(const RenderPassSpecification& spec);
    };
} // namespace Gaze

#endif // GAZE_ENGINE_RENDERPASS_H
