# Sampo #

# include common directory #
include_directories(${PROJECT_SOURCE_DIR}/sampo/src)

# Overrides globals #
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib/sampo/${outputdir})
set(VENDOR_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/sampo/vendor)

add_library(sampo STATIC 
	"src/sampo.hpp"
	"src/sampo_pch.hpp"
	"src/sampo_pch.cpp"
	"src/sampo/core/console_arguments.hpp"
	"src/sampo/core/datatypes.hpp"
	"src/sampo/core/application.hpp"
	"src/sampo/core/application.cpp"
	"src/sampo/core/core_definitions.hpp"
	"src/sampo/core/layer.hpp"
	"src/sampo/core/layer.cpp"
	"src/sampo/core/log.hpp"
	"src/sampo/core/log.cpp"
	"src/sampo/core/console_arguments.cpp"
	"src/sampo/core/assert.hpp"
	"src/sampo/core/platform.hpp"
	"src/sampo/debugging/imgui_layer.hpp"
	"src/sampo/debugging/imgui_layer.cpp"
	"src/sampo/events/event.hpp"
	"src/sampo/events/application_event.hpp"
	"src/sampo/events/key_event.hpp"
	"src/sampo/events/mouse_event.hpp"
	"src/sampo/events/gamepad_event.hpp"
	"src/sampo/graphics/buffer.hpp"
	"src/sampo/graphics/buffer.cpp"
	"src/sampo/graphics/graphics_context.hpp"
	"src/sampo/graphics/renderer.cpp"
	"src/sampo/graphics/shader.hpp"
	"src/sampo/graphics/shader.cpp"
	"src/sampo/graphics/vertex_array.hpp"
	"src/sampo/graphics/vertex_array.cpp"
	"src/sampo/graphics/window.hpp"
	"src/sampo/input/mouse.hpp"
	"src/sampo/input/mouse.cpp"
	"src/sampo/input/input.hpp"
	"src/sampo/input/input.cpp"
	"src/sampo/input/input_mapping.hpp"
	"src/sampo/input/keyboard.hpp"
	"src/sampo/input/keyboard.cpp"
	"src/sampo/input/gamepad.hpp"
	"src/sampo/input/gamepad.cpp")

# Configure solution #
target_precompile_headers(sampo PUBLIC src/sampo_pch.cpp)

# Compile settings #
target_compile_features(sampo PUBLIC cxx_std_20)

# Platform specifics #
if (WIN32)
	# Library source includes
	target_include_directories(sampo PUBLIC ${PROJECT_SOURCE_DIR}/sampo/src/platform)
	target_include_directories(sampo PUBLIC ${VENDOR_INCLUDE_DIR}/imgui)

	# Library includes
	add_subdirectory(${VENDOR_INCLUDE_DIR}/GLFW)
	add_subdirectory(${VENDOR_INCLUDE_DIR}/glad)
	add_subdirectory(${VENDOR_INCLUDE_DIR}/spdlog)
	add_subdirectory(${VENDOR_INCLUDE_DIR}/glm)

	target_sources(sampo PUBLIC 
		"src/platform/platform_definitions.hpp"
		"src/platform/opengl/opengl_buffer.hpp"
		"src/platform/opengl/opengl_buffer.cpp"
		"src/platform/opengl/opengl_context.hpp"
		"src/platform/opengl/opengl_context.cpp"
		"src/platform/opengl/opengl_vertex_array.hpp"
		"src/platform/opengl/opengl_vertex_array.cpp"
		"src/platform/windows/core/platform_win32.hpp"
		"src/platform/windows/core/platform_win32.cpp"
		"src/platform/windows/graphics/window_win32.hpp"
		"src/platform/windows/graphics/window_win32.cpp"
		"src/platform/windows/input/mouse_win32.cpp"
		"src/platform/windows/input/keyboard_win32.cpp"
		"src/platform/windows/input/gamepad_win32.cpp"
		"src/platform/windows/input/input_win32.hpp"
		"src/platform/windows/input/input_win32.cpp"

		${VENDOR_INCLUDE_DIR}/imgui/imgui.h
		${VENDOR_INCLUDE_DIR}/imgui/imgui.cpp
		${VENDOR_INCLUDE_DIR}/imgui/imgui_draw.cpp
		${VENDOR_INCLUDE_DIR}/imgui/imgui_tables.cpp
		${VENDOR_INCLUDE_DIR}/imgui/imgui_widgets.cpp
		${VENDOR_INCLUDE_DIR}/imgui/imgui_demo.cpp
		${VENDOR_INCLUDE_DIR}/imgui/backends/imgui_impl_opengl3.h
		${VENDOR_INCLUDE_DIR}/imgui/backends/imgui_impl_opengl3.cpp
		${VENDOR_INCLUDE_DIR}/imgui/backends/imgui_impl_glfw.h
		${VENDOR_INCLUDE_DIR}/imgui/backends/imgui_impl_glfw.cpp
	)
	
	# Link included libraries
	target_link_libraries(sampo PUBLIC glfw)
	target_link_libraries(sampo PUBLIC glad)
	target_link_libraries(sampo PUBLIC opengl32.lib)
	target_link_libraries(sampo PUBLIC spdlog::spdlog)
	target_link_libraries(sampo PUBLIC glm::glm-header-only)

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