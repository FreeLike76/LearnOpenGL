#version 330 core

in vec3 color;
in vec2 texCoord;
in vec3 Normal;
in vec3 crntPos;

uniform sampler2D tex0;
uniform sampler2D tex1;
uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

out vec4 FragColor;

void main()
{
    // Config
	float ambient = 0.2f;
	float specularMult = 1.0f;

	// Diffuse
	vec3 normal = normalize(Normal);
	vec3 lightDir = normalize(lightPos - crntPos);
	float diffuse = max(dot(normal, lightDir), 0.0f);

	// Specular
	vec3 viewDir = normalize(viewPos - crntPos);
	vec3 reflectDir = reflect(-lightDir, normal);
	float specular = specularMult * pow(max(dot(viewDir, reflectDir), 0.0f), 32);
	
	// Final color
	vec4 texColor = texture(tex0, texCoord);
	float texSpecular = texture(tex1, texCoord).r;
	FragColor = lightColor * (texColor * (ambient + diffuse) + texSpecular * specular);

	// Normal mapping
	//FragColor = vec4(normal, 1.0f);
}