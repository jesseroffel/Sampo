# Sampo #

# include common directory #
include_directories(${PROJECT_SOURCE_DIR}/sampo/src)
include_directories(${PROJECT_SOURCE_DIR}/sampo/vendor/spdlog/include)

add_library(sampo STATIC 
	"src/sampo.hpp" "src/sampo_pch.hpp" "src/sampo_pch.cpp" "src/sampo/core/console_arguments.hpp" "src/sampo/core/datatypes.hpp" "src/sampo/core/application.hpp" "src/sampo/core/application.cpp" "src/sampo/core/core_definitions.hpp" "src/sampo/core/layer.hpp" "src/sampo/core/layer.cpp" "src/sampo/core/log.hpp" "src/sampo/core/log.cpp" "src/sampo/core/platforms.hpp" "src/sampo/core/console_arguments.cpp" "src/sampo/core/assert.hpp" "src/sampo/core/platform.hpp" "src/sampo/graphics/window.hpp")

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

	add_subdirectory(${PROJECT_SOURCE_DIR}/sampo/vendor/GLFW)

	target_sources(sampo PUBLIC 
	"src/platform/windows/core/platform_win32.hpp" "src/platform/windows/core/platform_win32.cpp" "src/platform/windows/graphics/window_win32.hpp" "src/platform/windows/graphics/window_win32.cpp")
	
	target_link_libraries(sampo glfw)
	target_link_libraries(sampo opengl32.lib)
endif()

# Compiler version specifics #
if (MSVC)
	target_compile_options(sampo PUBLIC /MP)
	target_compile_options(sampo PRIVATE /W4 /WX)
else()
	target_compile_options(sampo PRIVATE -Wall -Wextra -pedantic -Werror)
endif()