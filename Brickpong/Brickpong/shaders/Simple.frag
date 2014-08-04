#version 330 core

in vec3 fragColor;

out vec4 fragData;

void main(){
	fragData = vec4(fragColor, 1.0);
}
