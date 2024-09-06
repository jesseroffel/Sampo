# Sampo #

# include common directory #
include_directories(${PROJECT_SOURCE_DIR}/sampo/src)
include_directories(${PROJECT_SOURCE_DIR}/sampo/vendor/spdlog/include)

add_library(sampo STATIC 
	"src/sampo.hpp" "src/sampo_pch.hpp" "src/sampo_pch.cpp" "src/sampo/core/console_arguments.hpp" "src/sampo/core/datatypes.hpp" "src/sampo/core/application.hpp" "src/sampo/core/application.cpp" "src/sampo/core/core_definitions.hpp" "src/sampo/core/entry_point.hpp" "src/sampo/core/layer.hpp" "src/sampo/core/layer.cpp" "src/sampo/core/log.hpp" "src/sampo/core/log.cpp" "src/sampo/core/platforms.hpp" "src/sampo/debugging/new_tracker.hpp" "src/sampo/io/file_states.hpp" "src/sampo/io/file_system.hpp" "src/sampo/math/vector3_io.hpp" "src/sampo/math/vector3_io.cpp" "src/sampo/math/vector3.hpp" "src/sampo/memory/allocator.hpp" "src/sampo/memory/allocator_pmr.hpp" "src/sampo/memory/allocator_pmr.cpp" "src/sampo/memory/callocator.hpp" "src/sampo/memory/callocator.cpp" "src/sampo/memory/linear_allocator.hpp" "src/sampo/memory/linear_allocator.cpp" "src/sampo/memory/memory_benchmark.hpp" "src/sampo/memory/memory_benchmark.cpp" "src/sampo/network/network_core.hpp" "src/sampo/network/network_definitions.hpp" "src/sampo/network/socket.hpp" "src/sampo/network/socket_address.hpp" "src/sampo/network/socket_address_factory.hpp" "src/sampo/network/socket_api.hpp" "src/sampo/network/socket_api.cpp" "src/sampo/network/socket_util.hpp"  "src/sampo/network/tcp_socket.hpp" "src/sampo/network/udp_socket.hpp" "src/sampo/core/console_arguments.cpp" "src/sampo/core/assert.hpp" "src/sampo/core/game.hpp" "src/sampo/core/game.cpp")

# Overrides globals #
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib/sampo/${outputdir})

# Configure solution # 
target_precompile_headers(sampo PUBLIC src/sampo_pch.cpp)

# Compile settings # 
target_compile_features(sampo PRIVATE cxx_std_20)

# Platform specifics # 
if (WIN32)
add_compile_definitions(sampo PRIVATE SAMPO_PLATFORM_WINDOWS)

include_directories(${PROJECT_SOURCE_DIR}/sampo/src/platform)
target_sources(sampo PUBLIC 
	"src/platform/windows/game_win32.hpp" "src/platform/windows/io/windows_file_system.cpp" "src/platform/windows/io/windows_string_helper.hpp" )
endif()

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	target_compile_options(sampo PUBLIC /MP)
	target_compile_options(sampo PRIVATE /W4 /WX)
else()
	target_compile_options(sampo PRIVATE -Wall -Wextra -pedantic -Werror)
endif()