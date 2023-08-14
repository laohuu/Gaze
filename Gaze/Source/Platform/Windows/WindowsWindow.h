#ifndef GAZE_ENGINE_WINDOWSWINDOW_H
#define GAZE_ENGINE_WINDOWSWINDOW_H

#include "Core/Window.h"
#include "Renderer/RendererContext.h"

#include <GLFW/glfw3.h>

namespace Gaze
{
    class WindowsWindow : public Window
    {
    public:
        WindowsWindow(const WindowProps& props);
        virtual ~WindowsWindow();

        void OnUpdate() override;

        unsigned int GetWidth() const override { return m_Data.Width; }
        unsigned int GetHeight() const override { return m_Data.Height; }

        // Window attributes
        void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
        void SetVSync(bool enabled) override;
        bool IsVSync() const override;

        virtual void* GetNativeWindow() const { return m_Window; }

        Ref<RendererContext> GetRenderContext() override { return m_RendererContext; }

    private:
        virtual void Init(const WindowProps& props);
        virtual void Shutdown();

    private:
        GLFWwindow*          m_Window;
        Ref<RendererContext> m_RendererContext;

        struct WindowData
        {
            std::string  Title;
            unsigned int Width, Height;
            bool         VSync;

            EventCallbackFn EventCallback;
        };

        WindowData m_Data;
    };
} // namespace Gaze

#endif // GAZE_ENGINE_WINDOWSWINDOW_H
