set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_library(impl STATIC)
target_sources(impl PUBLIC shape.cpp)
target_include_directories(impl INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})