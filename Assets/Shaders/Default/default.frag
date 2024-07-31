#version 330 core

in vec3 vPos;
in vec3 Normal;
in vec3 color;
in vec2 texCoord;

uniform sampler2D diffuse0;
uniform sampler2D specular0;

uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;

out vec4 FragColor;

float zNear = 0.1f;
float zFar = 100.0f;

vec4 pointLight(
	float ambient = 0.2f,
	float specularMult = 1.0f
) {
	// Light dir
	vec3 lightVec = lightPos - vPos;
	vec3 lightDir = normalize(lightVec);
	float dist = length(lightVec);
	
	// Attenuation
	float constant = 1.0f;
	float linear = 0.09f;
	float quadratic = 0.032f;
	float attenuation = 1.0f / (constant + linear * dist + quadratic * (dist * dist));

	// Diffuse
	vec3 normal = normalize(Normal);
	float diffuse = max(dot(normal, lightDir), 0.0f);
	//diffuse *= attenuation;

	// Specular
	vec3 viewDir = normalize(camPos - vPos);
	vec3 reflectDir = reflect(-lightDir, normal);
	float specular = specularMult * pow(max(dot(viewDir, reflectDir), 0.0f), 16);
	//specular *= attenuation;

	// Final color
	vec4 texColor = texture(diffuse0, texCoord);
	float texSpecular = texture(specular0, texCoord).r;
	return lightColor * (texColor * (ambient + diffuse) + texSpecular * specular);
}

float linearizeDepth(float depth) {
	return (2.0f * zNear * zFar) / (zFar + zNear -(depth * 2.0 - 1.0) * (zFar - zNear));
}

void main()
{
	float ambient = 0.2f;
	float specularMult = 1.0f;
	//FragColor = pointLight(ambient, specularMult);

	// Normal mapping
	// FragColor = vec4(Normal, 1.0f);

	// Depth mapping
	float depth = gl_FragCoord.z;
	float linearDepth = linearizeDepth(depth);
	float normalizedDepth = linearDepth / zFar;
	FragColor = vec4(vec3(normalizedDepth), 1.0f);
}