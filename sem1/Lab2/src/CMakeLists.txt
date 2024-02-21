set(CMAKE_INCLUDE_CURRENT_DIR ON)


add_library(impl STATIC)
target_sources(impl PUBLIC modules/CharArraySet.cpp modules/CharListSet.cpp modules/MachineWordSet.cpp modules/BitArraySet.cpp)
target_include_directories(impl INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})