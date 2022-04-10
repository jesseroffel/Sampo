# tcp_chatclient #

# include and create #
include_directories(${PROJECT_SOURCE_DIR}/framework/src)
include_directories(${PROJECT_SOURCE_DIR}/framework/vendor/spdlog/include)

add_executable(tcp_chatclient client.cpp)

# Overrides globals #
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin/tcp_chatclient/${outputdir})

# Configure solution # 
set_property (DIRECTORY PROPERTY VS_STARTUP_PROJECT "tcp_chatclient")

# Compile settings # 
target_compile_features(tcp_chatclient PUBLIC cxx_std_17)
target_link_libraries(tcp_chatclient PUBLIC framework)

# Platform specifics #  
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(tcp_chatclient PUBLIC /MP)
    target_compile_options(tcp_chatclient PRIVATE /W3)
    add_compile_definitions(tcp_chatclient PRIVATE SAMPO_PLATFORM_WINDOWS)

    include_directories(${PROJECT_SOURCE_DIR}/framework/src/platform/windows)
endif()