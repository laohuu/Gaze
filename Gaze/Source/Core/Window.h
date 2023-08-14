#ifndef GAZE_ENGINE_WINDOW_H
#define GAZE_ENGINE_WINDOW_H

#include "Core/Base.h"
#include "Events/Event.h"

#include "Renderer/RendererContext.h"

#include <sstream>

namespace Gaze
{
    struct WindowProps
    {
        std::string Title;
        uint32_t    Width;
        uint32_t    Height;

        WindowProps(const std::string& title = "Gaze Engine", uint32_t width = 1280, uint32_t height = 720) :
            Title(title), Width(width), Height(height)
        {}
    };

    // Interface representing a desktop system based Window
    class Window
    {
    public:
        using EventCallbackFn = std::function<void(Event&)>;

        virtual ~Window() = default;

        virtual void OnUpdate() = 0;

        virtual uint32_t GetWidth() const = 0;

        virtual uint32_t GetHeight() const = 0;

        // Window attributes
        virtual void SetEventCallback(const EventCallbackFn& callback) = 0;

        virtual void SetVSync(bool enabled) = 0;

        virtual bool IsVSync() const = 0;

        virtual void* GetNativeWindow() const = 0;

        static Window* Create(const WindowProps& props = WindowProps());

        virtual Ref<RendererContext> GetRenderContext() = 0;
    };
} // namespace Gaze

#endif // GAZE_ENGINE_WINDOW_H
