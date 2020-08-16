# Project: Dynamic_Array
# Author: Matthew J. Corbett
# Date: 8/15/2020
cmake_minimum_required(VERSION 3.1)
project(Dynamic_Array)
# Set the c++ standard
set_property(
    GLOBAL
    PROPERTY CXX_STANDARD 17)
# Include Files
include_directories(Include)
file(GLOB SOURCES "Src/*.cpp")
# Add Exeutable
add_executable(main ${SOURCES})
