# Demo #

include_directories(${PROJECT_SOURCE_DIR}/demo/src)
include_directories(${PROJECT_SOURCE_DIR}/framework/include)

add_executable(demo src/demo.cpp)
target_link_libraries(demo PUBLIC framework)
target_compile_features(demo PRIVATE cxx_std_17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/${outputdir}/demo)
set_property (DIRECTORY PROPERTY VS_STARTUP_PROJECT "demo")

# Demo compile settings # 
target_compile_features(demo PUBLIC cxx_std_17)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(demo PUBLIC /MP)
    target_compile_options(demo PRIVATE /W3)
    add_compile_definitions(demo PRIVATE SAMPO_PLATFORM_WINDOWS)
endif()