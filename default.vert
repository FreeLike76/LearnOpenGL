#version 330 core

// Input data
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTex;

// Output data
out vec3 color;
out vec2 texCoord;

// Config
uniform float scale;

void main()
{
   gl_Position = vec4(aPos.x + aPos.x * scale, aPos.y + aPos.y * scale, aPos.z + aPos.z * scale, 1.0);
   color = aColor;

   texCoord = aTex;
}