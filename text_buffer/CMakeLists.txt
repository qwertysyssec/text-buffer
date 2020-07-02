cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(text_buffer LANGUAGES CXX)
add_executable(${PROJECT_NAME} "main.cpp" "text_buffer.hpp" )
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_EXTENSIONS OFF)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(Boost 1.68 REQUIRED COMPONENTS container)
find_package(benchmark REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Boost::container benchmark::benchmark_main)
