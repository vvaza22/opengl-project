#pragma once

#include <cmath>
#include <matrixslayer/MatrixFactory.hpp>

namespace math {
  // Creates a rotation matrix around the y-axis
  matrixslayer::Mat rotationY(float angleRad) {
    return matrixslayer::Matrix4f({
      std::cos(angleRad) , 0.0f, std::sin(angleRad), 0.0f,
      0.0f               , 1.0f, 0.0f              , 0.0f,
      -std::sin(angleRad), 0.0f, std::cos(angleRad), 0.0f,
      0.0f               , 0.0f, 0.0f              , 1.0f
    });
  }
}
