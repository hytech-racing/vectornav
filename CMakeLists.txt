cmake_minimum_required(VERSION 3.14)

project(VectorNavDriver VERSION 1.0)

find_package(cmake_macros)
include(create_package)
include(easy_find_packages)

easy_find_packages(vectornav_driver "vectornav")

add_executable(vectornav_driver src/main.cpp)

target_link_libraries(vectornav_driver cc::vectornav)

