# Sampo #

# include common directory #
include_directories(${PROJECT_SOURCE_DIR}/sampo/src)

add_library(sampo STATIC 
	"src/sampo.hpp" "src/sampo_pch.hpp" "src/sampo_pch.cpp" "src/sampo/core/console_arguments.hpp" "src/sampo/core/datatypes.hpp" "src/sampo/core/application.hpp" "src/sampo/core/application.cpp" "src/sampo/core/core_definitions.hpp" "src/sampo/core/layer.hpp" "src/sampo/core/layer.cpp" "src/sampo/core/log.hpp" "src/sampo/core/log.cpp" "src/sampo/core/platforms.hpp" "src/sampo/core/console_arguments.cpp" "src/sampo/core/assert.hpp" "src/sampo/core/platform.hpp" "src/sampo/graphics/window.hpp" "src/sampo/events/event.hpp" "src/sampo/events/application_event.hpp" "src/sampo/events/key_event.hpp" "src/sampo/events/mouse_event.hpp")

# Overrides globals #
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib/sampo/${outputdir})

# Configure solution #
target_precompile_headers(sampo PUBLIC src/sampo_pch.cpp)

# Compile settings #
target_compile_features(sampo PUBLIC cxx_std_20)

# Platform specifics #
if (WIN32)

	# Library source includes
	target_include_directories(sampo PUBLIC ${PROJECT_SOURCE_DIR}/sampo/src/platform)

	# Library includes
	add_subdirectory(${PROJECT_SOURCE_DIR}/sampo/vendor/GLFW)
	add_subdirectory(${PROJECT_SOURCE_DIR}/sampo/vendor/glad)
	add_subdirectory(${PROJECT_SOURCE_DIR}/sampo/vendor/spdlog)

	target_sources(sampo PUBLIC 
	"src/platform/windows/core/platform_win32.hpp" "src/platform/windows/core/platform_win32.cpp" "src/platform/windows/graphics/window_win32.hpp" "src/platform/windows/graphics/window_win32.cpp")
	
	# Link included libraries
	target_link_libraries(sampo PUBLIC glfw)
	target_link_libraries(sampo PUBLIC glad)
	target_link_libraries(sampo PUBLIC opengl32.lib)
	target_link_libraries(sampo PUBLIC spdlog::spdlog)

	add_compile_definitions(sampo PUBLIC SAMPO_PLATFORM_WINDOWS)
	add_compile_definitions(sampo PUBLIC GLFW_INCLUDE_NONE)
endif()

# Compiler version specifics #
if (MSVC)
	target_compile_options(sampo PUBLIC /MP)
	target_compile_options(sampo PUBLIC /W4 /WX)
else()
	target_compile_options(sampo PUBLIC -Wall -Wextra -pedantic -Werror)
endif()