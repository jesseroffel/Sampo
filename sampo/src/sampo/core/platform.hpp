#pragma once
#ifdef SAMPO_PLATFORM_WINDOWS
#include "platform/windows/core/platform_win32.hpp"
namespace Sampo
{
	using Platform = Win32Platform;
	using Window = Win32Window;
}
#endif // SAMPO_PLATFORM_WINDOWS