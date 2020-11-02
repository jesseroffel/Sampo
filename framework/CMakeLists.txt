# Framework #

# include common directory #
include_directories(${PROJECT_SOURCE_DIR}/framework)

add_library(framework STATIC "sampo/sampo.hpp" "sampo/sampo_pch.hpp" "sampo/sampo_pch.cpp" "sampo/core/application.hpp"  "sampo/core/application.cpp" "sampo/core/core_definitions.hpp" "sampo/core/entry_point.hpp" "sampo/core/layer.hpp" "sampo/core/layer.cpp" "sampo/math/vector3_io.cpp" "sampo/debugging/new_tracker.hpp" "sampo/io/file_system.hpp")

# Overrides globals #
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib/framework/${outputdir})

# Configure solution # 
target_precompile_headers(framework PUBLIC sampo/sampo_pch.cpp)

# Compile settings # 
target_compile_features(framework PRIVATE cxx_std_17)

# Platform specifics # 
if (WIN32)
    target_sources(framework
        PUBLIC
            "sampo/platform/windows/io/windows_file_systems.cpp"
    )
endif()

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(framework PUBLIC /MP)
    target_compile_options(framework PRIVATE /W4 /WX)
    add_compile_definitions(framework PRIVATE SAMPO_PLATFORM_WINDOWS)
else()
    target_compile_options(framework PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

