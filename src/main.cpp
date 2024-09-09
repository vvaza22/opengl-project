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
#include <matrixslayer/Vector.hpp>
#include <math/projections.hpp>
#include <math/rotations.hpp>

const int   WINDOW_WIDTH  = 800;
const int   WINDOW_HEIGHT = 600;
const char* WINDOW_TITLE  = "MY AMAZING WINDOW";
const float ASPECT_RATIO  = (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT;

// Ugly global variables
matrixslayer::Vector cameraStartingPosition = {0.0f, 0.0f, 2.0f};
Camera camera(cameraStartingPosition);
float lastX, lastY;
bool firstMouse = true;

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

void mouseCallback(GLFWwindow* window, double xpos, double ypos) {

  // Cast to float
  float x = static_cast<float>(xpos);
  float y = static_cast<float>(ypos);

  if (firstMouse) {
    lastX = x;
    lastY = y;
    firstMouse = false;
  }

  // When I move the mouse to the right, xpos increases
  float xoffset = x - lastX;
  // When I move the mouse up, ypos increases(since top-left corner is (0, 0))
  float yoffset = lastY - y;

  lastX = x;
  lastY = y;

  camera.ProcessMouseMovement(xoffset, yoffset);
}

GLFWwindow* CreateWindow() {
  // glfwGetPrimaryMonitor() to make window full screen
  GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, nullptr, nullptr);

  // Handle window resize
  glfwSetFramebufferSizeCallback(window, WindowResizeCallback);

  // glfwSetKeyCallback(window, key_callback);
  glfwSetCursorPosCallback(window, mouseCallback);
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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
  if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
    camera->ProcessKeyboard(DOWN, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    camera->ProcessKeyboard(UP, deltaTime);
}



void MainLoop(GLFWwindow* window) {
  ShaderFactory shaderFactory;
  ModelFactory  modelFactory;

  ShaderProgram* program = shaderFactory.CreateShaderProgram("glsl/wnormal/vertex.glsl", "glsl/wnormal/fragment.glsl");
  ShaderProgram* programl = shaderFactory.CreateShaderProgram("glsl/light/vertex.glsl", "glsl/light/fragment.glsl");

  // ShaderProgram* program = shaderFactory.CreateShaderProgram(
  //     "glsl/test/vertex.glsl", "glsl/test/fragment.glsl");

  Model* shape = modelFactory.CreateModel("data/wnormal/cube.obj");

  glEnable(GL_DEPTH_TEST);
  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  matrixslayer::Mat model = matrixslayer::Matrix4f({
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
  });

  matrixslayer::Mat t = matrixslayer::Matrix4f({
    1.0f, 0.0f, 0.0f, 5.0f,
    0.0f, 1.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f, -3.0f,
    0.0f, 0.0f, 0.0f, 1.0f
  });

  matrixslayer::Mat model2 = matrixslayer::Matrix4f({
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
  });

  // Rotate object around y-axis by 1 degrees every frame
  matrixslayer::Mat rotation = math::rotationX(math::toRadians(1.0f));
  matrixslayer::Mat rotation2 = math::rotationY(math::toRadians(2.0f));

  matrixslayer::Mat view = matrixslayer::Matrix4f({
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f,-2.0f,
    0.0f, 0.0f, 0.0f, 1.0f
  });

  matrixslayer::Mat projection = math::perspective(90.0f, ASPECT_RATIO, 0.1f, 100.0f); 

  matrixslayer::Vec lightColor = {1.0f, 1.0f, 1.0f};
  matrixslayer::Vec objectColor = {1.0f, 0.5f, 0.31f};
  matrixslayer::Vec objectColor2 = {0.0f, 0.0f, 0.55f};


  float deltaTime = 0.0f;
  float lastFrame = 0.0f;
  
  while (!glfwWindowShouldClose(window)) {
    float currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;


    matrixslayer::Vec lightPosition = {10*cos(currentFrame), 2.0f, sin(currentFrame)};
    matrixslayer::Mat lightModel = matrixslayer::Matrix4f({
      0.3f, 0.0f, 0.0f, lightPosition[0],
      0.0f, 0.3f, 0.0f, lightPosition[1],
      0.0f, 0.0f, 0.3f, lightPosition[2],
      0.0f, 0.0f, 0.0f, 1.0f
    });

    processInput(window, &camera, deltaTime);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    model = rotation * model;
    model2 = rotation2 * model2;
    matrixslayer::Mat objModel2 = t * model2;

    matrixslayer::Mat lookAt = camera.view();

    program->use();

    // Light properties
    program->SetVec3("lightColor", lightColor.ptr());
    program->SetVec3("lightPosition", lightPosition.ptr());
    program->SetVec3("objectColor", objectColor.ptr());
    program->SetMat4("model", model.ptr());
    program->SetMat4("view", lookAt.ptr());
    program->SetMat4("projection", projection.ptr());
    shape->draw();

    program->SetVec3("objectColor", objectColor2.ptr());
    program->SetMat4("model", objModel2.ptr());
    shape->draw();

    programl->use();
    programl->SetVec3("objectColor", lightColor.ptr());
    programl->SetMat4("model", lightModel.ptr());
    programl->SetMat4("view", lookAt.ptr());
    programl->SetMat4("projection", projection.ptr());
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
