#version 330 core

in vec3 position;
in vec3 color;
in vec3 normal;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

smooth out vec3 fragColor;

void main(){
    mat4 MVP = Projection * View * Model;
	gl_Position =  MVP * vec4(position,1.0);

    vec4 lightPosition = vec4(0.0, 0.0, 15.0, 1.0);
    vec4 positionInWorld = Model * vec4(position, 1.0);
    vec4 directionToLight = lightPosition - positionInWorld;
    directionToLight = View * directionToLight;
    mat4 normalModel = transpose(inverse(Model));
    vec4 normalInCameraSpace = normalize(normalModel * vec4(normal, 1.0));
    float cosAngIncidence = dot(normalInCameraSpace.xyz, directionToLight.xyz);
    cosAngIncidence = clamp(cosAngIncidence, 0, 1);
    float lightIntensity = 1.0;

	fragColor = lightIntensity * color * cosAngIncidence;
}

