#include <shaders.hpp>
#include <files.hpp>
namespace shb{

std::string shaderPath = "../src/shaders/";

int createShaderProg(std::vector<Shader> shaders){
    const char* source;
    std::vector<int> handles;

    int success;
    char infoLog[512];

    for(int i = 0; i < shaders.size(); ++i){
        int handle = glCreateShader(shaders[i].type);
        std::string code = readFile(std::string(shaderPath + shaders[i].name).c_str());
        source = code.c_str();
        glShaderSource( handle,1,&source,NULL);
        glCompileShader(handle);

        
        glGetShaderiv(handle, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(handle, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        };
        handles.push_back(handle);
    }


    int shaderProg = glCreateProgram();
    for(int i = 0; i < handles.size(); ++i){
        glAttachShader(shaderProg,handles[i]);
    }

    glLinkProgram(shaderProg);
    glGetProgramiv(shaderProg, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(shaderProg, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    for(int i = 0; i < handles.size(); ++i){
        glDeleteShader(handles[i]);
    }


    return shaderProg;
}

}//namespace shb