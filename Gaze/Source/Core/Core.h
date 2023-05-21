#ifndef GAZE_CORE_H
#define GAZE_CORE_H

#include <memory>

#ifdef GZ_DEBUG
    #define GZ_ASSERT(x, ...) { if(!(x)) { GZ_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define GZ_CORE_ASSERT(x, ...) { if(!(x)) { GZ_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
    #define GZ_ASSERT(x, ...)
    #define GZ_CORE_ASSERT(x, ...)
#endif


#define BIT(x) (1 << x)

#define GZ_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

#endif //GAZE_CORE_H
