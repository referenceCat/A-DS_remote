#
# Author: Kirill Trofimov
# Email: trofkm@gmail.com
# Date: 28.09.23
#

cmake_minimum_required(VERSION 3.22)

find_program(CCACHE_FOUND ccache)
if (CCACHE_FOUND)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
    set(CMAKE_C_COMPILER_LAUNCHER "ccache")
endif (CCACHE_FOUND)


# Add custom cmake modules
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
# Includes
include(message_macros)
include(CheckIPOSupported)
include(clang-cxx-dev-tools)


# Enable Inter-procedural Optimization
check_ipo_supported(RESULT ipo_supported)
if (ipo_supported)
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
endif ()

project(A_DS_remote)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# here we specify the directories for each lab
# TODO: add all labs from sem 1

add_subdir_with_message(sem2/Lab3)


