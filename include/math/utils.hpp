#pragma once

#include <cmath>

namespace math {
  const float PI = 3.14159265359f;

  inline float toRadians(float degrees) {
    return degrees * PI / 180.0f;
  }

  inline float toDegrees(float radians) {
    return radians * 180.0f / PI;
  }
}