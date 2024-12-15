#include "sampo/core/core_definitions.hpp"

#ifdef SAMPO_PLATFORM_WINDOWS
	#include <Windows.h>
#endif // SAMPO_PLATFORM_WINDOWS

#define BIND_EVENT_FN(x, obj) std::bind(&x, obj, std::placeholders::_1)