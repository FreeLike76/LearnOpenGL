#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ShaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Texture.h"
#include "Camera.h"
#include "Utils.h"

int main()
{
	// Setup
	glfwInit();
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Vertices for triangle
	unsigned int nVertices = 5;
	GLfloat vertices[] = {
		// Position				// Color			// UV
		-0.5f,  0.0f,  0.5f,		1.0f, 0.0f, 0.0f,	0.0f, 0.0f,
		-0.5f,  0.0f, -0.5f,		0.0f, 1.0f, 0.0f,	0.0f, 1.0f,
		 0.5f,  0.0f, -0.5f,		0.0f, 0.0f, 1.0f,	1.0f, 1.0f,
		 0.5f,  0.0f,  0.5f,		0.0f, 0.0f, 0.0f,	1.0f, 0.0f,
		 0.0f,  0.8f,  0.0f,		1.0f, 1.0f, 1.0f,	0.5f, 0.5f,
	};

	unsigned int nIndices = 18;
	GLuint indices[] = {
		0, 4, 1,
		1, 4, 2,
		2, 4, 3,
		3, 4, 0,
		0, 1, 2,
		0, 2, 3
	};
	
	// Create window
	int windowWidth = Utils::Constants::Screen::WIDTH;
	int windowHeight = Utils::Constants::Screen::HEIGHT;
	GLFWwindow* window = glfwCreateWindow(
		windowWidth,
		windowHeight,
		"OpenGL", NULL, NULL
	);

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	
	gladLoadGL();
	glViewport(0, 0, windowWidth, windowHeight);

	Shader shaderProgram("default.vert", "default.frag");

	// Create Vertex Array Object and bind it
	VAO VAO1;
	VAO1.Bind();

	// Create Vertex Buffer Object and Element Buffer Object
	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	// Link VBO to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(GLfloat), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(GLfloat), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(GLfloat), (void*)(6 * sizeof(float)));
	
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// Texture
	Texture image("Assets/Textures/image.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	image.texUnit(shaderProgram, "tex0", 0);

	glEnable(GL_DEPTH_TEST);

	Camera camera(windowWidth, windowHeight, glm::vec3(0.0f, 0.0f, 2.0f));
	camera.sensitivity = Utils::Constants::Camera::SENSITIVITY;

	// Main loop
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.12f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		// Activate shader
		shaderProgram.Activate();
		
		camera.Inputs(window);
		camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");

		// Transforms
		//glm::mat4 model(1.0f);
		//glm::mat4 view(1.0f);
		//glm::mat4 projection(1.0f);
		//model = glm::rotate(model, float(glfwGetTime()), glm::vec3(0.0f, 1.0f, 0.0f));
		//view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));
		//projection = glm::perspective(glm::radians(45.0f), float(WIDTH) / float(HEIGHT), 0.1f, 100.0f);
		//// Set matrix uniforms
		//int uniModel = glGetUniformLocation(shaderProgram.ID, "model");
		//glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));
		//int uniView = glGetUniformLocation(shaderProgram.ID, "view");
		//glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));
		//int uniProjection = glGetUniformLocation(shaderProgram.ID, "projection");
		//glUniformMatrix4fv(uniProjection, 1, GL_FALSE, glm::value_ptr(projection));

		// Set texture to draw
		image.Bind();

		// Draw triangles
		VAO1.Bind();
		glDrawElements(GL_TRIANGLES, nIndices, GL_UNSIGNED_INT, 0);
		
		// Swap the back and front buffers
		glfwSwapBuffers(window);

		// Poll for and process events
		glfwPollEvents();
	}

	// Clean up
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	image.Delete();
	shaderProgram.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
	
	return 0;
}