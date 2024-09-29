#version 330 core

layout (location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 camMatrix;

void main()
{
	vec4 worldPos = model * vec4(aPos, 1.0);
	gl_Position = camMatrix * worldPos;
}

// layout (location = 0) in vec3 aPos;
// layout (location = 1) in vec3 aNormal;
// layout (location = 2) in vec3 aColor;
// layout (location = 3) in vec2 aTex;

// uniform mat4 model;
// uniform mat4 camMatrix;

// void main()
// {
// 	vec4 worldPos = model * vec4(aPos, 1.0);
// 	gl_Position = camMatrix * worldPos;
// }