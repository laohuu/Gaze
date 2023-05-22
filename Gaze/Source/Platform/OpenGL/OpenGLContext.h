#ifndef GAZE_OPENGLCONTEXT_H
#define GAZE_OPENGLCONTEXT_H

#include "Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Gaze {

    class OpenGLContext : public GraphicsContext {
    public:
        OpenGLContext(GLFWwindow *windowHandle);

        virtual void Init() override;

        virtual void SwapBuffers() override;

    private:
        GLFWwindow *m_WindowHandle;
    };

} // Gaze

#endif //GAZE_OPENGLCONTEXT_H
