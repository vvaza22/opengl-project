#include <iostream>

// OPENGL Libraries MUST START WITH GLAD
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <shader/ShaderProgram.hpp>
#include <shader/ShaderFactory.hpp>
#include <model/Model.hpp>
#include <model/ModelFactory.hpp>

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
const char* WINDOW_TITLE = "MY AMAZING WINDOW";

void InitProgram() {
	// Initialize GLFW
	glfwInit();

	// Request at least OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// Request the core profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void WindowResizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

GLFWwindow* CreateWindow() {
	//glfwGetPrimaryMonitor()
	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, nullptr, nullptr);

	// Handle window resize
	glfwSetFramebufferSizeCallback(window, WindowResizeCallback);

	//glfwSetKeyCallback(window, key_callback);
	//glfwSetCursorPosCallback(window, mouse_callback);  
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  

	return window;
}

void MainLoop(GLFWwindow* window) {
	ShaderFactory shaderFactory;
	ModelFactory modelFactory;

	ShaderProgram* program = 
		shaderFactory.CreateShaderProgram("glsl/test/vertex.glsl", "glsl/test/fragment.glsl");
	Model* model = modelFactory.CreateModel("data/model/triangle.obj");

	while(!glfwWindowShouldClose(window)) {
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		program->use();
		model->draw();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	delete model;
	delete program;
}

int main() {
	// Initialize GLFW
	InitProgram();

	// Create window where objects are drawn
	GLFWwindow* window = CreateWindow();

	// OpenGL is a state-machine
	glfwMakeContextCurrent(window);

	// Load GLAD
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Could not load GLAD" << std::endl;
		exit(1);
	}

	MainLoop(window);

	// Free resources
	glfwTerminate();

	return 0;
}
