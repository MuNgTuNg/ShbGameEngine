include_directories(${PROJECT_NAME}
PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
PUBLIC ${PARENT_DIR}../external/glad
PUBLIC ${PARENT_DIR}../external
PUBLIC ${PARENT_DIR}../external/glfw
PUBLIC ${PARENT_DIR}../include
PUBLIC ${PARENT_DIR}../external/freetype/include

)

add_library(src
camera.cpp
gui.cpp
app.cpp
app_input.cpp
shaders.cpp
text.cpp
textures.cpp
checkpoints.cpp
)