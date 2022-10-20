cmake_minimum_required(VERSION 3.22)
project(carpetv2)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 14)

add_executable(carpetv2 main.cpp)

target_link_libraries(carpetv2 ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
