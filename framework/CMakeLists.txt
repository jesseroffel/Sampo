# Framework #

# include common directory #
include_directories(${PROJECT_SOURCE_DIR}/framework/src)
include_directories(${PROJECT_SOURCE_DIR}/framework/vendor/spdlog/include)

add_library(framework STATIC 
    "src/sampo.hpp" "src/sampo_pch.hpp" "src/sampo_pch.cpp" "src/sampo/core/console_arguments.hpp" "src/sampo/core/datatypes.hpp" "src/sampo/core/application.hpp" "src/sampo/core/application.cpp" "src/sampo/core/core_definitions.hpp" "src/sampo/core/entry_point.hpp" "src/sampo/core/layer.hpp" "src/sampo/core/layer.cpp" "src/sampo/core/log.hpp" "src/sampo/core/log.cpp" "src/sampo/core/platforms.hpp" "src/sampo/debugging/new_tracker.hpp" "src/sampo/io/file_states.hpp" "src/sampo/io/file_system.hpp" "src/sampo/math/vector3_io.hpp" "src/sampo/math/vector3_io.cpp" "src/sampo/math/vector3.hpp" "src/sampo/memory/allocator.hpp" "src/sampo/memory/allocator_pmr.hpp" "src/sampo/memory/allocator_pmr.cpp" "src/sampo/memory/callocator.hpp" "src/sampo/memory/callocator.cpp" "src/sampo/memory/linear_allocator.hpp" "src/sampo/memory/linear_allocator.cpp" "src/sampo/memory/memory_benchmark.hpp" "src/sampo/memory/memory_benchmark.cpp" "src/sampo/network/network_core.hpp" "src/sampo/network/network_definitions.hpp" "src/sampo/network/socket.hpp" "src/sampo/network/socket_address.hpp" "src/sampo/network/socket_address_factory.hpp" "src/sampo/network/socket_api.hpp" "src/sampo/network/socket_api.cpp" "src/sampo/network/socket_util.hpp"  "src/sampo/network/tcp_socket.hpp" "src/sampo/network/udp_socket.hpp" "src/sampo/core/console_arguments.cpp" "src/sampo/core/assert.hpp")

# Overrides globals #
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib/framework/${outputdir})

# Configure solution # 
target_precompile_headers(framework PUBLIC src/sampo_pch.cpp)

# Compile settings # 
target_compile_features(framework PRIVATE cxx_std_20)

# Platform specifics # 
if (WIN32)
    add_compile_definitions(framework PRIVATE SAMPO_PLATFORM_WINDOWS)

    include_directories(${PROJECT_SOURCE_DIR}/framework/src/platform)
    target_sources(framework PUBLIC 
		"src/platform/windows/io/windows_file_system.cpp" "src/platform/windows/io/windows_string_helper.hpp" "src/platform/windows/network/windows_socket.cpp" "src/platform/windows/network/windows_socket_address.hpp" "src/platform/windows/network/windows_socket_address_factory.hpp" "src/platform/windows/network/windows_socket_api.hpp" "src/platform/windows/network/windows_socket_api.cpp" "src/platform/windows/network/windows_socket_util.hpp" "src/platform/windows/network/windows_tcp_socket.hpp" "src/platform/windows/network/windows_tcp_socket.cpp" "src/platform/windows/network/windows_udp_socket.hpp" "src/platform/windows/network/windows_udp_socket.cpp") 
endif()

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(framework PUBLIC /MP)
    target_compile_options(framework PRIVATE /W4 /WX)
else()
    target_compile_options(framework PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

