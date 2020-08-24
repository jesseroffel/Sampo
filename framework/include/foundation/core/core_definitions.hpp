#pragma once
// Core definitions file that mainly contains preprocessors and defitions that will be used thoughout the project. // 

#ifdef SAMPO_PLATFORM_WINDOWS
#define NOMINMAX
#else
	#error Sampo currently only supports Windows.
#endif


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