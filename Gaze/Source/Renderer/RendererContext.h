#ifndef GAZE_ENGINE_RENDERERCONTEXT_H
#define GAZE_ENGINE_RENDERERCONTEXT_H

#include "Core/Ref.h"

struct GLFWwindow;

namespace Gaze
{
    class RendererContext : public RefCounted
    {
    public:
        RendererContext()          = default;
        virtual ~RendererContext() = default;

        virtual void Create()      = 0;
        virtual void BeginFrame()  = 0;
        virtual void SwapBuffers() = 0;

        virtual void OnResize(uint32_t width, uint32_t height) = 0;

        static Ref<RendererContext> Create(GLFWwindow* windowHandle);
    };
} // namespace Gaze

#endif // GAZE_ENGINE_RENDERERCONTEXT_H
