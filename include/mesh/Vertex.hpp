#pragma once

class Vertex {
public:
  Vertex(float posX, float posY, float posZ) : x(posX), y(posY), z(posZ), nx(0.0f), ny(0.0f), nz(0.0f) {}
  Vertex(const Vertex& other) : x(other.x), y(other.y), z(other.z), nx(other.nx), ny(other.ny), nz(other.nz) {}
  void setNormal(float normX, float normY, float normZ) {
    this->nx = normX;
    this->ny = normY;
    this->nz = normZ;
  }

  // Position
  float x, y, z;

  // Normal vector
  float nx, ny, nz;
};
