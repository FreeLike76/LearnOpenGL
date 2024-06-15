#include "Camera.h"

Camera::Camera(
	int width,
	int height,
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f)
) {
	this->width = width;
	this->height = height;
	Position = position;
}

void Camera::UpdateMatrix(
	float FOVdeg,
	float nearPlane,
	float farPlane
) {
	glm::mat4 view = glm::lookAt(
		Position,
		Position + Orientation,
		Up
	);
	glm::mat4 projection = glm::perspective(
		glm::radians(FOVdeg),
		(float)width / height,
		nearPlane,
		farPlane
	);
	CameraMatrix = projection * view;
}

void Camera::Matrix(Shader& shader, const char* uniform)
{
	shader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(CameraMatrix));
}

void Camera::Inputs(GLFWwindow* window)
{
	handleMouseInput(window);
	handleKeyboardInput(window);
}

void Camera::handleKeyboardInput(GLFWwindow* window)
{
	// SPEED
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		speed = Utils::Constants::Speed::SLOW;
	else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		speed = Utils::Constants::Speed::FAST;
	else
		speed = Utils::Constants::Speed::NORMAL;

	// WASD
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		Position += speed * Orientation;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		Position -= speed * Orientation;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		Position -= glm::normalize(glm::cross(Orientation, Up)) * speed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		Position += glm::normalize(glm::cross(Orientation, Up)) * speed;
}

void Camera::handleMouseInput(GLFWwindow* window)
{
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		if (firstClick)
		{
			glfwSetCursorPos(window, width / 2, height / 2);
			firstClick = false;
		}

		double mouseX, mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);

		float rotX = sensitivity * float(height / 2 - mouseY) / height;
		float rotY = sensitivity * float(width / 2 - mouseX) / width;

		// Rotate X
		glm::vec3 newOrientation = glm::rotate(
			Orientation,
			glm::radians(rotX),
			glm::normalize(glm::cross(Orientation, Up))
		);
		if (!(glm::angle(newOrientation, Up) <= glm::radians(5.0f) || glm::angle(newOrientation, -Up) <= glm::radians(5.0f)))
			Orientation = newOrientation;

		// Rotate Y
		Orientation = glm::rotate(
			Orientation,
			glm::radians(rotY),
			Up
		);

		glfwSetCursorPos(window, width / 2, height / 2);
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		firstClick = true;
	}
}