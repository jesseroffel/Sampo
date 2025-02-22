#pragma once
// Pre-compiled header for commonly used features from the STL library and Sampo framework // 
#include <algorithm>
#include <functional>
#include <iostream>
#include <memory>
#include <utility>

#include <chrono>
#include <cmath>
#include <sstream>
#include <string>
#include <string_view>
#include <random>

#include <array>
#include <list>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// Sampo related
#include "sampo/core/core_definitions.hpp"
#include "sampo/core/datatypes.hpp"

#ifdef SAMPO_ASSERT_ENABLED
#include "sampo/core/assert.hpp"
#endif // SAMPO_ASSERT_ENABLED

#define UNUSED(...) (void)(__VA_ARGS__)

// Wrapper around std smart pointers, inspired by Hazel. //
namespace Sampo
{
	template<typename T, typename ... Args>
	constexpr std::unique_ptr<T> CreateUnique(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T, typename ... Args>
	constexpr std::shared_ptr<T> CreateShared(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}

#include "sampo/core/log.hpp"

// Platform definitions
#include "platform/platform_definitions.hpp"