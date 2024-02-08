#include <textures.hpp>
#include <stb/stb_image.h>
#define STB_IMAGE_IMPLEMENTATION

namespace shb{
const std::string Texture::texturePath = "../resources/textures/";
std::vector<unsigned int> Texture::textures;

// void setTextureParams(){
//     stbi_set_flip_vertically_on_load(true);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
// }

unsigned int Texture::loadTexture(std::string fileName){
    unsigned char *data;
    int width, height, nrChannels;
    data = stbi_load(std::string(texturePath + fileName).c_str(), &width, &height, &nrChannels, 0); 
    unsigned int handle; // <- THIS HOLDS THE ACTUAL TEXTURE FOR USE
    glGenTextures(1, &handle);  
    //texture needs to be bound to a texture slot in order to use functions below
    glActiveTexture(GL_TEXTURE0);      
    glBindTexture(GL_TEXTURE_2D, handle); 
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D); //<- 
    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(data);
    return handle;
}


void loadAllTextures(std::vector<unsigned int>* textures){
    std::vector<std::filesystem::__cxx11::directory_entry> textureNames;
    readFilesInDirectoryFromExtensions(".jpg",Texture::texturePath,textureNames);
  
    for(int i = 0; i < textureNames.size(); ++i){
        unsigned int ID = Texture::loadTexture(textureNames[i].path().filename());
        textures->push_back(ID);
    }
}


void clearAllTextures(std::vector<unsigned int>* textures){
    textures->clear();
}

void reloadTextures(std::vector<unsigned int>* textures){
    clearAllTextures(textures);
    loadAllTextures(textures);
}

void setTextureParams(){
    stbi_set_flip_vertically_on_load(true);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}


}//namespace shb
