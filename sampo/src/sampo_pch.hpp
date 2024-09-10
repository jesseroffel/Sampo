#pragma once
// Pre-compiled header for commonly used features from the STL library and Sampo framework // 
#include "sampo/core/platforms.hpp"

#ifdef SAMPO_PLATFORM_WINDOWS
	#ifndef NOMINMAX
		#define NOMINMAX
	#endif // NOMINMAX
#endif // SAMPO_PLATFORM_WINDOWS

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

// Platform specific includes //
#ifdef SAMPO_PLATFORM_WINDOWS
	#include <Windows.h>
#endif // SAMPO_PLATFORM_WINDOWS