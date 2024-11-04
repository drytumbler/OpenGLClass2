cmake_minimum_required(VERSION 3.5)
project(my_test_cmake_project VERSION 0.1.1)

find_package(OpenGL REQUIRED)

# Common source files
set(SOURCES
    src/config.cpp
    src/glad.c
    src/TriangleMesh.cpp
    src/Material.cpp
    src/Shader.cpp
    src/IBO.cpp
    src/VBO.cpp
    src/VAO.cpp
    src/Camera.cpp
)

# Function to create executables
macro(create_executable name)
    add_executable(${name} ${SOURCES} src/${name}.cpp)
    target_include_directories(${name} PRIVATE include)
    target_link_libraries(${name} glfw OpenGL::GL)
endmacro()

# Create all executables
create_executable(main)
create_executable(disp_tex)
create_executable(shaderToy)
create_executable(pyramid_ex)
