#include <structures/FloatArray.hpp>

FloatArray::FloatArray(int l, float* a) : length(l) {
  this->array = new float[l];
  for (int i = 0; i < l; i++) {
    this->array[i] = a[i];
  }
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