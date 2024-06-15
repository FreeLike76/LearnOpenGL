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

GLfloat vertices[] = {
	// Position				// Color				 // UV			 // Normals
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,	 0.0f, -1.0f, 0.0f, // Bottom side
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 5.0f,	 0.0f, -1.0f, 0.0f, // Bottom side
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 5.0f,	 0.0f, -1.0f, 0.0f, // Bottom side
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,	 0.0f, -1.0f, 0.0f, // Bottom side

	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,	-0.8f, 0.5f,  0.0f, // Left Side
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,	-0.8f, 0.5f,  0.0f, // Left Side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,	-0.8f, 0.5f,  0.0f, // Left Side

	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,	 0.0f, 0.5f, -0.8f, // Non-facing side
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,	 0.0f, 0.5f, -0.8f, // Non-facing side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,	 0.0f, 0.5f, -0.8f, // Non-facing side

	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,	 0.8f, 0.5f,  0.0f, // Right side
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,	 0.8f, 0.5f,  0.0f, // Right side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,	 0.8f, 0.5f,  0.0f, // Right side

	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,	 0.0f, 0.5f,  0.8f, // Facing side
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,	 0.0f, 0.5f,  0.8f, // Facing side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,	 0.0f, 0.5f,  0.8f  // Facing side
};

GLuint indices[] = {
	0, 1, 2,	// Bottom side
	0, 2, 3,	// Bottom side
	4, 6, 5,	// Left side
	7, 9, 8,	// Non-facing side
	10, 12, 11, // Right side
	13, 15, 14	// Facing side
};

GLfloat lightVertices[] = {
	// Position
	-0.1f, -0.1f,  0.1f,
	-0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f,  0.1f,
	-0.1f,  0.1f,  0.1f,
	-0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f,  0.1f
};

GLuint lightIndices[] = {
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
};


void Log(const char* message)
{
	std::cout << message << std::endl;
}

int main()
{
	// Setup
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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

	Log("Window created");

	Shader shaderProgram("default.vert", "default.frag");

	// Create Vertex Array Object and bind it
	VAO VAO1;
	VAO1.Bind();

	// Create Vertex Buffer Object and Element Buffer Object
	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	// Link VBO to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));

	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	Log("Shader program created");

	Shader lightShader("light.vert", "light.frag");

	VAO lightVAO;
	lightVAO.Bind();

	VBO lightVBO(lightVertices, sizeof(lightVertices));
	EBO lightEBO(lightIndices, sizeof(lightIndices));

	lightVAO.LinkAttrib(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(GLfloat), (void*)0);

	lightVAO.Unbind();
	lightEBO.Unbind();
	lightVBO.Unbind();

	Log("Light shader created");

	glm::vec4 lightColor = glm::vec4(1.0f, 0.8f, 0.8f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.0, 1.5, 0.5);
	glm::mat4 lightModel = glm::translate(glm::mat4(1.0f), lightPos);

	glm::vec3 pyramidPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 pyramidModel = glm::mat4(1.0f);
	pyramidModel = glm::translate(pyramidModel, pyramidPos);

	lightShader.Activate();
	glUniformMatrix4fv(
		glGetUniformLocation(lightShader.ID, "model"),
		1, GL_FALSE,
		glm::value_ptr(lightModel)
	);
	glUniform4f(
		glGetUniformLocation(lightShader.ID, "lightColor"),
		lightColor.x, lightColor.y, lightColor.z, lightColor.w
	);
	
	shaderProgram.Activate();
	glUniformMatrix4fv(
		glGetUniformLocation(shaderProgram.ID, "model"),
		1, GL_FALSE,
		glm::value_ptr(pyramidModel)
	);
	glUniform4f(
		glGetUniformLocation(shaderProgram.ID, "lightColor"),
		lightColor.x, lightColor.y, lightColor.z, lightColor.w
	);
	glUniform3f(
		glGetUniformLocation(shaderProgram.ID, "lightPos"),
		lightPos.x, lightPos.y, lightPos.z
	);

	Log("Objects setup");

	Texture image("Assets/Textures/image.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	image.texUnit(shaderProgram, "tex0", 0);

	Log("Texture loaded");

	Camera camera(windowWidth, windowHeight, glm::vec3(0.0f, 0.0f, 2.0f));
	camera.sensitivity = Utils::Constants::Camera::SENSITIVITY;

	Log("Camera created");

	glEnable(GL_DEPTH_TEST);

	// Main loop
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.12f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.Inputs(window);
		camera.UpdateMatrix(45.0f, 0.1f, 100.0f);

		// Pyramid
		shaderProgram.Activate();
		camera.Matrix(shaderProgram, "camMatrix");
		image.Bind();
		VAO1.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);

		// Light
		lightShader.Activate();
		camera.Matrix(lightShader, "camMatrix");
		glUniform3f(
			glGetUniformLocation(lightShader.ID, "viewPos"),
			camera.Position.x, camera.Position.y, camera.Position.z
		);

		lightVAO.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);

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