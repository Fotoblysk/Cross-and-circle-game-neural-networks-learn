cmake_minimum_required(VERSION 3.6)
project(Cross_and_circle_game_neural_networks_learn)

set(CMAKE_CXX_STANDARD 11)
include_directories(tiny-dnn)

set(SOURCE_FILES main.cpp)
add_executable(Cross_and_circle_game_neural_networks_learn ${SOURCE_FILES})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread")
find_package(Threads REQUIRED)
target_link_libraries(Cross_and_circle_game_neural_networks_learn ${CMAKE_THREAD_LIBS_INIT})


