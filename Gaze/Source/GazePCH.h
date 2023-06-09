#ifndef GAZE_GAZEPCH_H
#define GAZE_GAZEPCH_H

#include "Core/PlatformDetection.h"

#ifdef GZ_PLATFORM_WINDOWS
#ifndef NOMINMAX
		// See github.com/skypjack/entt/wiki/Frequently-Asked-Questions#warning-c4003-the-min-the-max-and-the-macro
		#define NOMINMAX
	#endif
#endif

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <string>
#include <sstream>
#include <array>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "Core/Base.h"

#include "Core/Log.h"

#include "Debug/Instrumentor.h"

#ifdef GZ_PLATFORM_WINDOWS
    #include <Windows.h>
#endif

#endif //GAZE_GAZEPCH_H
