#ifndef GAZE_CORE_H
#define GAZE_CORE_H

#include <memory>
#include "PlatformDetection.h"

#ifdef GZ_DEBUG
    #define GZ_ENABLE_ASSERTS
#else

#endif

#ifdef GZ_ENABLE_ASSERTS
    #if defined(GZ_PLATFORM_WINDOWS)
		#define GZ_DEBUGBREAK() __debugbreak()
	#elif defined(HZ_PLATFORM_LINUX)
		#include <signal.h>
		#define GZ_DEBUGBREAK() raise(SIGTRAP)
	#else
		#error "Platform doesn't support debugbreak yet!"
	#endif
    #define GZ_ASSERT(x, ...) { if(!(x)) { GZ_ERROR("Assertion Failed: {0}", __VA_ARGS__); GZ_DEBUGBREAK(); } }
    #define GZ_CORE_ASSERT(x, ...) { if(!(x)) { GZ_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); GZ_DEBUGBREAK(); } }
#else
    #define GZ_ASSERT(x, ...)
    #define GZ_CORE_ASSERT(x, ...)
#endif


#define BIT(x) (1 << x)
#define GZ_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

namespace Gaze {

    template<typename T>
    using Scope = std::unique_ptr<T>;

    template<typename T, typename ... Args>
    constexpr Scope<T> CreateScope(Args &&... args) {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    template<typename T>
    using Ref = std::shared_ptr<T>;

    template<typename T, typename ... Args>
    constexpr Ref<T> CreateRef(Args &&... args) {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }
}

#endif //GAZE_CORE_H
