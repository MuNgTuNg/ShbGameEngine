#version 330 core

out vec4 FragColor;
in vec3 color;
in vec3 pos;


uniform float iTime;
uniform int offset;
uniform int brightness;
uniform vec3 colors;
uniform float smoothstepStart;
uniform float smoothstepEnd;


vec3 palette( float t ){
    vec3 a = vec3(0.428, -0.782, 1.508);
    vec3 b = vec3(0.268, 2.198, 2.958);
    vec3 c = vec3(3.138, 3.138, 3.138);
    vec3 d = vec3(-1.342, -0.492, -0.672);

    return a + b*cos(6.28318*(c*t+d));
}

void main()
{
    vec3 uv = pos.xyz;
    vec3 uv0 = uv;
    vec3 finalColor = vec3(0.0);
    
    for(float i = 0.0; i < 4.0; i++){
        uv *=1.5;
        uv = fract(uv);
        uv-=0.5;

        float d = length(uv) * exp(-length(uv0));

        vec3 colors = palette(length(uv0) + i*.4 +iTime * 0.1);

        d = sin(d* offset - iTime*0.5)/offset;   
        d = abs(d); 
        d = smoothstep(smoothstepStart, smoothstepEnd,d);
        d = pow(0.02/d, 1.2);
        finalColor += colors* d;
    }
    //d = step(0.1,d);
    FragColor =  vec4(finalColor,1);
}