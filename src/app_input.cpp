#include <app.hpp>
namespace shb{


void App::updateKeyInput(){
    float moveSpeed = 5.f;
    moveSpeed *= delta;

    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        running = false;
    }
    if(glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS){
        state.mix+=0.01f;
    }
    if(glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS){
        state.mix-=0.01f;
    }

    
        if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
            cameras[camIndex].look(CAM_LOOK_UP);
        }
        if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
            cameras[camIndex].look(CAM_LOOK_DOWN);
        }
        if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS){
            cameras[camIndex].look(CAM_LOOK_LEFT);
        }
        if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS){
            cameras[camIndex].look(CAM_LOOK_RIGHT);
        }

        if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS){
            cameras[camIndex].move(CAM_MOVE_UP);
        }
        if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS){
            cameras[camIndex].move(CAM_MOVE_DOWN);
        }
        if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
            cameras[camIndex].move(CAM_MOVE_FORWARD);
        }
        if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
            cameras[camIndex].move(CAM_MOVE_BACKWARD);
        }
        if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
            cameras[camIndex].move(CAM_MOVE_LEFT);
            //cameras[camIndex].pos -= glm::normalize(glm::cross(cameras[camIndex].front, cameras[camIndex].up)) * moveSpeed;
        }
        if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
            cameras[camIndex].move(CAM_MOVE_RIGHT);
            //cameras[camIndex].pos += glm::normalize(glm::cross(cameras[camIndex].front, cameras[camIndex].up)) * moveSpeed;
        }
        
        
        if(glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS){
            cameras[camIndex].setInputState(window,CAM_INPUT_MOUSE);
        }
        if(glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS){
            cameras[camIndex].setInputState(window,CAM_INPUT_NONE);
        }
    
}

//Camera mouse controls
void App::updateMouseInput(){
    //getting cursor position
    glfwGetCursorPos(window, &mouseXPos, &mouseYPos);
    if(cameras[camIndex].inputState == CAM_INPUT_MOUSE){
        float xOffset = mouseXPos-cameras[camIndex].lastX;
        float yOffset = cameras[camIndex].lastY - mouseYPos;
        cameras[camIndex].lastY = mouseYPos;
        cameras[camIndex].lastX = mouseXPos;
        
        cameras[camIndex].sensitivity = 0.01f;
        xOffset *= cameras[camIndex].sensitivity;
        yOffset *= cameras[camIndex].sensitivity;
        cameras[camIndex].yaw= std::fmod((cameras[camIndex].yaw + xOffset), (GLfloat)360.0f); //stops floating point error from huge values
        cameras[camIndex].pitch+=yOffset;

        if(cameras[camIndex].pitch > 89.0f)
        cameras[camIndex].pitch =  89.0f;
        if(cameras[camIndex].pitch < -89.0f)
        cameras[camIndex].pitch = -89.0f;
        
        //cos(pitch) is the length of the direction vector projected onto the xz axis
        cameras[camIndex].direction.x = cos(glm::radians(cameras[camIndex].yaw)) * cos(glm::radians(cameras[camIndex].pitch));
        cameras[camIndex].direction.z = sin(glm::radians(cameras[camIndex].yaw))  * cos(glm::radians(cameras[camIndex].pitch));
        cameras[camIndex].direction.y = sin(glm::radians(cameras[camIndex].pitch)); 
        

        cameras[camIndex].front = glm::normalize(cameras[camIndex].direction);
    }
}

}//namespace shb