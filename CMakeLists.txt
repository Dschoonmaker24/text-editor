cmake_minimum_required(VERSION 3.7)

#allow target_link_libraries from other directories
cmake_policy(SET CMP0079 NEW)

project(TextEditor VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

option(BUILD_SHARED_LIBS OFF)

add_subdirectory(text-editor)
add_subdirectory(dependencies)