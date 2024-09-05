#pragma once

#include <matrixslayer/Vector.hpp>
#include <matrixslayer/MatrixFactory.hpp>

enum Direction {
  FORWARD,
  BACKWARD,
  LEFT,
  RIGHT
};

class Camera {
public:
  Camera(const matrixslayer::Vec& cameraPosition);
  matrixslayer::Mat view() const;
  void ProcessKeyboard(Direction direction, float deltaTime);
private:
  matrixslayer::Vec position;

  // Vectors that describe how camera can move
  matrixslayer::Vec front; // If you follow this vector, you will move forward
  matrixslayer::Vec right; // If you follow this vector, you will move right

  // What point the camera is looking at
  matrixslayer::Vec target;

  // Normalized coordinate axes for camera
  matrixslayer::Vec xAxisNorm;
  matrixslayer::Vec yAxisNorm;
  matrixslayer::Vec zAxisNorm;

  // Uses Gram-Schmidt process to create coordinate axes for camera
  void updateCameraVectors();
};
