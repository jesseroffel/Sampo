#pragma once
#include "platforms.hpp"

#ifdef SAMPO_PLATFORM_WINDOWS
#include "platform/windows/core/platform_win32.hpp"
namespace Sampo
{
	using Platform = Win32Platform;
}
#endif // SAMPO_PLATFORM_WINDOWS