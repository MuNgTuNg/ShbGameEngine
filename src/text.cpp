#include <text.hpp>
#include <bitset>
#include <checkpoints.hpp>
namespace shb{

    

void TextRenderer::rendertext(std::string text , glm::vec3 pos){
    glm::mat4 textModel{1.f};
    //textPos.x =
    //textPos.y = abs(sin((float)glfwGetTime())) * 0.5;
    //textPos.z = cos((float)glfwGetTime());  
    //textModel *= glm::translate(glm::mat4{1.f},textPos);
    //textModel *= glm::rotate(glm::mat4{1.f},glm::radians((float)glfwGetTime()*10),{0,1,0});
    
    glUseProgram(textShaderProg);     
    glUniform3f(glGetUniformLocation(textShaderProg,"textColor"),color_.x,color_.y,color_.z);
    glUniformMatrix4fv(glGetUniformLocation(textShaderProg,"model"),1,GL_FALSE,&textModel[0][0]);
    glUniform1f(glGetUniformLocation(textShaderProg,"scale"),scale_);
    
    glActiveTexture(GL_TEXTURE15); //fix
    glUniform1i(glGetUniformLocation(textShaderProg, "text"), 15);
    glBindVertexArray(textVAO);

    std::map<char, Character> characters = fonts[currentFontName];
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++){
        Character ch = characters[*c];
        float xpos = pos.x + ch.Bearing.x * scale_;
        float ypos = pos.y - (ch.Size.y - ch.Bearing.y) * scale_;
        float w = ch.Size.x * scale_;
        float h = ch.Size.y * scale_;
        //Todo:: reformat these so that i can have a third dimension to the rendering of the text.
        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 0.0f },            
            { xpos,     ypos,       0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 1.0f },

            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos + w, ypos,       1.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 0.0f }           
        };
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        glBindBuffer(GL_ARRAY_BUFFER, textVBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); 
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        pos.x += (ch.Advance >> 6) * scale_;
    }
    scale_ = 1.f; //reset text size
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void TextRenderer::setFont(std::string fontName){    
    currentFontName = fontName;
    //currentFontIndex = fontNames.find(currentFontName); //todo:: font index system
}

//Load font from a file into OpenGL. File is loaded in bitmap form, and then stored in an 
//OpenGL texture, inside a character struct, and then paired with a font in a map
int TextRenderer::loadFont(const std::string& font){
    GLint previousUnpackAlignment;
    glGetIntegerv(GL_UNPACK_ALIGNMENT, &previousUnpackAlignment);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction

    FT_Face face;
    std::string fontAndPath = fontFP + font;  //TODO:: font choosing system
    if (FT_New_Face(ft, fontAndPath.c_str(), 0, &face))
    {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;  
        return -1;
    }
        

    FT_Set_Pixel_Sizes(face, 0, textSize); 
    //printFaceDetails(face);

    std::map<char, Character> characters;
    for(unsigned char c = 0; c < 128; c++){
        // load character glyph and render it's bitmap data
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }
        unsigned int texture;
        glGenTextures(1,&texture);
        glBindTexture(GL_TEXTURE_2D,texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        Character character = {
            texture,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows ),
            glm::ivec2(face->glyph->bitmap_left,face->glyph->bitmap_top),
            face->glyph->advance.x
        };
        characters.insert(std::pair<char,Character>(c,character));
    }
    fonts.insert(std::pair<std::string,std::map<char, Character>>(font,characters));
    FT_Done_Face(face);
    
    
    //return to previous pixel unpack alignment
    glPixelStorei(GL_UNPACK_ALIGNMENT, previousUnpackAlignment);
    return 0;
}



TextRenderer::TextRenderer(){
    
    if (FT_Init_FreeType(&ft))
    {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
    }
    
}

void TextRenderer::loadFonts(){
    checkpoint("fonts loading.");
    std::vector<std::filesystem::__cxx11::directory_entry> fontFiles;
    readFilesInDirectoryFromExtensions(".ttf",fontFP,fontFiles);

    for(auto font : fontFiles){
        loadFont(font.path().filename());
        fontNames.push_back(font.path().filename());
    }
    
    currentFontName = fontNames.front();
}

void TextRenderer::init(){
    
    loadFonts();
    
    textShaderProg = createShaderProg(
    {   {"text_shader.vert",GL_VERTEX_SHADER}, 
        {"text_shader.frag",GL_FRAGMENT_SHADER}    
    }
    );
    setupTextBuffers();
    setTextUniformProjection(glm::ortho(0.f,(float)WIN_WIDTH,0.f,(float)WIN_HEIGHT,0.f,100.f));
    
    //setTextUniformProjection(glm::perspective(glm::radians(90.f),(float)WIN_WIDTH/WIN_HEIGHT,0.1f,10000.f));
}


void TextRenderer::setTextUniformProjection(glm::mat4 proj){
    textProj = proj;
    glUseProgram(textShaderProg);
    glUniformMatrix4fv(glGetUniformLocation(textShaderProg, "projection"), 1 , GL_FALSE, glm::value_ptr(textProj));
}


void TextRenderer::setupTextBuffers(){
    glGenVertexArrays(1,&textVAO);
    glGenBuffers(1, &textVBO);
    glBindVertexArray(textVAO);
    glBindBuffer(GL_ARRAY_BUFFER, textVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);   
}
TextRenderer::~TextRenderer(){
    FT_Done_FreeType(ft);
    glDeleteBuffers(1,&textVBO);
    glDeleteVertexArrays(1,&textVAO);
}

}//namespace shb