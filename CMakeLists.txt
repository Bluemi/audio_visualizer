cmake_minimum_required (VERSION 2.6)

project(AudioVisualizer)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_C_FLAGS_DEBUG "--Wall" "-fmax-errors 5" )

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src")

add_subdirectory(src)
