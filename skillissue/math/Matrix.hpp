#ifndef _Matrix_
#define _Matrix_

#include <vector>
#include <initializer_list>

class Matrix {
public:
  Matrix(int r, int c);
  Matrix(const Matrix& m);
  Matrix(std::initializer_list<std::initializer_list<float>> list);

  Matrix operator+(const Matrix &m) const;
  Matrix operator-(const Matrix &m) const;
  Matrix operator*(const Matrix &m) const;
  Matrix operator*(float scalar) const;
  Matrix operator/(float scalar) const;

  void print() const;
  int getRows() const;
  int getCols() const;
  const float* getData() const;

  void set(int row, int col, float value);
  float get(int row, int col) const;

private:
  int rows;
  int cols;
  std::vector<float> data;
};

#endif