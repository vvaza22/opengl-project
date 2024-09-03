#pragma once

#include <matrixslayer/MatrixFactory.hpp>
#include <math/utils.hpp>

namespace math {
  /*
   * Camera is at (0,0,0) and looking down the negative z-axis
   */
  matrixslayer::Mat perspective(float fov, float aspect, float near, float far) {
    float fovRad = toRadians(fov);
    float tanHalfFov = std::tan(fovRad / 2.0f);
    float tanInv = 1.0f / tanHalfFov;
    float A = tanInv / aspect;
    float B = tanInv;
    float C = (near + far) / (near - far);
    float D = (2.0f * near * far) / (near - far);
    return matrixslayer::Matrix4f({
      A   , 0.0f, 0.0f, 0.0f,
      0.0f, B   , 0.0f, 0.0f,
      0.0f, 0.0f, C   , D   ,
      0.0f, 0.0f,-1.0f, 0.0f
    });
  }
}
