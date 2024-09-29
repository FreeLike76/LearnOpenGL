#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aColor;
layout (location = 3) in vec2 aTex;

out vec3 vPos;
out vec3 Normal;
out vec3 color;
out vec2 texCoord;

uniform mat4 model;
uniform mat4 camMatrix;

void main()
{
	vec4 worldPos = model * vec4(aPos, 1.0);

	gl_Position = camMatrix * worldPos;
	vPos = worldPos.xyz;
	color = aColor;
	
	//texCoord = aTex;
	//texCoord = vec2(aTex.x, 1.0 - aTex.y);
	texCoord = mat2(0.0, -1.0, 1.0, 0.0) * aTex;

	Normal = aNormal;
}