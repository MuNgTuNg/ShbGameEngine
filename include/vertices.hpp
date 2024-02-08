#pragma once
#include <vector>

namespace shb{

namespace VertexData{


struct Vertices{
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
};


inline Vertices cube(){
    return {
        {
            //VERT
                              //col                    //tex

            //front face
            -1.f, 1.f, 1.f,   0.208f, 0.49f,  0.929f, //top left front
            -1.f,-1.f,1.f,    0.337f, 0.933f, 0.957f,  //bottom left front
            1.f,-1.f,1.f,     0.329f, 0.22f,  0.863f,  //bottom right front
            -1.f, 1.f, 1.f,   0.208f, 0.49f, 0.929f,  //top left front
            1.f,-1.f,1.f,     0.329f, 0.22f, 0.863f, //bottom right front
            1.f,1.f,1.f,      0.196f, 0.91f, 0.459f,  //top right front

            //right side face
            1.f,1.f,1.f,      0.196f, 0.91f, 0.459f,  //top right front
            1.f,-1.f,1.f,     0.329f, 0.22f, 0.863f,  //bottom right front
            1.f,-1.f,-1.f,    0.698f, 0.298f,0.388f, //bottom right back
            1.f,1.f,1.f,      0.196f, 0.91f, 0.459f,  //top right front
            1.f,-1.f,-1.f,    0.698f, 0.298f,0.388f, //bottom right back
            1.f,1.f,-1.f,     0.875f, 0.231f,0.341f,  //top right back

            //back face
            1.f,1.f,-1.f,     0.875f, 0.231f,0.341f,  //top right back
            1.f,-1.f,-1.f,    0.698f, 0.298f,0.388f,  //bottom right back
            -1.f,-1.f,-1.f,   0.435f, 0.486f, 0.071,  //bottom left back
            -1.f,1.f,-1.f,    0.996f, 0.306f, 0.f,   //top left back
            -1.f,-1.f,-1.f,   0.435f, 0.486f, 0.071,  //bottom left back
            1.f,1.f,-1.f,     0.875f, 0.231f,0.341f,  //top right back

            //left side face
            -1.f,  1.f,  -1.f, 1.f, 0.682f, 0.012f,  //top left back
            -1.f, -1.f, -1.f,  1.f, 0.682f, 0.012f,  //bottom left back
            -1.f,  1.f,  1.f,  1.f, 0.682f, 0.012f,  //top left front
            -1.f, 1.f, 1.f,    0.67f, 0.278f, 0.525f, //top left front
            -1.f, -1.f, -1.f,  0.67f, 0.278f, 0.525f, //bottom left back
            -1.f, -1.f, 1.f,   0.67f, 0.278f, 0.525f, //bottom left front

            //bottom face
            -1.f,-1.f,-1.f,  0.984f, 0.863f, 0.886f,  //bottom back left
            -1.f,-1.f,1.f,   0.984f, 0.863f, 0.886f,  //bottom front left
            1.f,-1.f,1.f,    0.984f, 0.863f, 0.886f,  //bottom front right
            1.f,-1.f,-1.f,   1.f, 0.624f, 0.698f,     //bottom back right
            -1.f,-1.f,-1.f,  1.f, 0.624f, 0.698f,     //bottom back left
            1.f,-1.f,1.f,    1.f, 0.624f, 0.698f,     //bottom front right

            //top face
            -1.f,1.f,-1.f,  0.604f, 0.478f, 0.627f, //top left back
            -1.f,1.f,1.f,   0.604f, 0.478f, 0.627f, //top left front
            1.f,1.f,1.f,    0.604f, 0.478f, 0.627f, //top right front
            -1.f,1.f,-1.f,  0.604f, 0.478f, 0.627f, //top left back
            1.f,1.f,1.f,    0.604f, 0.478f, 0.627f, //top right front
            1.f,1.f,-1.f,   0.604f, 0.478f, 0.627f //top right back


            
        },
        {
            0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36
        }
   
    };
}

inline Vertices cubeTextured(){
    return {
        {
            //VERT
                              //col                    //tex

            //front face
            -1.f, 1.f, 1.f,   0.208f, 0.49f,  0.929f,   0.f, 1.f, //top left front
            -1.f,-1.f,1.f,    0.337f, 0.933f, 0.957f,  0.f,0.f,  //bottom left front
            1.f,-1.f,1.f,     0.329f, 0.22f,  0.863f,  1.f, 0.f, //bottom right front
            -1.f, 1.f, 1.f,   0.208f, 0.49f, 0.929f,   0.f, 1.f, //top left front
            1.f,-1.f,1.f,     0.329f, 0.22f, 0.863f,   1.f, 0.f, //bottom right front
            1.f,1.f,1.f,      0.196f, 0.91f, 0.459f,   1.f, 1.f,  //top right front

            //right side face
            1.f,1.f,1.f,      0.196f, 0.91f, 0.459f,   0.f, 1.f,  //top right front
            1.f,-1.f,1.f,     0.329f, 0.22f, 0.863f,   0.f, 0.f, //bottom right front
            1.f,-1.f,-1.f,    0.698f, 0.298f,0.388f,   1.f, 0.f, //bottom right back
            1.f,1.f,1.f,      0.196f, 0.91f, 0.459f,   0.f, 1.f,  //top right front
            1.f,-1.f,-1.f,    0.698f, 0.298f,0.388f,   1.f, 0.f, //bottom right back
            1.f,1.f,-1.f,     0.875f, 0.231f,0.341f,   1.f, 1.f, //top right back

            //back face
            1.f,1.f,-1.f,     0.875f, 0.231f,0.341f,   0.f, 1.f, //top right back
            1.f,-1.f,-1.f,    0.698f, 0.298f,0.388f,   0.f, 0.f, //bottom right back
            -1.f,-1.f,-1.f,   0.435f, 0.486f, 0.071,   1.f, 0.f, //bottom left back
            -1.f,1.f,-1.f,    0.996f, 0.306f, 0.f,     1.f, 1.f,//top left back
            -1.f,-1.f,-1.f,   0.435f, 0.486f, 0.071,   1.f, 0.f, //bottom left back
            1.f,1.f,-1.f,     0.875f, 0.231f,0.341f,   0.f, 1.f, //top right back

            //left side face
            -1.f,  1.f,  -1.f, 1.f, 0.682f, 0.012f,  0.f, 1.f,//top left back
            -1.f, -1.f, -1.f,  1.f, 0.682f, 0.012f,  0.f, 0.f,//bottom left back
            -1.f,  1.f,  1.f,  1.f, 0.682f, 0.012f,  1.f, 1.f,//top left front
            -1.f, 1.f, 1.f,    0.67f, 0.278f, 0.525f, 1.f, 1.f, //top left front
            -1.f, -1.f, -1.f,  0.67f, 0.278f, 0.525f, 0.f, 0.f, //bottom left back
            -1.f, -1.f, 1.f,   0.67f, 0.278f, 0.525f, 1.f, 0.f, //bottom left front

            //bottom face
            -1.f,-1.f,-1.f,  0.984f, 0.863f, 0.886f,  0.f,0.f,//bottom back left
            -1.f,-1.f,1.f,   0.984f, 0.863f, 0.886f,  0.f,1.f,//bottom front left
            1.f,-1.f,1.f,    0.984f, 0.863f, 0.886f,  1.f,1.f,//bottom front right
            1.f,-1.f,-1.f,   1.f, 0.624f, 0.698f,   1.f,0.f,//bottom back right
            -1.f,-1.f,-1.f,  1.f, 0.624f, 0.698f,   0.f,0.f,//bottom back left
            1.f,-1.f,1.f,    1.f, 0.624f, 0.698f,   1.f,1.f,//bottom front right

            //top face
            -1.f,1.f,-1.f,  0.604f, 0.478f, 0.627f, 0.f,1.f,//top left back
            -1.f,1.f,1.f,   0.604f, 0.478f, 0.627f, 0.f,0.f,//top left front
            1.f,1.f,1.f,    0.604f, 0.478f, 0.627f, 1.f,0.f,//top right front
            -1.f,1.f,-1.f,  0.604f, 0.478f, 0.627f, 0.f,1.f,//top left back
            1.f,1.f,1.f,    0.604f, 0.478f, 0.627f, 1.f,0.f,//top right front
            1.f,1.f,-1.f,   0.604f, 0.478f, 0.627f, 1.f,1.f//top right back


            
        },
        {
            0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36
        }
   
    };
}



inline Vertices quad(){
    //VERT
    return{
    { //xyz            //col          //tex
      0.5f,   0.5f,  0.1f,    1.f,0.f,0.f,   2.f, 2.f,
      0.5f,  -0.5f,  0.1f,    0.f,1.f,0.f,   2.f, 0.0f,
     -0.5f,  -0.5f,  0.1f,    0.f,0.f,1.f,   0.0f, 0.0f,
     -0.5f,   0.5f,  0.1f,    1.f,0.f,1.f,   0.0f, 2.f
    },
    //IND
    {
     0,1,3,  //bottom left, top left, top right
     1,2,3   //bottom left, top right, borttom right
    }
    };
}

}//namespace vertices
}//namespace shb