#include <model/Model.hpp>
#include <iostream>

Model::Model(FloatArray* array) {
  // Vertex Array Object (VAO) remembers how calls are made to VBO
  // next time we need to use the model, we can just bind the VAO and VBO will be automatically bound
  createVertexArrayObject();

  // Vertex Buffer Object (VBO) stores object coordinates
  createVertexBufferObject();

  // Bind VAO and start recording VBO calls
  bindVertexArrayObject();

  // Bind VBO
  bindVertexBufferObject();

  // Send the data to GPU
  sendDataToVertexBufferObject(array->Length(), array->Ptr());

  unbindVertexBufferObject();

  // Unbind VAO and end recording
  unbindVertexArrayObject();
}

Model::~Model() {
  GLuint VAO = this->vertexArrayObjectID;
  glDeleteVertexArrays(1, &VAO);

  GLuint VBO = this->vertexBufferObjectID;
  glDeleteBuffers(1, &VBO);
}

void Model::createVertexArrayObject() {
  GLuint VAO;

  // Generate single vertex array object
  glGenVertexArrays(1, &VAO);

  this->vertexArrayObjectID = VAO;
}

void Model::bindVertexArrayObject() {
  glBindVertexArray(this->vertexArrayObjectID);
}

void Model::unbindVertexArrayObject() {
  glBindVertexArray(0);
}

void Model::createVertexBufferObject() {
  GLuint VBO;

  // Generate single vertex buffer object
  glGenBuffers(1, &VBO);

  this->vertexBufferObjectID = VBO;
}

void Model::bindVertexBufferObject() {
  glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferObjectID);
}

/**
 * Precondition: VBO is bound on GL_ARRAY_BUFFER
 */
void Model::sendDataToVertexBufferObject(int length, const float* array) {
  // GL_STATIC_DRAW because the data is accessed many times but never changed
  glBufferData(GL_ARRAY_BUFFER, length * sizeof(float), array, GL_STATIC_DRAW);

  // Configure how the buffer data should be interpreted by vertex shader
  // In this simple case we are only passing one argument to the vertex shader

  // Pass vec3 as attribute 0, each vec3 denotes vertex coordinates in 3d space
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
  // Enable attribute 0
  glEnableVertexAttribArray(0);
}

void Model::unbindVertexBufferObject() {
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}