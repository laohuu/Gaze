#ifndef GAZE_ENGINE_ASSERT_H
#define GAZE_ENGINE_ASSERT_H

#include "Core/Base.h"
#include "Core/Log.h"
#include <filesystem>

#ifdef GZ_ENABLE_ASSERTS
// Alteratively we could use the same "default" message for both "WITH_MSG" and "NO_MSG" and
	// provide support for custom formatting by concatenating the formatting string instead of having the format inside the default message
	#define GZ_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { GZ##type##ERROR(msg, __VA_ARGS__); GZ_DEBUGBREAK(); } }
	#define GZ_INTERNAL_ASSERT_WITH_MSG(type, check, ...) GZ_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
	#define GZ_INTERNAL_ASSERT_NO_MSG(type, check) GZ_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", GZ_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

	#define GZ_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
	#define GZ_INTERNAL_ASSERT_GET_MACRO(...) GZ_EXPAND_MACRO( GZ_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, GZ_INTERNAL_ASSERT_WITH_MSG, GZ_INTERNAL_ASSERT_NO_MSG) )

	// Currently accepts at least the condition and one additional parameter (the message) being optional
	#define GZ_ASSERT(...) GZ_EXPAND_MACRO( GZ_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
	#define GZ_CORE_ASSERT(...) GZ_EXPAND_MACRO( GZ_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )
#else
    #define GZ_ASSERT(...)
    #define GZ_CORE_ASSERT(...)
#endif

#endif //GAZE_ENGINE_ASSERT_H
