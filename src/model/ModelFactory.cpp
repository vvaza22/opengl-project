#include <model/ModelFactory.hpp>
#include <structures/FloatArray.hpp>
#include <filesystem/Reader.hpp>

Model* ModelFactory::CreateModel(const std::string& path) {
  FloatArray* array = filesystem::ReadFloatArray(path);
  // Copies array to GPU
  Model* model = new Model(array);
  // Can safely delete
  delete array;

  return model;
}