add_library(impl INTERFACE screen.h shape.h)
target_include_directories(impl INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})