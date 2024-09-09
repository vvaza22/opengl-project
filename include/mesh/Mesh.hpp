#pragma once

#include <vector>

class Mesh {
  public:
    Mesh(const std::vector<float>& vert) : vertices(vert) {}
    Mesh(const Mesh& other) : vertices(other.vertices) {}
    const float* ptr() const { return vertices.data(); }
    unsigned int size() const { return vertices.size(); }
  private:
    std::vector<float> vertices;
};
