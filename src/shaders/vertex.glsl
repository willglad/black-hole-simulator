#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in float aAlpha;

uniform float aspectRatio;

out float alpha;

void main(){
    vec3 correctedPos = aPos;
    correctedPos.x /= aspectRatio;
    gl_Position = vec4(correctedPos, 1.0);
    alpha = aAlpha;
}