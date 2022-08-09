cmake_minimum_required(VERSION 3.18.1)
project("myapplication")
include_directories("${CMAKE_SOURCE_DIR}/include")
add_library(
        myapplication
        SHARED
        native-lib.cpp)
find_library(
        log-lib
        log)
target_link_libraries(
        myapplication
        ${log-lib})