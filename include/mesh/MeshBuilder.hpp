#pragma once

#include <mesh/Mesh.hpp>
#include <mesh/Vertex.hpp>

class MeshBuilder {
public:
  MeshBuilder() = default;
  void addVertex(const Vertex& vertex) {
    vertices.push_back(vertex);
  }
  // Build mesh with only vertex coordinates
  Mesh* build() const {
    std::vector<float> data;
    for (const auto& vertex : this->vertices) {
      data.push_back(vertex.x);
      data.push_back(vertex.y);
      data.push_back(vertex.z);
    }
    return new Mesh(data);
  }
private:
  std::vector<Vertex> vertices;
};
