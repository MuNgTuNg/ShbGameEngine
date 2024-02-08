#pragma once
#include <GLFW/glfw3.h>
#include <camera.hpp>
namespace shb{


#ifdef ULTRAWIDE

#define WIN_WIDTH 3440
#define WIN_HEIGHT 1440

#else 

#define WIN_WIDTH 1920
#define WIN_HEIGHT 1080

#endif



struct AppState{
    bool running = true;
    float delta = 0;
    float mix = 0;
};

}//namespace shb