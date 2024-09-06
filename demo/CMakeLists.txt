# Demo #

# include and create #
include_directories(${PROJECT_SOURCE_DIR}/demo/src)
include_directories(${PROJECT_SOURCE_DIR}/sampo/src)
include_directories(${PROJECT_SOURCE_DIR}/sampo/vendor/spdlog/include)

add_executable(demo "src/main_win32.cpp")

# Overrides globals #
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin/demo/${outputdir})

# Configure solution # 
set_property (DIRECTORY PROPERTY VS_STARTUP_PROJECT "demo")

# Compile settings # 
target_compile_features(demo PUBLIC cxx_std_20)
target_link_libraries(demo PUBLIC sampo)


# Platform specifics #  
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	target_compile_options(demo PUBLIC /MP)
	target_compile_options(demo PRIVATE /W4)
	add_compile_definitions(demo PRIVATE SAMPO_PLATFORM_WINDOWS)

include_directories(${PROJECT_SOURCE_DIR}/sampo/src/platform/windows)
endif()