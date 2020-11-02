#pragma once
// Precompiled header for commonly used features from the STL library and Sampo framework // 

// STL //
#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>
#include <string>
#include <string_view>
#include <sstream>
#include <chrono>
#include <random>
#include <cmath>

#include <array>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>

// Sampo //

// Platform specific includes //
#ifdef SAMPO_PLATFORM_WINDOWS
	#include <Windows.h>
#endif