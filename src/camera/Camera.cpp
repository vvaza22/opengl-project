#include <camera/Camera.hpp>

const float SPEED = 2.5f;

Camera::Camera(const matrixslayer::Vec& cameraPosition) {
  position = cameraPosition;

  // Movement vectors
  front = matrixslayer::Vec({0.0f, 0.0f, -1.0f});
  right = matrixslayer::Vec({1.0f, 0.0f, 0.0f});

  updateCameraVectors();
}

void Camera::updateCameraVectors() {
  // Camera is looking down the negative z-axis initially
  target = position + front;

  // Build coordinate axes for camera
  matrixslayer::Vec cameraZ = position - target;

  // Gram-Schmidt process
  matrixslayer::Vec worldUp = {0.0f, 1.0f, 0.0f};
  matrixslayer::Vec cameraX = worldUp ^ cameraZ; // Cross product
  matrixslayer::Vec cameraY = cameraZ ^ cameraX;

  // Normalize
  xAxisNorm = cameraX / cameraX.length();
  yAxisNorm = cameraY / cameraY.length();
  zAxisNorm = cameraZ / cameraZ.length();
}

matrixslayer::Mat Camera::view() const {
  // Create matrix that moves camera in (0, 0, 0)
  matrixslayer::Mat moveCamera = matrixslayer::Matrix4f({
    1.0f, 0.0f, 0.0f, -position[0],
    0.0f, 1.0f, 0.0f, -position[1],
    0.0f, 0.0f, 1.0f, -position[2],
    0.0f, 0.0f, 0.0f, 1.0f
  });

  // Create matrix that aligns world axes with camera axes
  matrixslayer::Mat alignCamera = matrixslayer::Matrix4f({
    xAxisNorm[0], xAxisNorm[1], xAxisNorm[2], 0.0f,
    yAxisNorm[0], yAxisNorm[1], yAxisNorm[2], 0.0f,
    zAxisNorm[0], zAxisNorm[1], zAxisNorm[2], 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
  });

  // Create lookAt matrix
  matrixslayer::Mat lookAt = alignCamera * moveCamera;
  return lookAt;
}

void Camera::ProcessKeyboard(Direction direction, float deltaTime) {
  float velocity = SPEED * deltaTime;
  if (direction == FORWARD)
    position = position + front * velocity;
  if (direction == BACKWARD)
    position = position - front * velocity;
  if (direction == RIGHT)
    position = position + right * velocity;
  if (direction == LEFT)
    position = position - right * velocity;

  updateCameraVectors();
}
