#version 330 core

out vec4 FragColor;

uniform vec3 rayColor;
in float alpha;

void main(){
    FragColor = vec4(rayColor, alpha);
}