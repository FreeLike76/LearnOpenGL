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

	Log("Create textures");
	Texture textures[] = {
		Texture("Assets/Textures/Planks/planks.png", "diffuse", 0),
		Texture("Assets/Textures/Planks/planksSpec.png", "specular", 1)
	};

	Log("Init shader program");
	Shader shaderProgram("Assets/Shaders/Default/default.vert", "Assets/Shaders/Default/default.frag");
	// Shader shaderProgram("Assets/Shaders/Depth/depth.vert", "Assets/Shaders/Depth/depth.frag");

	Log("Creating mesh");
	std::vector <Vertex> meshFloorVertices(vertices, vertices + sizeof(vertices) / sizeof(vertices[0]));
	std::vector <GLuint> meshFloorIndices(indices, indices + sizeof(indices) / sizeof(indices[0]));
	std::vector <Texture> meshTextures(textures, textures + sizeof(textures) / sizeof(textures[0]));
	Mesh meshFloor(meshFloorVertices, meshFloorIndices, meshTextures);

	Model modelGTLF("Assets/Models/bunny/scene.gltf");
	//Model modelGTLF("Assets/Models/map/scene.gltf");

	Log("Init light shader program");
	Shader lightShader("Assets/Shaders/Light/light.vert", "Assets/Shaders/Light/light.frag");

	Log("Creating light mesh");
	std::vector<Vertex> meshLightVertices(lightVertices, lightVertices + sizeof(lightVertices) / sizeof(lightVertices[0]));
	std::vector<GLuint> meshLightIndices(lightIndices, lightIndices + sizeof(lightIndices) / sizeof(lightIndices[0]));
	std::vector <Texture> meshLighthTextures;
	Mesh meshLight(meshLightVertices, meshLightIndices, meshLighthTextures);

	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	glm::vec3 lightPos = glm::vec3(0.5f, 1.0f, 0.5f);
	lightModel = glm::translate(lightModel, lightPos);
	
	lightShader.Activate();
	glUniform4f(
		glGetUniformLocation(lightShader.ID, "lightColor"),
		lightColor.x, lightColor.y, lightColor.z, lightColor.w
	);
	glUniform3f(
		glGetUniformLocation(lightShader.ID, "lightPos"),
		lightPos.x, lightPos.y, lightPos.z
	);

	shaderProgram.Activate();
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

	Log("Configuration");
	glEnable(GL_DEPTH_TEST);

	// Occlusion culling
	// glEnable(GL_CULL_FACE);
	// glCullFace(GL_FRONT);
	// glFrontFace(GL_CW);

	// Vsync off
	// glfwSwapInterval(0);

	// Frame counter
	double timePrev = glfwGetTime();
	double timeCur = 0.0;

	Log("Main loop");
	while (!glfwWindowShouldClose(window))
	{
		// Frame time calculation
		timeCur = glfwGetTime();
		float frameTime = timeCur - timePrev;
		timePrev = timeCur;
		glfwSetWindowTitle(window, ("OpenGL - Frame time: " + std::to_string(frameTime)).c_str());

		// Reset buffers
		glClearColor(0.07f, 0.12f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Handle input
		camera.Inputs(window);
		camera.UpdateMatrix(45.0f, 0.1f, 100.0f);

		modelGTLF.Draw(shaderProgram, camera);
		meshFloor.Draw(shaderProgram, camera);
		meshLight.Draw(lightShader, camera, lightModel);

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