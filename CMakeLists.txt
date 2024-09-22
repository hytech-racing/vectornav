cmake_minimum_required(VERSION 3.10)

project(VectorNavDriver VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/libs/vn_driver_lib/cpp/include)

add_executable(vectornav_driver src/main.cpp src/VectorNavComms.cpp)

target_link_libraries(vectornav_driver ${CMAKE_SOURCE_DIR}/libs/vn_driver_lib/cpp/build/liblibvncxx.a)

