#pragma once
#include <glad.h>
#include <GLFW/glfw3.h>


#include <string>
#include <vector>
#include <files.hpp>


namespace shb{



class Texture{

public:
    static unsigned int loadTexture(std::string fileName);
    static const std::string texturePath;
    static std::vector<unsigned int> textures;
};

void loadAllTextures(std::vector<unsigned int>* textures);
void clearAllTextures(std::vector<unsigned int>* textures);
void setTextureParams();
void setTextureParams();

}//namespace shb
