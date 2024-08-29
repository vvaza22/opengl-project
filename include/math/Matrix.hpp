#ifndef _Matrix_
#define _Matrix_

class Matrix {
public:
  Matrix(int r, int c);
  Matrix(const Matrix& m);
  ~Matrix();

  Matrix operator+(const Matrix &m) const;
  Matrix operator-(const Matrix &m) const;
  Matrix operator*(const Matrix &m) const;
  Matrix operator*(float scalar) const;
  Matrix operator/(float scalar) const;

  void print() const;
  int getRows() const;
  int getCols() const;

  void set(int index, float value);
  void set(int row, int col, float value);
  float get(int index) const;
  float get(int row, int col) const;

protected:
  int rows;
  int cols;
  float* data;
};

#endif