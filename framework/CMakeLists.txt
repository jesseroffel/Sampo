# Framework #

# include and create #
include_directories(${PROJECT_SOURCE_DIR}/framework/include)

add_library(framework STATIC "include/sampo.hpp" "include/sampo_pch.hpp" "include/sampo_pch.cpp" "include/foundation/core/application.hpp"  "include/foundation/core/application.cpp" "include/foundation/core/core_definitions.hpp" "include/foundation/core/entry_point.hpp" "include/foundation/core/layer.hpp" "include/foundation/core/layer.cpp")

# Overrides globals #
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib/framework/${outputdir})

# Configure solution # 
target_precompile_headers(framework PUBLIC include/sampo_pch.cpp)

# Compile settings # 
target_compile_features(framework PRIVATE cxx_std_17)

# Platform specifics # 
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(framework PUBLIC /MP)
    target_compile_options(framework PRIVATE /W4 /WX)
    add_compile_definitions(framework PRIVATE SAMPO_PLATFORM_WINDOWS)
else()
    target_compile_options(framework PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

