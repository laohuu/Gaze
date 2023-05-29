#ifndef GAZE_CORE_H
#define GAZE_CORE_H

#include <memory>

#ifdef GZ_DEBUG
#ifdef GZ_PLATFORM_WINDOWS
#define GZ_ASSERT(x, ...) { if(!(x)) { GZ_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define GZ_CORE_ASSERT(x, ...) { if(!(x)) { GZ_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); } }
#else
#define GZ_ASSERT(x, ...) { if(!(x)) { GZ_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define GZ_CORE_ASSERT(x, ...) { if(!(x)) { GZ_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); } }
#endif
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
