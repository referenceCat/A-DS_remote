#
# Author: Kirill Trofimov
# Email: trofkm@gmail.com
# Date: 05.12.23
#

# Additional targets to perform clang-format/clang-tidy
# Get all project files
file(GLOB_RECURSE
        ALL_CXX_SOURCE_FILES
        "${CMAKE_SOURCE_DIR}/**/src/*.cpp"
        "${CMAKE_SOURCE_DIR}/**/src/*.cxx"
        "${CMAKE_SOURCE_DIR}/**/src/*.cc"
        "${CMAKE_SOURCE_DIR}/**/src/*.C"
        "${CMAKE_SOURCE_DIR}/**/tests/*.cpp"
        "${CMAKE_SOURCE_DIR}/**/tests/*.cxx"
        "${CMAKE_SOURCE_DIR}/**/tests/*.cc"
        "${CMAKE_SOURCE_DIR}/**/tests/*.C"
)

file(GLOB_RECURSE
        ALL_CXX_HEADER_FILES
        "${CMAKE_SOURCE_DIR}/**/include/*.h"
        "${CMAKE_SOURCE_DIR}/**/include/*.H"
        "${CMAKE_SOURCE_DIR}/**/include/*.hh"
        "${CMAKE_SOURCE_DIR}/**/include/*.hxx"
        "${CMAKE_SOURCE_DIR}/**/include/*.hpp"
)


# Adding clang-format target if executable is found
find_program(CLANG_FORMAT "clang-format")
if(CLANG_FORMAT)
    add_custom_target(
            clang-format
            COMMAND clang-format
            -i
            -style=file
            ${ALL_CXX_SOURCE_FILES}
            ${ALL_CXX_HEADER_FILES}
    )
endif()

# Adding clang-tidy target if executable is found
find_program(CLANG_TIDY "clang-tidy")
if(CLANG_TIDY)
    add_custom_target(
            clang-tidy
            COMMAND clang-tidy
            ${ALL_CXX_SOURCE_FILES}
            -config=''
            --
            -std=c++11
            ${INCLUDE_DIRECTORIES}
    )
endif()