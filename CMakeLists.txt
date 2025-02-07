cmake_minimum_required(VERSION 3.15)

project(SmartBuffer VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE SOURCES
        "${CMAKE_SOURCE_DIR}/src/*.cpp"
        "${CMAKE_SOURCE_DIR}/src/*.hpp"
)

file(GLOB_RECURSE HEADERS
        "${CMAKE_SOURCE_DIR}/include/*.hpp"
)

include_directories(
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/src
)

add_library(smart_buffer STATIC ${SOURCES})

set_target_properties(smart_buffer PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
)

install(TARGETS smart_buffer
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin
)

install(FILES ${HEADERS} DESTINATION include)
