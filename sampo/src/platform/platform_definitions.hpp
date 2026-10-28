#include "sampo/core/core_definitions.hpp"

#ifdef SAMPO_PLATFORM_WINDOWS
	#include <Windows.h>

	// AUDIO (miniaudio)
	#define MA_NO_ENCODING
	#define MA_NO_FLAC
	#define MA_NO_MP3
	#define MA_NO_GENERATION
#endif // SAMPO_PLATFORM_WINDOWS

#define BIND_EVENT_FN(x, obj) std::bind(&x, obj, std::placeholders::_1)