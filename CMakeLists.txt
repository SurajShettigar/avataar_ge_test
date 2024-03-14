cmake_minimum_required(VERSION 3.27)
project(material_test)

set(CMAKE_CXX_STANDARD 17)

add_executable(material_test
        material_test/camera.cpp
        material_test/material.cpp
        material_test/mesh.cpp
        material_test/object.cpp
        material_test/scene.cpp
        material_test/renderer.cpp
        material_test/app.cpp
        material_test/main.cpp)

## Add libraries
add_subdirectory(ext/glad)
add_subdirectory(ext/glfw)
add_subdirectory(ext/glm)
add_subdirectory(ext/tinyobjloader)

target_include_directories(material_test PUBLIC material_test)
target_link_libraries(material_test PUBLIC glad glfw glm tinyobjloader)

## Copy data and shaders to build directory
file(COPY data DESTINATION ${CMAKE_BINARY_DIR})
add_compile_definitions(DATA_DIR=\"${CMAKE_BINARY_DIR}/data\")
file(COPY shaders DESTINATION ${CMAKE_BINARY_DIR})
add_compile_definitions(SHADER_DIR=\"${CMAKE_BINARY_DIR}/shaders\")
