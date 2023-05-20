#ifndef GAZE_CORE_H
#define GAZE_CORE_H

//#define GZ_API __declspec(dllexport)
#define GZ_API

#include <memory>

#ifdef GZ_DEBUG
    #define GZ_ASSERT(x, ...) { if(!(x)) { MTR_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define GZ_CORE_ASSERT(x, ...) { if(!(x)) { MTR_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
    #define GZ_ASSERT(x, ...)
    #define GZ_CORE_ASSERT(x, ...)
#endif


#define BIT(x) (1 << x)

#endif //GAZE_CORE_H
