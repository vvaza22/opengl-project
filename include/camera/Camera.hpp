#ifndef _Camera_
#define _Camera_

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

enum Direction {
  FORWARD,
  BACKWARD,
  LEFT,
  RIGHT
};

class Camera {
public:
  Camera(const glm::vec3& pos);
  glm::mat4 GetViewMatrix() const;
  void ProcessKeyboard(Direction direction, float deltaTime);
private:
  glm::vec3 position;
  glm::vec3 front;
  glm::vec3 up;
  glm::vec3 right;
};

#endif