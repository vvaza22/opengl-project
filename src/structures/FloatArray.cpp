#include <structures/FloatArray.hpp>

FloatArray::FloatArray(int length, float* array) {
  this->length = length;
  this->array = array;
}

FloatArray::~FloatArray() {
  delete[] this->array;
}

int FloatArray::Length() const {
  return this->length;
}

const float* FloatArray::Ptr() const {
  return this->array;
}