# Demo #

# include and create #
include_directories(${PROJECT_SOURCE_DIR}/demo/src)
include_directories(${PROJECT_SOURCE_DIR}/sampo/src)

add_executable(demo
	"src/main_win32.cpp"
	"src/demo_layer.hpp"
	"src/demo_layer.cpp"
	"src/renderer2D_layer.hpp"
	"src/renderer2D_layer.cpp")

# Overrides globals #
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin/demo/${outputdir})

# Configure solution #
set_property (DIRECTORY PROPERTY VS_STARTUP_PROJECT "demo")

# Compile settings #
target_compile_features(demo PUBLIC cxx_std_20)
target_link_libraries(demo PUBLIC sampo)

# Platform specifics #

# Compiler version specifics # 
if (MSVC)
	target_compile_options(demo PUBLIC /MP)
endif()