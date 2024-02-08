cmake_minimum_required(VERSION 3.2)
project(game)
set(CMAKE_BUILD_TYPE Debug)

add_compile_options(-Wnarrowing)
#add_definitions(-DULTRAWIDE)

add_executable(${PROJECT_NAME} src/app.cpp)




target_include_directories(${PROJECT_NAME}
PRIVATE external/glad/include
external/glad/
external/glfw/include
include
src
external/
external/freetype/include
external/imGUI
external/imGUI/backends
${CMAKE_SOURCE_DIR}/external/imGUI
${CMAKE_SOURCE_DIR}/external/imGUI/backends

)

add_subdirectory(external)
add_subdirectory(src)


target_link_libraries(${PROJECT_NAME} 
    src
    imgui
    freetype
    glm
    dl
    src
    glad
    glfw
    pthread
    stb
)