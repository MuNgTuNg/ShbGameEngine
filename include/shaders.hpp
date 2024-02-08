#pragma once
#include <vector>
#include <string>
#include <glad.h>
#include <GLFW/glfw3.h>

namespace shb{

    

struct Shader{
    std::string name;
    GLenum type;
};

int createShaderProg(std::vector<Shader> shaders);

}//namespace shb