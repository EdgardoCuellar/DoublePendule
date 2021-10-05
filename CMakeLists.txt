cmake_minimum_required(VERSION 3.17)
project(DoublePendule)

set(CMAKE_CXX_STANDARD 20)

find_package(SDL2 REQUIRED)
include_directories( ${SDL2_INCLUDE_DIR} )

add_executable(DoublePendule main.cpp Screen.cpp Point.cpp Pendule.cpp)

target_link_libraries(DoublePendule ${SDL2_LIBRARY} )