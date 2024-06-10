#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ShaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Texture.h"

int main()
{
	// Setup
	glfwInit();
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Vertices for triangle
	//GLfloat vertices[] = {
	//	// Position				// Color
	//	-0.5f, -0.5f, 0.0f,		0.8f, 0.3f, 0.02f, // Lower left
	//	 0.5f, -0.5f, 0.0f,		0.8f, 0.3f, 0.02f, // Lower right
	//	 0.0f, 0.5f, 0.0f,		1.0f, 0.6f, 0.32f, // Upper middle
	//	 -0.25f, 0.0f, 0.0f,	0.9f, 0.45f, 0.17f, // Inner left
	//	 0.25f, 0.0f, 0.0f,		0.9f, 0.45f, 0.17f, // Inner right
	//	 0.0f, -0.5f, 0.0f,		0.8f, 0.3f, 0.02f, // Inner down
	//};

	//GLuint indices[] = {
	//	5, 3, 0,
	//	4, 2, 3,
	//	1, 4, 5
	//};

	unsigned int nVertices = 4;
	GLfloat vertices[] = {
		// Position				// Color			// UV
		-0.5f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	0.0f, 0.0f,
		-0.5f,  0.5f, 0.0f,		0.0f, 1.0f, 0.0f,	0.0f, 1.0f,
		 0.5f,  0.5f, 0.0f,		0.0f, 0.0f, 1.0f,	1.0f, 1.0f,
		 0.5f, -0.5f, 0.0f,		1.0f, 1.0f, 1.0f,	1.0f, 0.0f,
	};

	unsigned int nIndices = 6;
	GLuint indices[] = {
		0, 2, 1,
		0, 3, 2
	};
	
	// Create window
	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	
	gladLoadGL();
	glViewport(0, 0, 800, 600);

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

	// Get scale uniform
	GLuint uniScale = glGetUniformLocation(shaderProgram.ID, "scale");
	float scale = 0.5f;
	float scaleChange = 0.001f;

	// Texture
	Texture image("Assets/Textures/image.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	image.texUnit(shaderProgram, "tex0", 0);

	// Main loop
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.12f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		// Activate shader
		shaderProgram.Activate();
		
		// Set scale uniform
		glUniform1f(uniScale, scale);

		// Update scale logic
		scale += scaleChange;
		if (scale > 1.0f)
			scaleChange = -scaleChange;
		else if (scale < 0.5f)
			scaleChange = -scaleChange;

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