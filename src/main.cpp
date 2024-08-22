#include <iostream>

// OPENGL Libraries MUST START WITH GLAD
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <shader/ShaderProgram.hpp>
#include <shader/ShaderFactory.hpp>

const int WINDOW_WIDTH = 1366;
const int WINDOW_HEIGHT = 768;
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
	GLFWwindow* window =
		glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, glfwGetPrimaryMonitor(), nullptr);

	// Handle window resize
	glfwSetFramebufferSizeCallback(window, WindowResizeCallback);

	// glfwSetKeyCallback(window, key_callback);
	// glfwSetCursorPosCallback(window, mouse_callback);  
	// glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  

	return window;
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

	ShaderFactory shaderFactory;
	ShaderProgram* program = 
		shaderFactory.CreateShaderProgram("glsl/test/vertex.glsl", "glsl/test/fragment.glsl");
	
	delete program;

	// Free resources
	glfwTerminate();

	return 0;
}
