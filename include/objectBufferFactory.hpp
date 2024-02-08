#pragma once
#include <buffers.hpp>

#include <object.hpp>
// class ObjectBufferDetails{
//     public:
//  //TODO:: detach buffers from object class as they can be reused.
//     ObjectBufferDetails(){
        
//     }
//     Buffer indexBuffer{BUFFER_TYPE_INDEX};
//     Buffer  vertexBuffer{BUFFER_TYPE_VERTEX};
//     unsigned int vao = 0;
// };
// enum ObjectBufferDataType{
//     BUFFERS_NONE,
//     BUFFERS_QUAD,
//     BUFFERS_CUBE,
//     NUM_BUFFERS
// };

// class ObjectBufferFactory{
//     public:
//     ObjectBufferFactory(){
//         //only creation of buffers
//         buffersQuad.indexBuffer.fillBuffer(VertexData::quad().indices);
//         buffersQuad.vertexBuffer.fillBuffer(VertexData::quad().vertices);
//         buffersQuad.vao = formatVertexBufferGetVAO(buffersQuad.vertexBuffer,
//         {
//         {VAO_FORMAT_VER, 3},
//         {VAO_FORMAT_COL, 3},
//         {VAO_FORMAT_TEX, 2}
//         }
//         );

//         buffersCube.indexBuffer.fillBuffer(VertexData::cubeTextured().indices);
//         buffersCube.vertexBuffer.fillBuffer(VertexData::cubeTextured().vertices);
//         buffersCube.vao = formatVertexBufferGetVAO(buffersCube.vertexBuffer,
//         {
//         {VAO_FORMAT_VER, 3},
//         {VAO_FORMAT_COL, 3},
//         {VAO_FORMAT_TEX, 2}
//         }
//         );
//     }
//     static void setBuffers(Object* object,ObjectBufferDataType type);

//     static ObjectBufferDetails buffersQuad;
//     static ObjectBufferDetails buffersCube;
// };


