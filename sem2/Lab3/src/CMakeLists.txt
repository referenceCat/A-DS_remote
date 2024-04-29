set(CMAKE_INCLUDE_CURRENT_DIR ON)


add_library(impl STATIC
        MyBinarySearchTree.h)
target_sources(impl PUBLIC MyBinarySearchTree.cpp)
target_include_directories(impl INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})