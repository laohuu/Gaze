#include "GazePCH.h"
#include "Window.h"

#ifdef GZ_PLATFORM_WINDOWS

#include "Platform/Windows/WindowsWindow.h"

#endif

namespace Gaze {

    Window* Window::Create(const WindowProps &props) {
#ifdef GZ_PLATFORM_WINDOWS
        return new WindowsWindow(props);
#else
        GZ_CORE_ASSERT(false, "Unknown platform!");
        return nullptr;
#endif
    }

}
