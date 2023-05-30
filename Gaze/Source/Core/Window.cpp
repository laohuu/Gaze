#include "GazePCH.h"
#include "Window.h"

#ifdef GZ_PLATFORM_WINDOWS

#include "Platform/Windows/WindowsWindow.h"

#endif

namespace Gaze {

    Gaze::Scope<Window> Window::Create(const WindowProps &props) {
#ifdef GZ_PLATFORM_WINDOWS
        return CreateScope<WindowsWindow>(props);
#else
        GZ_CORE_ASSERT(false, "Unknown platform!");
        return nullptr;
#endif
    }

}
