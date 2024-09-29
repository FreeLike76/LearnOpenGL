#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "Utils.h"
#include "ShaderClass.h"

class Camera
{
public:
	glm::vec3 Position;
	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 CameraMatrix = glm::mat4(1.0f);

	bool firstClick = true;

	int width, height;
	float speed = 0.1f;
	float sensitivity = 20.0f;

	Camera(int width, int height, glm::vec3 position);

	void UpdateMatrix(float FOVdeg, float nearPlane, float farPlane);
	void Matrix(Shader& shader, const char* uniform);

	void Inputs(GLFWwindow* window);

private:
	void handleKeyboardInput(GLFWwindow* window);
	void handleMouseInput(GLFWwindow* window);
};

#endif