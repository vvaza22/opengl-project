#include <camera/Camera.hpp>

const float SPEED = 2.5f;

Camera::Camera(const glm::vec3& pos) {
  position = pos;
  front = glm::vec3(0.0f, 0.0f, -1.0f);
  up = glm::vec3(0.0f, 1.0f, 0.0f);
  right = glm::normalize(glm::cross(front, up));
}

glm::mat4 Camera::GetViewMatrix() const {
  return glm::lookAt(position, position+front, up);
}

void Camera::ProcessKeyboard(Direction direction, float deltaTime) {
  float velocity = SPEED * deltaTime;
  if (direction == FORWARD)
    position += front * velocity;
  if (direction == BACKWARD)
    position -= front * velocity;
  if (direction == RIGHT)
    position += right * velocity;
  if (direction == LEFT)
    position -= right * velocity;
}