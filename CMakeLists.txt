cmake_minimum_required(VERSION 3.17)
project(loadingRPC)

# //TODO: fix linker while building on generated sln

set(CMAKE_CXX_STANDARD 17)
if (ANYRPC_LIB_BUILD_SHARED)
    if (WIN32)
        add_definitions( -DANYRPC_DLL )
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
    else()
         message("Congratulations, it's not Windows")
    endif()
endif ()

find_package(rttr CONFIG REQUIRED)

# //TODO: add GTest for using for us and building anyrpc with tests

include_directories(anyrpc)
include_directories(anyrpc/include)


# anyrpc default customization
option(BUILD_TESTS NO) 
option(BUILD_WITH_LOG4CPLUS NO)

# // display included dirs
get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
foreach(dir ${dirs})
  message(STATUS "Include dir='${dir}'")
endforeach()
# // end display

add_subdirectory(anyrpc)

add_executable(lrpcserve main.cpp)
target_link_libraries(lrpcserve PRIVATE anyrpc RTTR::Core)

add_subdirectory(unittests)
#TODO: NEXT do copy dll for unittests