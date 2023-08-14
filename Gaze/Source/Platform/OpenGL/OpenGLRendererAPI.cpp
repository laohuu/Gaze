#include "GazePCH.h"

#include "OpenGLRendererAPI.h"

#include <glad/glad.h>

namespace Gaze
{
    struct OpenGLRendererData
    {
        RendererCapabilities RenderCaps;
    };

    static OpenGLRendererData* s_Data = nullptr;

    void OpenGLMessageCallback(unsigned    source,
                               unsigned    type,
                               unsigned    id,
                               unsigned    severity,
                               int         length,
                               const char* message,
                               const void* userParam)
    {
        switch (severity)
        {
            case GL_DEBUG_SEVERITY_HIGH:
                GZ_CORE_CRITICAL(message);
                return;
            case GL_DEBUG_SEVERITY_MEDIUM:
                GZ_CORE_ERROR(message);
                return;
            case GL_DEBUG_SEVERITY_LOW:
                GZ_CORE_WARN(message);
                return;
            case GL_DEBUG_SEVERITY_NOTIFICATION:
                GZ_CORE_TRACE(message);
                return;
        }

        GZ_CORE_ASSERT(false, "Unknown severity level!");
    }

    void OpenGLRendererAPI::Init()
    {
        GZ_PROFILE_FUNCTION();
        s_Data = new OpenGLRendererData();

#ifdef GZ_DEBUG
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(OpenGLMessageCallback, nullptr);

        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, nullptr, GL_FALSE);
#endif

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_LINE_SMOOTH);

        auto& caps   = s_Data->RenderCaps;
        caps.Vendor  = (const char*)glGetString(GL_VENDOR);
        caps.Device  = (const char*)glGetString(GL_RENDERER);
        caps.Version = (const char*)glGetString(GL_VERSION);
    }

    void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
    {
        glViewport(x, y, width, height);
    }

    void OpenGLRendererAPI::SetClearColor(const glm::vec4& color) { glClearColor(color.r, color.g, color.b, color.a); }

    void OpenGLRendererAPI::Clear() { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }

    void OpenGLRendererAPI::DrawIndexed(const Gaze::Ref<VertexArray>& vertexArray, uint32_t indexCount)
    {
        vertexArray->Bind();
        uint32_t count = indexCount ? indexCount : vertexArray->GetIndexBuffer()->GetCount();
        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void OpenGLRendererAPI::DrawLines(const Ref<VertexArray>& vertexArray, uint32_t vertexCount)
    {
        vertexArray->Bind();
        glDrawArrays(GL_LINES, 0, vertexCount);
    }

    void OpenGLRendererAPI::SetLineWidth(float width) { glLineWidth(width); }

    RendererCapabilities& OpenGLRendererAPI::GetCapabilities() { return s_Data->RenderCaps; }
} // namespace Gaze