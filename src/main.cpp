// clang-format off
#include <iostream>

// OPENGL Libraries MUST START WITH GLAD
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <camera/Camera.hpp>
#include <cmath>
#include <model/Model.hpp>
#include <model/ModelFactory.hpp>
#include <shader/ShaderFactory.hpp>
#include <shader/ShaderProgram.hpp>
#include <matrixslayer/MatrixFactory.hpp>

const int   WINDOW_WIDTH  = 800;
const int   WINDOW_HEIGHT = 600;
const char* WINDOW_TITLE  = "MY AMAZING WINDOW";
const float ASPECT_RATIO  = (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT;

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

GLFWwindow*
CreateWindow() {
  // glfwGetPrimaryMonitor()
  GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, nullptr, nullptr);

  // Handle window resize
  glfwSetFramebufferSizeCallback(window, WindowResizeCallback);

  // glfwSetKeyCallback(window, key_callback);
  // glfwSetCursorPosCallback(window, mouse_callback);
  // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  return window;
}

void processInput(GLFWwindow* window, Camera* camera, float deltaTime) {
  // Close the window on esc
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    camera->ProcessKeyboard(FORWARD, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    camera->ProcessKeyboard(BACKWARD, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    camera->ProcessKeyboard(LEFT, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    camera->ProcessKeyboard(RIGHT, deltaTime);
}

void MainLoop(GLFWwindow* window) {
  // glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);
  // Camera camera(cameraPosition);

  ShaderFactory shaderFactory;
  ModelFactory  modelFactory;

  ShaderProgram* program = shaderFactory.CreateShaderProgram(
      "glsl/test/vertex.glsl", "glsl/test/fragment.glsl");
  Model* shape = modelFactory.CreateModel("data/model/cube.obj");

  glEnable(GL_DEPTH_TEST);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  matrixslayer::Mat model = matrixslayer::Matrix4f({
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
  });

  matrixslayer::Mat view = matrixslayer::Matrix4f({
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 2.0f,
    0.0f, 0.0f, 0.0f, 1.0f
  });

  float fov     = 45.0f;
  float tangent = std::tan(glm::radians(fov / 2.0f));
  float far     = 100.0f;
  float near    = 0.1f;
  float C       = (-far - near) / (far - near);
  float D       = (2.0f * far * near) / (far - near);
  float d       = 1.0f / tangent;

  matrixslayer::Mat projection = matrixslayer::Matrix4f({
    d / ASPECT_RATIO, 0.0f, 0.0f, 0.0f,
    0.0f            , d   , 0.0f, 0.0f,
    0.0f            , 0.0f, C   , D   ,
    0.0f            , 0.0f, 1.0f, 1.0f
  });
  
  while (!glfwWindowShouldClose(window)) {
    // float currentFrame = static_cast<float>(glfwGetTime());
    // deltaTime = currentFrame - lastFrame;
    // lastFrame = currentFrame;

    // processInput(window, &camera, deltaTime);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    program->use();
    program->SetMat4("model", model.ptr());
    program->SetMat4("view", view.ptr());
    program->SetMat4("projection", projection.ptr());
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
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cerr << "Could not load GLAD" << std::endl;
    exit(1);
  }

  MainLoop(window);

  // Free resources
  glfwTerminate();

  return 0;
}
