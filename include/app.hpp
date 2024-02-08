#pragma once
#include <glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include <ft2build.h>
#include FT_FREETYPE_H
#include <buffers.hpp>

#include <imGUI/imgui.h>
#include <imGUI/imgui_impl_glfw.h>
#include <imGUI/imgui_impl_opengl3.h>

#include <thread>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>

#include <files.hpp>
#include <shaders.hpp>

#include <gui.hpp>
#include <camera.hpp>
#include <text.hpp>
#include <vertices.hpp>
#include <textures.hpp>

#include <checkpoints.hpp>


//error messaging system on version 4 of opengl

// void GLAPIENTRY MessageCallback( GLenum source,
//                  GLenum type,
//                  GLuint id,
//                  GLenum severity,
//                  GLsizei length,
//                  const GLchar* message,
//                  const void* userParam )
// {
//   fprintf( stderr, "\nGL CALLBACK: %s type = 0x%x, severity = 0x%x\n\n-> Message = %s <-\n\n",
//            ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
//             type, severity, message );
// }

namespace shb{

// class AppBase{
//     public:
//     AppBase() {}
//     virtual ~AppBase();
//     virtual int renderFrame() = 0;
//     virtual void updateKeyInput() = 0;
//     virtual void updateMouseInput() = 0;

// };


enum objectType{
    OBJECT_TYPE_NONE,
    OBJECT_TYPE_CUBE,
    OBJECT_TYPE_QUAD,
    NUM_OBJECT_TYPES
};

//objects should have shaders, shader programs, uniform setter functions
//need to determine how to implement an "objectType" based factory pattern to create objects
class Object{
    public:
    Object(){
        //checkpoint("Object constructor.");
    }
    glm::mat4 model{1.f};
    glm::vec3 pos{0.f,0.f,0.f};
    glm::vec3 scale{1.f,1.f,1.f};

    int shaderProgram = 0;
 
    //TODO:: detach buffers from object class as they can be reused.
    Buffer* indexBuffer;
    Buffer* vertexBuffer;
    unsigned int vao = 0;

    unsigned int numElements = 0;

    int texture = -1;
    objectType type = OBJECT_TYPE_NONE;
    std::string name = "err";
    unsigned int index = 0;
};




class App { 
    friend class GUI;
    public:
    bool running = true;
    std::string appName;

    App(const std::string& _name);
    ~App();
    void renderFrame();
    void renderText();
    void updateKeyInput();
    void updateMouseInput();
    void attachAppToWindow(GLFWwindow* _window) { window = _window;}
    static AppState const getState() { return state;}


    void reloadShader(); //TODO:: make this generic.
    private:
    GLFWwindow* window = nullptr;
    TextRenderer textRenderer; 
    static AppState state;

    int camIndex = 0;
    Camera followCamera{};
    Camera mainCamera{{0.f,2.f,1.f},{0.f,0.f,0.f}};
    std::vector<Camera> cameras;
    
    public:

    std::vector<Object*> objects;

    //Timing variables
    double delta = 0;
    double timeSinceStart = 0;
    double oldTimeSinceStart;
    double elapsedText = 0.f;
    double durationText = 1.f;

    double mouseXPos = 0, mouseYPos = 0;

    //frame data
    double fps = 0;
    double frameTimeMS = 0;


    //vector of shader programs TODO::
    int shaderProgramTex3DObject;
    int shaderProgram3DObjectSkybox;
    int shaderProgram3DObject;

    //sort out
    Object floor;
    int floorIndex = 0;
    int cubeIndex = 0;
    int cube2Index = 0;
    Object cube2;

    Buffer quadIndexBuffer{GL_ELEMENT_ARRAY_BUFFER};
    Buffer quadVertexBuffer{GL_ARRAY_BUFFER};
    unsigned int quadVAO =0;

    Buffer cubeTexturedIndexBuffer{GL_ELEMENT_ARRAY_BUFFER};
    Buffer cubeTexturedVertexBuffer{GL_ARRAY_BUFFER};
    unsigned int cubeTexturedVAO =0;

    Buffer cubeIndexBuffer{GL_ELEMENT_ARRAY_BUFFER};
    Buffer cubeVertexBuffer{GL_ARRAY_BUFFER};
    unsigned int cubeVAO =0;

    Object skybox;
    //skybox shader stuff
    int offset = 17;
    float smoothstepStart = 0.f;
    float smoothstepEnd = 0.155f;
    glm::vec3 skyboxColor{0.f,0.730f,1.f};
    

    Object cube3;
    float cubeRotAngle;
    glm::vec3 cubeRotAxis ;
    glm::mat4 rotation;


    std::vector<Object> cubes;
   

    TextDetails textDetails;

    float radians = 90.f;
    float aspectRatioX = (float)WIN_WIDTH;
    float aspectRatioY = (float)WIN_HEIGHT;
    float near = 0.1f;
    float far = 10000.f;

    float viewportHeight = WIN_HEIGHT;
    float viewportWidth = WIN_WIDTH;
    bool transparency = true;
    bool maintainViewportSize = true;
    bool maintainAspectRatio = true;
    int windowWidth, windowHeight;
    std::vector<float> clearRGB = {0.f,0.f,0.f};
    double growingWindowTimerMS = 0;

    glm::mat4 proj3d = glm::perspective(glm::radians(radians),aspectRatioX/aspectRatioY,near,far);
    glm::mat4 view{1.f};
};

}//namespace shb