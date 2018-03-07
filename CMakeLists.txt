cmake_minimum_required(VERSION 3.9)
project(Football_Penalty_Shooter)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -lglut -lGLU -lGL -lSOIL")

set(SOURCE_FILES main.cpp functionalities.cpp shapes.cpp)
FILE(COPY resources DESTINATION "${CMAKE_BINARY_DIR}")

add_executable(Football_Penalty_Shooter ${SOURCE_FILES})
