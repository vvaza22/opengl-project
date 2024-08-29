#include <math/Matrix.hpp>
#include <cassert>
#include <stdexcept>
#include <iostream>

Matrix::Matrix(int r, int c) : rows(r), cols(c), data(r*c) {}

Matrix::Matrix(const Matrix& m) : rows(m.getRows()), cols(m.getCols()), data(m.data) {}

Matrix::Matrix(std::initializer_list<std::initializer_list<float>> list) {
  this->rows = (int)list.size();
  assert(this->rows > 0);

  this->cols = (int)list.begin()->size();
  this->data.resize(this->rows * this->cols);

  int i = 0;
  for(auto row : list) {
    assert((int)row.size() == this->cols);
    for(auto element : row) {
      this->data[i++] = element;
    }
  }
}

Matrix Matrix::operator+(const Matrix &m) const {
  assert(this->rows == m.getRows() && this->cols == m.getCols());

  Matrix result(this->rows, this->cols);
  for(int i = 0; i < this->rows * this->cols; i++) {
    result.set(i, this->get(i) + m.get(i));
  }

	return result;
}

Matrix Matrix::operator-(const Matrix &m) const {
  assert(this->rows == m.getRows() && this->cols == m.getCols());

  Matrix result(this->rows, this->cols);
  for(int i = 0; i < this->rows * this->cols; i++) {
    result.set(i, this->get(i) - m.get(i));
  }

	return result;
}

Matrix Matrix::operator*(const Matrix &m) const {
  assert(this->cols == m.getRows());

  Matrix result(this->rows, m.getCols());

  // For each row in this matrix
  for(int row = 0; row < this->getRows(); row++) {

    // For each column in the other matrix
    for(int col = 0; col < m.getCols(); col++) {

      // Calculate the scalar product
      float value = 0;
      for(int element = 0; element < m.getRows(); element++) {
        value += this->get(row, element) * m.get(element, col);
      }
      result.set(row, col, value);

    }

  }

	return result;
}

Matrix Matrix::operator*(float scalar) const {
  Matrix result(this->rows, this->cols);

  for(int i = 0; i < this->rows * this->cols; i++) {
    result.set(i, this->get(i) * scalar);
  }

	return result;
}

Matrix Matrix::operator/(float scalar) const {
  Matrix result(this->rows, this->cols);

  for(int i = 0; i < this->rows * this->cols; i++) {
    result.set(i, this->get(i) / scalar);
  }

	return result;
}

void Matrix::set(int index, float value) {
    if (index < 0 || index >= this->rows * this->cols) {
        throw std::out_of_range("Index out of range");
    }
    data[index] = value;
}

void Matrix::set(int row, int col, float value) {
    if (row < 0 || row >= this->rows || col < 0 || col >= this->cols) {
        throw std::out_of_range("Row or column out of range");
    }
    data[row * this->cols + col] = value;
}

float Matrix::get(int index) const {
    if (index < 0 || index >= this->rows * this->cols) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

float Matrix::get(int row, int col) const {
    if (row < 0 || row >= this->rows || col < 0 || col >= this->cols) {
        throw std::out_of_range("Row or column out of range");
    }
    return data[row * this->cols + col];
}

void Matrix::print() const {
  for (int i = 0; i < this->rows; i++) {
    for (int j = 0; j < this->cols; j++) {
      std::cout << this->data[i * this->cols + j] << " ";
    }
    std::cout << std::endl;
  }
}

int Matrix::getRows() const {
  return this->rows;
}

int Matrix::getCols() const {
  return this->cols;
}

const float* Matrix::getData() const {
  return this->data.data();
}