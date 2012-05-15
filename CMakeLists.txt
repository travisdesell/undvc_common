cmake_minimum_required (VERSION 2.6)
project (undvc_common)
# The version number.
set (UNDVC_COMMON_VERSION_MAJOR 0)
set (UNDVC_COMMON_VERSION_MINOR 1)
 
set(CMAKE_CXX_FLAGS "-g -Wall -O3 -funroll-loops -ftree-vectorize -msse3")

add_library(undvc_common vector_io arguments)
