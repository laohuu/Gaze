#ifndef GAZE_CORE_H
#define GAZE_CORE_H

#include "PlatformDetection.h"
#include <memory>
#include "Ref.h"

#ifdef GZ_DEBUG
    #if defined(GZ_PLATFORM_WINDOWS)
        #define GZ_DEBUGBREAK() __debugbreak()
    #elif defined(GZ_PLATFORM_LINUX)
        #include <signal.h>
        #define GZ_DEBUGBREAK() raise(SIGTRAP)
    #else
        #error "Platform doesn't support debugbreak yet!"
    #endif
    #define GZ_ENABLE_ASSERTS
#else
#define GZ_DEBUGBREAK()
#endif

#define GZ_EXPAND_MACRO(x) x
#define GZ_STRINGIFY_MACRO(x) #x


#define BIT(x) (1 << x)
#define GZ_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

namespace Gaze {

    template<typename T>
    using Scope = std::unique_ptr<T>;

    template<typename T, typename ... Args>
    constexpr Scope<T> CreateScope(Args &&... args) {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

//    template<typename T>
//    using Ref = std::shared_ptr<T>;
//
//    template<typename T, typename ... Args>
//    constexpr Ref<T> CreateRef(Args &&... args) {
//        return std::make_shared<T>(std::forward<Args>(args)...);
//    }
}

#include "Core/Log.h"
#include "Core/Assert.h"

#endif //GAZE_CORE_H
