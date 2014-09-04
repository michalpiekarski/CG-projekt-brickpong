#version 330 core

in vec3 position;
in vec3 color;

uniform mat4 MVP;

out vec3 fragColor;

void main(){

	gl_Position =  MVP * vec4(position,1.0);

	fragColor = color;
}

