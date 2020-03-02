cmake_minimum_required(VERSION 3.17)
project(unittests)
find_package(rttr CONFIG REQUIRED)
include_directories(${CMAKE_SOURCE_DIR})

add_executable(simpleClient simpleClient.cpp)
target_link_libraries(simpleClient anyrpc RTTR::Core)
