#version 330 core

layout (location = 0) in vec3 aPos;

uniform float aspectRatio;

void main(){
    vec3 correctedPos = aPos;
    correctedPos.x /= aspectRatio;
    gl_Position = vec4(correctedPos, 1.0);
}