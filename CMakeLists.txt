cmake_minimum_required(VERSION 3.5)
project(my_test_cmake_project VERSION 0.1.1)

find_package(OpenGL REQUIRED)
add_executable(
    my_test_cmake_project
        src/config.cpp
        src/main.cpp 
        src/glad.c
        src/TriangleMesh.cpp
        src/Material.cpp
	src/Shader.cpp
	src/IBO.cpp
	src/VBO.cpp
	src/VAO.cpp
	src/Camera.cpp
        #src/math.cpp
    )

    add_executable(
    disp_tex
        src/config.cpp
        src/disp_tex.cpp 
        src/glad.c
        src/TriangleMesh.cpp
        src/Material.cpp
	src/Shader.cpp
	src/IBO.cpp
	src/VBO.cpp
	src/VAO.cpp
	src/Camera.cpp
        #src/math.cpp
)

    add_executable(
    shadertoy
        src/config.cpp
        src/shaderToy.cpp 
        src/glad.c
        src/TriangleMesh.cpp
        src/Material.cpp
	src/Shader.cpp
	src/IBO.cpp
	src/VBO.cpp
	src/VAO.cpp
	src/Camera.cpp
        #src/math.cpp
)

target_include_directories(my_test_cmake_project PRIVATE include)
target_link_libraries(my_test_cmake_project glfw OpenGL::GL)

target_include_directories(disp_tex PRIVATE include)
target_link_libraries(disp_tex glfw OpenGL::GL)

target_include_directories(shadertoy PRIVATE include)
target_link_libraries(shadertoy glfw OpenGL::GL)

