#version 330 core

// Input data
in vec3 color;
in vec2 texCoord;

// Output data
out vec4 FragColor;

// Uniforms
uniform sampler2D tex0;

void main()
{
   //FragColor = vec4(color, 1.0f);
   FragColor = texture(tex0, texCoord);
}