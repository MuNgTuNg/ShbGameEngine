add_subdirectory(glm)
add_subdirectory(glfw)
add_subdirectory(glad)

#  find_package(Git QUIET)
#  if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
#  # Update submodules as needed
#      option(GIT_SUBMODULE "Check submodules during build" ON)
#      if(GIT_SUBMODULE)
#          message(STATUS "Submodule update")
#          execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
#                          WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
#                          RESULT_VARIABLE GIT_SUBMOD_RESULT)
#          if(NOT GIT_SUBMOD_RESULT EQUAL "0")
#              message(FATAL_ERROR "git submodule update --init --recursive failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
#          endif()
#      endif()
#  endif()

#  if(NOT EXISTS "${PROJECT_SOURCE_DIR}/external/imgui/CMakeLists.txt")
#      message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
#  endif()

#add_subdirectory(imgui2)

add_library(imgui 
    imGUI/imgui.h 
    imGUI/imgui.cpp 
    imGUI/imgui_impl_glfw.h
    imGUI/imgui_impl_opengl3.h
    imGUI/imgui_impl_glfw.cpp
    imGUI/imgui_impl_opengl3.cpp
    imGUI/imgui_impl_opengl3_loader.h
    imGUI/imgui_demo.cpp
    imGUI/imgui_draw.cpp 
    imGUI/imconfig.h 
    imGUI/imgui_internal.h 
    imGUI/imgui_tables.cpp 
    imGUI/imgui_widgets.cpp 
    imGUI/imstb_rectpack.h 
    imGUI/imstb_textedit.h 
    imGUI/imstb_truetype.h 
)

target_include_directories(${PROJECT_NAME}
    PUBLIC ${CMAKE_SOURCE_DIR}
)

add_library(stb INTERFACE
        stb/stb_image.h
)
