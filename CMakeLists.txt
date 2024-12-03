cmake_minimum_required(VERSION 3.15)

project(SmartBuffer VERSION 1.0.0 LANGUAGES CXX)

add_library(smart_buffer STATIC SmartBuffer.cpp)

target_include_directories(smart_buffer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(smart_buffer PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
)

add_executable(smart_buffer_example main.cpp)

target_link_libraries(smart_buffer_example PRIVATE smart_buffer)

install(TARGETS smart_buffer
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)

install(FILES SmartBuffer.hpp DESTINATION include)

enable_testing()