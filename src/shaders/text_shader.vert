
#version 330 core
layout (location = 0) in vec4 vertex; // <vec2 pos, vec2 tex>
out vec2 TexCoords;

uniform mat4 projection;
uniform mat4 model;
uniform float scale;

void main()
{   
    
    gl_Position = model * projection * vec4(vertex.x ,vertex.y,0, 1.0);
    TexCoords = vertex.zw;
}  