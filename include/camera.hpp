#pragma once
#include <iostream>

namespace shb{


enum cameraInputState{
    CAM_INPUT_NONE,
    CAM_INPUT_MOUSE,
    NUM_CAM_INPUTS
};
enum cameraMovementDir{
    NO_CAM_MOVEMENT,
    CAM_MOVE_FORWARD,
    CAM_MOVE_BACKWARD,
    CAM_MOVE_UP,
    CAM_MOVE_DOWN,
    CAM_MOVE_LEFT,
    CAM_MOVE_RIGHT,
    CAM_LOOK_UP,
    CAM_LOOK_DOWN,
    CAM_LOOK_LEFT,
    CAM_LOOK_RIGHT,
    NUM_CAM_MOVEMENTS //This value at the end allows the enum to become iteratable :-)
};

class TextRenderer;
class Camera{
    public:
    Camera();

    Camera(
        glm::vec3 positionIn,
        glm::vec3 targetIn
    );

    void updateDelta();
    
    void look(cameraMovementDir);
    void move(cameraMovementDir);
    void setInputState(GLFWwindow* window, cameraInputState state);
    void calculateVectors();
    void update();

    glm::vec3 worldUp{0.0f,1.0f,0.0f};  //world up will always be the same in this camera system

    glm::vec3 pos{0.0f,0.0f,0.0f}; //changes
    glm::vec3 front{0.0f,0.0f,-1.f};    //assigned to by changing the direction vector and normalising it 
    glm::vec3 target{0.0f,0.0f,-1.f};   //changes

    glm::mat4 view;

    glm::vec3 direction{glm::normalize(pos - target)}; //is calculated and changes
    glm::vec3 right{glm::normalize(glm::cross(worldUp,direction))}; //is calculated
    glm::vec3 up{glm::cross(direction,right)};     //is calculated

    float yaw = -90.f;
    float pitch = 0.f;
    
    float lastX = 0;
    float lastY = 0;
    float sensitivity = 0.01f;
    float moveSpeed = 0.5f;

    int index = -1;

    cameraInputState inputState = CAM_INPUT_NONE;

    TextRenderer* textRenderer_;


};

}//namespace shb