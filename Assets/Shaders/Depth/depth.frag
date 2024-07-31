#version 330 core

out vec4 FragColor;

float zNear = 0.1f;
float zFar = 100.0f;

float linearizeDepth(float depth) {
	return (2.0f * zNear * zFar) / (zFar + zNear -(depth * 2.0 - 1.0) * (zFar - zNear));
}

void main()
{
 	float depth = gl_FragCoord.z;
	float linearDepth = linearizeDepth(depth);
	float normalizedDepth = linearDepth / zFar;
	FragColor = vec4(vec3(normalizedDepth), 1.0f);
}

// float zNear = 0.1f;
// float zFar = 100.0f;

// float linearizeDepth(float depth, float zNear, float zFar)
// {
// 	return (2.0f * zNear) / (zFar + zNear - depth * (zFar - zNear));
// }

// void main()
// {

// 	float depth = gl_FragCoord.z;
// 	float linearDepth = linearizeDepth(depth, zNear, zFar);
// 	float normalizedDepth = linearDepth / zFar;
// 	FragColor = vec4(vec3(normalizedDepth), 1.0f);
// }
