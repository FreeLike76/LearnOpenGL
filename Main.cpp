#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Utils.h"
#include "Mesh.h"
#include "Model.h"

//GLfloat vertices[] = {
//	// Position				// Color				 // UV			 // Normals
//	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,	 0.0f, -1.0f, 0.0f, // Bottom side
//	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 5.0f,	 0.0f, -1.0f, 0.0f, // Bottom side
//	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 5.0f,	 0.0f, -1.0f, 0.0f, // Bottom side
//	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,	 0.0f, -1.0f, 0.0f, // Bottom side
//
//	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,	-0.8f, 0.5f,  0.0f, // Left Side
//	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,	-0.8f, 0.5f,  0.0f, // Left Side
//	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,	-0.8f, 0.5f,  0.0f, // Left Side
//
//	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,	 0.0f, 0.5f, -0.8f, // Non-facing side
//	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,	 0.0f, 0.5f, -0.8f, // Non-facing side
//	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,	 0.0f, 0.5f, -0.8f, // Non-facing side
//
//	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,	 0.8f, 0.5f,  0.0f, // Right side
//	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,	 0.8f, 0.5f,  0.0f, // Right side
//	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,	 0.8f, 0.5f,  0.0f, // Right side
//
//	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,	 0.0f, 0.5f,  0.8f, // Facing side
//	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,	 0.0f, 0.5f,  0.8f, // Facing side
//	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,	 0.0f, 0.5f,  0.8f  // Facing side
//};
//
//GLuint indices[] = {
//	0, 1, 2,	// Bottom side
//	0, 2, 3,	// Bottom side
//	4, 6, 5,	// Left side
//	7, 9, 8,	// Non-facing side
//	10, 12, 11, // Right side
//	13, 15, 14	// Facing side
//};

//GLfloat vertices[] = {
//	// Position				// Color				 // UV			 // Normals
//	-1.0f, 0.0f,  1.0f,		0.0f, 0.0f, 0.0f,		0.0f, 0.0f,		0.0f, 1.0f, 0.0f,
//	-1.0f, 0.0f, -1.0f,		0.0f, 0.0f, 0.0f,		0.0f, 1.0f,		0.0f, 1.0f, 0.0f,
//	 1.0f, 0.0f, -1.0f,		0.0f, 0.0f, 0.0f,		1.0f, 1.0f,		0.0f, 1.0f, 0.0f,
//	 1.0f, 0.0f,  1.0f,		0.0f, 0.0f, 0.0f,		1.0f, 0.0f,		0.0f, 1.0f, 0.0f
//};
//GLuint indices[] =
//{
//	0, 1, 2,
//	0, 2, 3
//};

Vertex vertices[] = {
	Vertex{ glm::vec3(-1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f) },
	Vertex{ glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f) },
	Vertex{ glm::vec3(1.0f, 0.0f, -1.0f),  glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f) },
	Vertex{ glm::vec3(1.0f, 0.0f,  1.0f),  glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f) }
};
GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3
};

Vertex lightVertices[] = {
	Vertex{glm::vec3(-0.1f, -0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f, -0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f, -0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f, -0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f,  0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f,  0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f,  0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f,  0.1f,  0.1f)}
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

void setupGLFW()
{
	// Setup GLFW
	if (!glfwInit())
	{
		Log("Failed to initialize GLFW");
		exit(-1);
	}

	// Set OpenGL version to 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

GLFWwindow* createWindow(
	int width,
	int height,
	const char* title
) {
	GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (window == NULL)
	{
		Log("Failed to create GLFW window");
		glfwTerminate();
		exit(-1);
	}

	return window;
}

int main()
{
	Log("GLFW Setup");
	setupGLFW();

	Log("Creating window");
	int windowWidth = Utils::Constants::Screen::WIDTH;
	int windowHeight = Utils::Constants::Screen::HEIGHT;
	GLFWwindow* window = createWindow(windowWidth, windowHeight, "OpenGL");
	glfwMakeContextCurrent(window);

	Log("Glad load GL");
	gladLoadGL();
	glViewport(0, 0, windowWidth, windowHeight);

	// TextureType::ToString(TextureType::DIFFUSE)
	// TextureType::ToString(TextureType::SPECULAR)
	Log("Create textures");
	Texture textures[] = {
		Texture("Assets/Textures/Planks/planks.png", "diffuse", 0),
		Texture("Assets/Textures/Planks/planksSpec.png", "specular", 1)
	};

	Log("Init shader program");
	Shader shaderProgram("default.vert", "default.frag");

	Log("Creating mesh");
	std::vector <Vertex> meshFloorVertices(vertices, vertices + sizeof(vertices) / sizeof(vertices[0]));
	std::vector <GLuint> meshFloorIndices(indices, indices + sizeof(indices) / sizeof(indices[0]));
	std::vector <Texture> meshTextures(textures, textures + sizeof(textures) / sizeof(textures[0]));


	//Model model("Assets/Models/bunny/scene.gltf");
	Model model("Assets/Models/map/scene.gltf");

	//Mesh meshFloor(meshFloorVertices, meshFloorIndices, meshTextures);
	//Mesh meshFloor = model.Meshes[0];

	Log("Init light shader program");
	Shader lightShader("light.vert", "light.frag");

	Log("Creating light mesh");
	std::vector<Vertex> meshLightVertices(lightVertices, lightVertices + sizeof(lightVertices) / sizeof(lightVertices[0]));
	std::vector<GLuint> meshLightIndices(lightIndices, lightIndices + sizeof(lightIndices) / sizeof(lightIndices[0]));
	Mesh meshLight(meshLightVertices, meshLightIndices, meshTextures);

	// Light setup
	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	glm::mat4 lightModel = glm::mat4(1.0f);
	glm::vec3 lightPos = glm::vec3(0.5f, 5.0f, 0.5f);
	lightModel = glm::translate(lightModel, lightPos);

	// Object setup
	glm::mat4 objectModel = glm::mat4(1.0f);
	//glm::vec3 objectPos = glm::vec3(0.0f, 0.0f, 0.0f);
	//glm::vec3 objectScale = glm::vec3(2.0f, 2.0f, 2.0f);
	//objectModel = glm::scale(objectModel, objectScale);
	//objectModel = glm::rotate(objectModel, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	//objectModel = glm::translate(objectModel, objectPos);

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
		glm::value_ptr(objectModel)
	);
	glUniform4f(
		glGetUniformLocation(shaderProgram.ID, "lightColor"),
		lightColor.x, lightColor.y, lightColor.z, lightColor.w
	);
	glUniform3f(
		glGetUniformLocation(shaderProgram.ID, "lightPos"),
		lightPos.x, lightPos.y, lightPos.z
	);

	Log("Camera creation");
	Camera camera(windowWidth, windowHeight, glm::vec3(0.0f, 0.0f, 2.0f));
	camera.sensitivity = Utils::Constants::Camera::SENSITIVITY;

	Log("Main loop");
	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.12f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.Inputs(window);
		camera.UpdateMatrix(45.0f, 0.1f, 100.0f);

		//meshFloor.Draw(shaderProgram, camera);
		model.Draw(shaderProgram, camera);
		meshLight.Draw(lightShader, camera);

		// Swap the back and front buffers
		glfwSwapBuffers(window);

		// Poll for and process events
		glfwPollEvents();
	}

	// Clean up
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