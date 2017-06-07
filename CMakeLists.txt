cmake_minimum_required(VERSION 3.6)
project(Cross_and_circle_game_neural_networks_learn)
add_definitions(-DCNN_USE_TBB)

set(CMAKE_CXX_STANDARD 11)
include_directories(tiny-dnn)

set(SOURCE_FILES main.cpp)
add_executable(Cross_and_circle_game_neural_networks_learn ${SOURCE_FILES})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread")
find_package(Threads REQUIRED)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/Modules)


# Find Intel Threading Building Blocks (TBB)
find_package(TBB QUIET)
if(USE_TBB AND TBB_FOUND)
    message(STATUS "Found Intel TBB: ${TBB_INCLUDE_DIR}")
    # In case that TBB is found we force to disable OpenMP since
    # tiny-dnn does not support mutiple multithreading backends.
    set(USE_OMP OFF)
    #TODO: add definitions in configure
    add_definitions(-DCNN_USE_TBB)
    include_directories(${TBB_INCLUDE_DIRS})
    link_directories(${TBB_LIBRARY_DIRS})
    list(APPEND REQUIRED_LIBRARIES ${TBB_LIBRARIES})
elseif(USE_TBB AND NOT TBB_FOUND)
    # In case the user sets the flag USE_TBB to ON, the CMake build-tree
    # will require to find TBB in your system. Otherwise, the user can
    # set the paths to headers and libs by hand.
    message(FATAL_ERROR "Intel TBB not found. Please set TBB_INCLUDE_DIRS & "
            "TBB_LIBRARIES")
endif()




#target_link_libraries(Cross_and_circle_game_neural_networks_learn ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(Cross_and_circle_game_neural_networks_learn ${CMAKE_THREAD_LIBS_INIT} ${REQUIRED_LIBRARIES})

