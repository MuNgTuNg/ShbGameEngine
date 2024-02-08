#version 330 core

out vec4 FragColor;

in vec3 color;
in vec2 TexCoord;

//THIS REFERS TO THE TEXTURE UNIT I AM USING
uniform sampler2D tex;
void main()
{
    FragColor =  vec4(color,1.0f);
    FragColor =  texture(tex, TexCoord);
}