# Sampo #

# include common directory #
include_directories(${PROJECT_SOURCE_DIR}/sampo/src)

# Overrides globals #
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib/sampo/${outputdir})
set(SAMPO_SOURCE_DIR ${PROJECT_SOURCE_DIR}/sampo/src/sampo)
set(VENDOR_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/sampo/vendor)

add_library(sampo STATIC 
	src/sampo.hpp
	src/sampo_pch.hpp
	src/sampo_pch.cpp
	${SAMPO_SOURCE_DIR}/core/console_arguments.hpp
	${SAMPO_SOURCE_DIR}/core/datatypes.hpp
	${SAMPO_SOURCE_DIR}/core/application.hpp
	${SAMPO_SOURCE_DIR}/core/application.cpp
	${SAMPO_SOURCE_DIR}/core/core_definitions.hpp
	${SAMPO_SOURCE_DIR}/core/layer.hpp
	${SAMPO_SOURCE_DIR}/core/layer.cpp
	${SAMPO_SOURCE_DIR}/core/log.hpp
	${SAMPO_SOURCE_DIR}/core/log.cpp
	${SAMPO_SOURCE_DIR}/core/console_arguments.cpp
	${SAMPO_SOURCE_DIR}/core/assert.hpp
	${SAMPO_SOURCE_DIR}/core/platform.hpp
	${SAMPO_SOURCE_DIR}/debugging/imgui_layer.hpp
	${SAMPO_SOURCE_DIR}/debugging/imgui_layer.cpp
	${SAMPO_SOURCE_DIR}/events/event.hpp
	${SAMPO_SOURCE_DIR}/events/application_event.hpp
	${SAMPO_SOURCE_DIR}/events/key_event.hpp
	${SAMPO_SOURCE_DIR}/events/mouse_event.hpp
	${SAMPO_SOURCE_DIR}/graphics/window.hpp
	${SAMPO_SOURCE_DIR}/input/mouse.hpp
	${SAMPO_SOURCE_DIR}/input/mouse.cpp
	${SAMPO_SOURCE_DIR}/input/input.hpp
	${SAMPO_SOURCE_DIR}/input/input.cpp
	${SAMPO_SOURCE_DIR}/input/input_mapping.hpp
	${SAMPO_SOURCE_DIR}/input/keyboard.hpp
	${SAMPO_SOURCE_DIR}/input/keyboard.cpp)

# Configure solution #
target_precompile_headers(sampo PUBLIC src/sampo_pch.cpp)

# Compile settings #
target_compile_features(sampo PUBLIC cxx_std_20)

# Platform specifics #
if (WIN32)
	set(PLATFORM_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/sampo/src/platform)

	# Library source includes
	target_include_directories(sampo PUBLIC ${PROJECT_SOURCE_DIR}/sampo/src/platform)
	target_include_directories(sampo PUBLIC ${VENDOR_INCLUDE_DIR}/imgui)

	# Library includes
	add_subdirectory(${VENDOR_INCLUDE_DIR}/GLFW)
	add_subdirectory(${VENDOR_INCLUDE_DIR}/glad)
	add_subdirectory(${VENDOR_INCLUDE_DIR}/spdlog)
	add_subdirectory(${VENDOR_INCLUDE_DIR}/glm)

	target_sources(sampo PUBLIC 
		src/platform/platform_definitions.hpp
		${PLATFORM_INCLUDE_DIR}/windows/core/platform_win32.hpp
		${PLATFORM_INCLUDE_DIR}/windows/core/platform_win32.cpp
		${PLATFORM_INCLUDE_DIR}/windows/graphics/window_win32.hpp
		${PLATFORM_INCLUDE_DIR}/windows/graphics/window_win32.cpp
		${PLATFORM_INCLUDE_DIR}/windows/input/mouse_win32.cpp
		${PLATFORM_INCLUDE_DIR}/windows/input/keyboard_win32.cpp
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