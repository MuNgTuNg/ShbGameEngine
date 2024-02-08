target_include_directories(${PROJECT_NAME}
PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
PUBLIC ${PARENT_DIR}../external/glad
PUBLIC ${PARENT_DIR}../external
PUBLIC ${PARENT_DIR}../external/glfw
PUBLIC ${PARENT_DIR}../include
PUBLIC ${PARENT_DIR}../external/freetype/include
PUBLIC ${CMAKE_SOURCE_DIR}/external/imGUI
PUBLIC ${CMAKE_SOURCE_DIR}/external/imGUI/backends
)
add_library(include INTERFACE
    camera.hpp
    state.hpp
    textures.hpp
    app.hpp
    files.hpp
    shaders.hpp
    gui.hpp
    text.hpp
    vertices.hpp
    buffers.hpp
    checkpoints.hpp
)