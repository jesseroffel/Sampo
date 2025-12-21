#pragma once
//* Common aliases for common datatypes
#ifdef SAMPO_PLATFORM_WINDOWS
#include <stdint.h>

using int8 = __int8;
using uint8 = unsigned __int8;
using int16 = __int16;
using uint16 = unsigned __int16;
using int32 = __int32;
using uint32 = unsigned __int32;
using int64 = __int64;
using uint64 = unsigned __int64;

#define int8_min INT8_MIN
#define int16_min INT16_MIN
#define int32_min INT32_MIN
#define int64_min INT64_MIN
#define int8_max INT8_MAX
#define int16_max INT16_MAX
#define int32_max INT32_MAX
#define int64_max INT64_MAX

#define uint8_max UINT8_MAX
#define uint16_max UINT16_MAX
#define uint32_max UINT32_MAX
#define uint64_max UINT64_MAX
#endif //SAMPO_PLATFORM_WINDOWS