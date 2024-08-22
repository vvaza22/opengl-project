#ifndef _FloatArray_
#define _FloatArray_

class FloatArray {
public:
  FloatArray(int length, float* array);
  ~FloatArray();

  int Length() const;
  const float* Ptr() const;
private:
  int length;
  float* array;
};

#endif