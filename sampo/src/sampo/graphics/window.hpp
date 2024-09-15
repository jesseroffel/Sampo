#pragma once

#ifdef SAMPO_PLATFORM_WINDOWS
#include "platform/windows/graphics/window_win32.hpp"
namespace Sampo
{
	class Win32Window;
	using Window = Win32Window;
}
#endif // SAMPO_PLATFORM_WINDOWS