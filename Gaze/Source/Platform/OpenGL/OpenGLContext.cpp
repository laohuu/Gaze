#include "GazePCH.h"

#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Gaze
{
    OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : m_WindowHandle(windowHandle)
    {
        GZ_CORE_INFO("OpenGLContext is created");
        GZ_CORE_ASSERT(windowHandle, "Window handle is null!")
    }

    OpenGLContext::~OpenGLContext() {}

    void OpenGLContext::Create()
    {
        glfwMakeContextCurrent(m_WindowHandle);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        GZ_CORE_ASSERT(status, "Failed to initialize Glad!");

        GZ_CORE_INFO("OpenGL Info:");
        GZ_CORE_INFO("  Vendor: {0}", (char*)glGetString(GL_VENDOR));
        GZ_CORE_INFO("  Renderer: {0}", (char*)glGetString(GL_RENDERER));
        GZ_CORE_INFO("  Version: {0}", (char*)glGetString(GL_VERSION));

        GZ_CORE_ASSERT(GLVersion.major > 4 || (GLVersion.major == 4 && GLVersion.minor >= 5),
                       "Hazel requires at least OpenGL version 4.5!");
    }

    void OpenGLContext::SwapBuffers() { glfwSwapBuffers(m_WindowHandle); }
} // namespace Gaze