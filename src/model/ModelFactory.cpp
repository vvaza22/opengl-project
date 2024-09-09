#include <model/ModelFactory.hpp>
#include <structures/FloatArray.hpp>
#include <filesystem/Reader.hpp>
#include <mesh/MeshBuilder.hpp>

Model* ModelFactory::CreateModel(const std::string& path) {
  MeshBuilder* builder = filesystem::ReadObject(path);
  Mesh* mesh = builder->build();

  // Copies array to GPU
  Model* model = new Model(mesh);

  // Can safely delete
  delete mesh;

  return model;
}
