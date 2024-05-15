set(CMAKE_INCLUDE_CURRENT_DIR ON)


add_library(impl STATIC
        WeightedTree.h)
target_sources(impl PUBLIC WeightedTree.cpp)
target_include_directories(impl INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})