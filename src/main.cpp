#include <iostream>

// OPENGL Libraries MUST START WITH GLAD
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
	Model* shape = modelFactory.CreateModel("data/model/cube.obj");

	glEnable(GL_DEPTH_TEST);

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	projection = glm::perspective(glm::radians(45.0f), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);

	while(!glfwWindowShouldClose(window)) {
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		program->use();
		program->SetMat4("model", model);
		program->SetMat4("view", view);
		program->SetMat4("projection", projection);
		shape->draw();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	delete shape;
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
