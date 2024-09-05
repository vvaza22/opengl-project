#pragma once

#include <matrixslayer/Vector.hpp>
#include <matrixslayer/MatrixFactory.hpp>

enum Direction {
  FORWARD,
  BACKWARD,
  LEFT,
  RIGHT,
  UP,
  DOWN
};

class Camera {
public:
  Camera(const matrixslayer::Vec& cameraPosition);
  matrixslayer::Mat view() const;
  void ProcessKeyboard(Direction direction, float deltaTime);
  void ProcessMouseMovement(float xoffset, float yoffset);
private:
  matrixslayer::Vec position;

  // Vectors that describe how camera can move
  matrixslayer::Vec front; // If you follow this vector, you will move forward
  matrixslayer::Vec right; // If you follow this vector, you will move right
  matrixslayer::Vec up; // If you follow this vector, you will move up

  // Normalized coordinate axes for camera
  matrixslayer::Vec xAxisNorm;
  matrixslayer::Vec yAxisNorm;
  matrixslayer::Vec zAxisNorm;

  // Mouse movement up and down
  float pitchRadians;
  float yawRadians;

  // Uses Gram-Schmidt process to create coordinate axes for camera
  void updateCameraVectors();
};
