#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <map>
#include <string>
#include <iostream>
#include <filesystem>

#include <glad.h>
#include <GLFW/glfw3.h>


#include <ft2build.h>
#include FT_FREETYPE_H


#include <shaders.hpp>
#include <state.hpp>
#include <files.hpp>


/*
Text renderer renders texts on textures on quads, using 
texture unit 0
*/
namespace shb{


enum positions{
    TITLE,
    TOP,
    BOTTOM_LEFT,
    BOTTOM_RIGHT,
    CENTRE
};

class TextPositons{
    public:
    static glm::vec3 getPosition(positions pos){ 
        if(pos == TITLE){
            return {10.f, (float)WIN_HEIGHT - 50.f,0.f };
        }
        if(pos == CENTRE){
            return {(float)WIN_WIDTH/2, (float)WIN_HEIGHT/2,0.f };
        }
        if(pos == BOTTOM_LEFT){
            return {20.0f, 20.0f, 0.f};
        }
        return {0.0f,0.0f,0.0f};
    }
     
};

struct Character {
    unsigned int TextureID;  // ID handle of the glyph texture
    glm::ivec2   Size;       // Size of glyph
    glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
    long int Advance;    // Offset to advance to next glyph
};


class TextRenderer{
    public:
    void setColor(glm::vec3 color) { 
        color_ = color;
    }
    void setScale(float scale){
        scale_ = scale;
    }
    void setPos(float x,float y){
        x_ = x;
        y_ = y;
    }
    
   
    std::string text_ = "No Text";
    float x_ = WIN_WIDTH/2;
    float y_ = WIN_HEIGHT/2;
    float scale_ = 1.f;
    glm::vec3 color_{255.f,0.f,255.f};
    glm::vec3 textPos = {0.f,0.f,0.f};
    //

    void rendertext(std::string text= "No Text", 
                    glm::vec3 pos = TextPositons::getPosition(CENTRE)
                    );

    
    
    //fonts
    FT_Library ft;
    std::string fontFP = "../resources/fonts/";
    std::string currentFontName;
    std::vector<std::string> fontNames;
    int currentFontIndex = 0;

    
    TextRenderer();
    ~TextRenderer();

 
    void init();
    void loadFonts();
    int loadFont(const std::string& font);
    void initLibrary();
    void setupTextBuffers();
    void setTextUniformProjection(glm::mat4 proj);
    void setFont(std::string fontName);
    
    int textSize = 48;
    unsigned int textVAO, textVBO;
    std::map<std::string, std::map<char, Character>> fonts;
    

    glm::mat4 textProj;
    int textShaderProg;

};

struct TextDetails{
    float textLeft = 0.f;
    float textRight = (float)WIN_WIDTH;
    float textBottom = 0.f;
    float textTop = (float)WIN_HEIGHT;
    float textZNear = 0.f;
    float textZFar = 100.f;
};
//render text
//delete text
//attach texts (vector to attach to, offset from vector)

}//namespace shb