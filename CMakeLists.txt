cmake_minimum_required(VERSION 3.0.0)
project(my_test_cmake_project VERSION 0.1.0)

find_package(OpenGL REQUIRED)
add_executable(
    my_test_cmake_project
        src/config.h 
        src/config.cpp
        src/main.cpp 
        src/glad.c
        src/TriangleMesh.cpp
        src/Material.cpp
)

target_include_directories(my_test_cmake_project PRIVATE include)
target_link_libraries(my_test_cmake_project glfw OpenGL::GL)
