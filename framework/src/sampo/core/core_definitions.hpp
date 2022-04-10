#pragma once
// Core definitions file that mainly contains preprocessors and definitions that will be used throughout the project. // 
#include "sampo/core/platforms.hpp"

#ifdef SAMPO_PLATFORM_WINDOWS
	#define WIN32_LEAN_AND_MEAN
#else
	#error Sampo currently only supports Windows.
#endif // SAMPO_PLATFORM_WINDOWS

#define UNUSED(...) (void)(__VA_ARGS__)

// Wrapper around std smart pointers, inspired by Hazel. //
#include <memory>
namespace Sampo
{
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
    constexpr Ref<T> CreateRef(Args&& ... args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }
}

#include "sampo/core/log.hpp"