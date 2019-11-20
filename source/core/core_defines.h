#pragma once

#if defined(WIN32)
#define RAKAS_PLATFORM_WINDOWS
#elif defined(WIN64)
#define RAKAS_PLATFORM_WINDOWS
#endif

#include "core/primitive_defines.h"

//Initializing
#define RAKAS_INIT_BASIC 0x01
#define RAKAS_INIT_FULL 0x02