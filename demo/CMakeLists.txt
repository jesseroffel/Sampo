# Demo #

# include and create #
include_directories(${PROJECT_SOURCE_DIR}/demo/src)
include_directories(${PROJECT_SOURCE_DIR}/framework/src)
include_directories(${PROJECT_SOURCE_DIR}/framework/vendor/spdlog/include)

add_executable(demo src/demo.cpp "src/demolayer.hpp" "src/demolayer.cpp" "src/networktest.hpp" "src/networktest.cpp" "src/mathtests.hpp" "src/mathtests.cpp")

# Overrides globals #
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin/demo/${outputdir})

# Configure solution # 
set_property (DIRECTORY PROPERTY VS_STARTUP_PROJECT "demo")

# Compile settings # 
target_compile_features(demo PUBLIC cxx_std_17)
target_link_libraries(demo PUBLIC framework)


# Platform specifics #  
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(demo PUBLIC /MP)
    target_compile_options(demo PRIVATE /W3)
    add_compile_definitions(demo PRIVATE SAMPO_PLATFORM_WINDOWS)

    include_directories(${PROJECT_SOURCE_DIR}/framework/src/platform/windows)
endif()