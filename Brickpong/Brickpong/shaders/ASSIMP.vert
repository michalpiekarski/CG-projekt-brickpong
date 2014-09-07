#version 330 core

in vec3 position;
in vec3 color;
in vec3 normal;

uniform mat4 MVP;

out vec3 fragColor;

void main(){

	gl_Position =  MVP * vec4(position,1.0);

    // TODO: Niezb�dne jest przekszta�cenie vektora normalnego z przestrzeni obiektu w przestrze� �wiata
    float light = clamp(dot(normal, vec3(0.5,0.0,0.5)), 0, 1);

	fragColor = color * light;
}

