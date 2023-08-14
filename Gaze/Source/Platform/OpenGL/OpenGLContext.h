#ifndef GAZE_OPENGLCONTEXT_H
#define GAZE_OPENGLCONTEXT_H

#include "Renderer/RendererContext.h"

struct GLFWwindow;

namespace Gaze
{
    class OpenGLContext : public RendererContext
    {
    public:
        OpenGLContext(GLFWwindow* windowHandle);
        virtual ~OpenGLContext();

        virtual void Create() override;
        virtual void BeginFrame() override {}
        virtual void SwapBuffers() override;
        virtual void OnResize(uint32_t width, uint32_t height) override {}

    private:
        GLFWwindow* m_WindowHandle;
    };
} // namespace Gaze

#endif // GAZE_OPENGLCONTEXT_H
