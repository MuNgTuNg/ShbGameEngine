#pragma once
#include <glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
namespace shb{

enum VAOFormat{
    VAO_FORMAT_NONE,
    VAO_FORMAT_VER,
    VAO_FORMAT_COL,
    VAO_FORMAT_TEX,
    VAO_FORMAT_NORM,
    NUM_VAO_FORMATS
};

inline unsigned int createVAO(){
    unsigned int VAO = 0;
    glGenVertexArrays(1,&VAO);
    return VAO;
}
struct VAOFormatDetails{
    VAOFormat type;
    int verticesAmount;
};


enum bufferType{
    NONE,
    BUFFER_TYPE_INDEX,
    BUFFER_TYPE_VERTEX,
    NUM_TYPES
};


class Buffer{
 public:
    Buffer(int type_){
        type = type_;
        glGenBuffers(1,&ID);
    }
    

    /*
    * @brief careful using this one with vertex buffers as 
    *
    *
    */
    template<typename T>
    void fillBuffer(std::vector<T> data){
        glBindBuffer(type,ID);
        glBufferData(type,data.size() * sizeof(T),&data[0],GL_STATIC_DRAW);
        glBindBuffer(type,0);
    }
    ~Buffer(){
        glDeleteBuffers(1,&ID);
    }
    unsigned int id() const { return ID;}

    
 private:
 int type;
 unsigned int ID;
};


inline void fillBuffer(Buffer* buffer, std::vector<float> data, int type){
    glBindBuffer(type,buffer->id());
    glBufferData(type,data.size() * sizeof(float),&data[0],GL_STATIC_DRAW);
    glBindBuffer(type,0);
}


/**
 * @brief A buffer formatting function.
 * @param buffer The buffer to be bound and formatted.
 * @param formats a vector of VAOFormatDetails structs contatining the type
 * and the amount of vertices. The details will be sent to the gpu in the order of the vector
 * that is supplied to this function. The type parameter of the format is mainly for a visual que when creating the
 * vector, for easier debugging.
 * @todo make this type independant using templates.
 */
inline unsigned int formatVertexBufferGetVAO(Buffer buffer, std::vector<VAOFormatDetails> formats ){
    glBindBuffer(GL_ARRAY_BUFFER,buffer.id());
    unsigned int VAO = 0;
    glGenVertexArrays(1,&VAO);
    glBindVertexArray(VAO);
    int totalVertices = 0;
    for(auto format : formats){
        totalVertices += format.verticesAmount;
    }

    int iteration = 0;
    int verticesSoFar = 0;
    for(auto format : formats){
        glVertexAttribPointer(iteration, format.verticesAmount, GL_FLOAT, GL_FALSE, totalVertices * sizeof(float), (void*)(verticesSoFar*sizeof(float)));
        glEnableVertexAttribArray(iteration);
        verticesSoFar += format.verticesAmount;
        ++iteration;
    }
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);
    return VAO;
}

}//namespace shb