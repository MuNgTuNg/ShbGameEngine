#pragma once
#include <glad.h>

#include <imGUI/imgui.h>
#include <imGUI/imgui_impl_glfw.h>
#include <imGUI/imgui_impl_opengl3.h>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include <state.hpp>

#include <iostream>
#include <assert.h>



namespace shb{
class App;
class GUI {
    public: 
    GUI(GLFWwindow*);
    int attachAppToGUI(App* _app);
    void displayXYZ();
    void show();
    void init();

    App* app = nullptr;
    GLFWwindow* window;
    bool demoWindow = false;
    bool open = false;

    static bool initialisedLib;


    //skybox
    float shaderColors[3] = {0.f,0.730f,1.f};
};

}//namespace shb