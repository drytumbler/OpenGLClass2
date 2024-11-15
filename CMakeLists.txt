cmake_minimum_required(VERSION 3.5)
project(my_test_cmake_project VERSION 0.1.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})


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
    src/Primitive.cpp
    src/TextEditorApp.cpp
    src/TextEditorBuffer.cpp
    src/ui.cpp
    src/State.cpp
    src/TextureBrowser.cpp
)

add_library(imgui STATIC
	include/imgui/imgui.cpp
	include/imgui/imgui_draw.cpp
	include/imgui/imgui_tables.cpp
	include/imgui/imgui_demo.cpp
	include/imgui/imgui_widgets.cpp
	include/imgui/imgui_impl_glfw.cpp
	include/imgui/imgui_impl_opengl3.cpp
    )

add_library(nfd STATIC
	lib/libnfd.a
    )

set_target_properties(nfd PROPERTIES LINKER_LANGUAGE C)

    
# Check if `nfd` needs additional platform libraries, e.g., GTK for Linux
if(UNIX AND NOT APPLE)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GTK REQUIRED gtk+-3.0)
    target_link_libraries(nfd PRIVATE ${GTK_LIBRARIES})
    target_include_directories(nfd PRIVATE ${GTK_INCLUDE_DIRS})
endif()

# Function to create executables
macro(create_executable name)
    add_executable(${name} ${SOURCES} src/${name}.cpp)
    target_include_directories(${name} PRIVATE include)
    target_link_libraries(${name} glfw OpenGL::GL imgui /home/ruben/projects/OpenGLClass2/lib/libnfd.a ${GTK3_LIBRARIES})
endmacro()

# Create all executables
#create_executable(main)
#create_executable(disp_tex)
create_executable(shaderToy)
create_executable(prEditor)
create_executable(main)
#create_executable(pyramid_ex)
