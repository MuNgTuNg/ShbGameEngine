#include <app.hpp>

namespace shb{
Camera::Camera(){
     
}

Camera::Camera(
    glm::vec3 positionIn,
    glm::vec3 targetIn
) 
{
    pos = positionIn;
    target = targetIn;
}

void Camera::updateDelta(){
    moveSpeed = 5.f;
    moveSpeed *= App::getState().delta;
}
     
void Camera::update(){
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw))  * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch)); 
    front = glm::normalize(direction);
    view = glm::lookAt(pos, pos + front, up);
}

void Camera::look(cameraMovementDir lookDir){
    updateDelta();
    sensitivity = 2.f;
    switch(lookDir){
        case CAM_LOOK_DOWN: 
            pitch -= sensitivity;
            break;
        case CAM_LOOK_UP: 
            pitch += sensitivity;
            break;
        case CAM_LOOK_LEFT: 
            yaw -= sensitivity;
            break;
        case CAM_LOOK_RIGHT:
            yaw += sensitivity;
            break;
    }
    if(pitch > 89.0f)
        pitch =  89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

    if(yaw >= 360.f || yaw <= -360.f){
        yaw = 0.f;
    }
    
    //cos(pitch) is the length of the direction vector projected onto the xz axis
}
void Camera::move(cameraMovementDir moveDir){
    updateDelta();
    switch(moveDir){
        case CAM_MOVE_UP: 
            pos += up * moveSpeed;
            break;
        case CAM_MOVE_DOWN: 
            pos -= up * moveSpeed;
            break;
        case CAM_MOVE_LEFT: 
            pos -= glm::normalize(glm::cross(front, up)) * moveSpeed;
            break;
        case CAM_MOVE_RIGHT: 
            pos += glm::normalize(glm::cross(front, up)) * moveSpeed;
            break;
        case CAM_MOVE_FORWARD:
            pos += moveSpeed * front;
            break;
        case CAM_MOVE_BACKWARD:
            pos -= moveSpeed * front;
            break;
    }
}
    
void Camera::setInputState(GLFWwindow* window, cameraInputState state){
   inputState = state;
   if(inputState == CAM_INPUT_NONE){
       glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); 
   }
   if(inputState == CAM_INPUT_MOUSE){
       glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); 
   }
}

void Camera::calculateVectors(){
    direction = glm::normalize(pos - target);
    right = glm::normalize(glm::cross(worldUp,direction));
    up = glm::cross(direction,right);
}

}//namespace shb