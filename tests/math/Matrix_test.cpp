#include <gtest/gtest.h>
#include <math/Matrix.hpp>

TEST(MatrixTest, CreateSetGet) {
  Matrix m(2, 3);
  EXPECT_EQ(m.getRows(), 2);
  EXPECT_EQ(m.getCols(), 3);

  // set(row, col, value) test
  m.set(0, 0, 1.0f);
  m.set(0, 1, 2.0f);
  m.set(0, 2, 3.0f);
  m.set(1, 0, 4.0f);
  m.set(1, 1, 5.0f);
  m.set(1, 2, 6.0f);

  // get(row, col) test
  EXPECT_EQ(m.get(0, 0), 1.0f);
  EXPECT_EQ(m.get(0, 1), 2.0f);
  EXPECT_EQ(m.get(0, 2), 3.0f);
  EXPECT_EQ(m.get(1, 0), 4.0f);
  EXPECT_EQ(m.get(1, 1), 5.0f);
  EXPECT_EQ(m.get(1, 2), 6.0f);
}

TEST(MatrixTest, CopyConstructor) {
  Matrix m1(2, 3);
  m1.set(0, 0, 1.0f);
  m1.set(0, 1, 2.0f);
  m1.set(0, 2, 3.0f);
  m1.set(1, 0, 4.0f);
  m1.set(1, 1, 5.0f);
  m1.set(1, 2, 6.0f);

  Matrix m2(m1);
  EXPECT_EQ(m2.get(0, 0), 1.0f);
  EXPECT_EQ(m2.get(0, 1), 2.0f);
  EXPECT_EQ(m2.get(0, 2), 3.0f);
  EXPECT_EQ(m2.get(1, 0), 4.0f);
  EXPECT_EQ(m2.get(1, 1), 5.0f);
  EXPECT_EQ(m2.get(1, 2), 6.0f);
}

TEST(MatrixTest, InitializerListConstructor) {
  Matrix m = {
    {1.0f, 2.0f, 3.0f},
    {4.0f, 5.0f, 6.0f}
  };
  EXPECT_EQ(m.get(0, 0), 1.0f);
  EXPECT_EQ(m.get(0, 1), 2.0f);
  EXPECT_EQ(m.get(0, 2), 3.0f);
  EXPECT_EQ(m.get(1, 0), 4.0f);
  EXPECT_EQ(m.get(1, 1), 5.0f);
  EXPECT_EQ(m.get(1, 2), 6.0f);
}

TEST(MatrixTest, Addition) {
  Matrix m1(2, 3);
  m1.set(0, 0, 1.0f);
  m1.set(0, 1, 2.0f);
  m1.set(0, 2, 3.0f);
  m1.set(1, 0, 4.0f);
  m1.set(1, 1, 5.0f);
  m1.set(1, 2, 6.0f);

  Matrix m2(2, 3);
  m2.set(0, 0, 7.2f);
  m2.set(0, 1, 10.0f);
  m2.set(0, 2, 3.0f);
  m2.set(1, 0, 3.5f);
  m2.set(1, 1, 1.0f);
  m2.set(1, 2, 2.5f);

  Matrix result = m1 + m2;
  EXPECT_EQ(result.get(0, 0), 8.2f);
  EXPECT_EQ(result.get(0, 1), 12.0f);
  EXPECT_EQ(result.get(0, 2), 6.0f);
  EXPECT_EQ(result.get(1, 0), 7.5f);
  EXPECT_EQ(result.get(1, 1), 6.0f);
  EXPECT_EQ(result.get(1, 2), 8.5f);
}

TEST(MatrixTest, Subtraction) {
  Matrix m1(2, 3);
  m1.set(0, 0, 1.0f);
  m1.set(0, 1, 2.0f);
  m1.set(0, 2, 3.0f);
  m1.set(1, 0, 4.0f);
  m1.set(1, 1, 5.0f);
  m1.set(1, 2, 6.0f);

  Matrix m2(2, 3);
  m2.set(0, 0, 7.2f);
  m2.set(0, 1, 10.0f);
  m2.set(0, 2, 3.0f);
  m2.set(1, 0, 3.5f);
  m2.set(1, 1, 1.0f);
  m2.set(1, 2, 2.5f);

  Matrix result = m1 - m2;
  EXPECT_EQ(result.get(0, 0), -6.2f);
  EXPECT_EQ(result.get(0, 1), -8.0f);
  EXPECT_EQ(result.get(0, 2), 0.0f);
  EXPECT_EQ(result.get(1, 0), 0.5f);
  EXPECT_EQ(result.get(1, 1), 4.0f);
  EXPECT_EQ(result.get(1, 2), 3.5f);
}

TEST(MatrixTest, MultiplicationByScalar) {
  Matrix m(3, 4);
  m.set(0, 0, 1.0f);
  m.set(0, 1, 2.0f);
  m.set(0, 2, 3.0f);
  m.set(0, 3, 4.0f);
  m.set(1, 0, 5.0f);
  m.set(1, 1, 6.0f);
  m.set(1, 2, 7.0f);
  m.set(1, 3, 8.0f);
  m.set(2, 0, 9.0f);
  m.set(2, 1, 10.0f);
  m.set(2, 2, 11.0f);
  m.set(2, 3, 12.0f);
  
  Matrix result = m * 2.0f;
  EXPECT_EQ(result.get(0, 0), 2.0f);
  EXPECT_EQ(result.get(0, 1), 4.0f);
  EXPECT_EQ(result.get(0, 2), 6.0f);
  EXPECT_EQ(result.get(0, 3), 8.0f);
  EXPECT_EQ(result.get(1, 0), 10.0f);
  EXPECT_EQ(result.get(1, 1), 12.0f);
  EXPECT_EQ(result.get(1, 2), 14.0f);
  EXPECT_EQ(result.get(1, 3), 16.0f);
  EXPECT_EQ(result.get(2, 0), 18.0f);
  EXPECT_EQ(result.get(2, 1), 20.0f);
  EXPECT_EQ(result.get(2, 2), 22.0f);
  EXPECT_EQ(result.get(2, 3), 24.0f);
}

TEST(MatrixTest, DivisionByScalar) {
  Matrix m(3, 4);
  m.set(0, 0, 1.0f);
  m.set(0, 1, 2.0f);
  m.set(0, 2, 3.0f);
  m.set(0, 3, 4.0f);
  m.set(1, 0, 5.0f);
  m.set(1, 1, 6.0f);
  m.set(1, 2, 7.0f);
  m.set(1, 3, 8.0f);
  m.set(2, 0, 9.0f);
  m.set(2, 1, 10.0f);
  m.set(2, 2, 11.0f);
  m.set(2, 3, 12.0f);
  
  float scalar = 2.0f;
  Matrix result = m / scalar;
  
  EXPECT_EQ(result.get(0, 0), 0.5f);
  EXPECT_EQ(result.get(0, 1), 1.0f);
  EXPECT_EQ(result.get(0, 2), 1.5f);
  EXPECT_EQ(result.get(0, 3), 2.0f);
  EXPECT_EQ(result.get(1, 0), 2.5f);
  EXPECT_EQ(result.get(1, 1), 3.0f);
  EXPECT_EQ(result.get(1, 2), 3.5f);
  EXPECT_EQ(result.get(1, 3), 4.0f);
  EXPECT_EQ(result.get(2, 0), 4.5f);
  EXPECT_EQ(result.get(2, 1), 5.0f);
  EXPECT_EQ(result.get(2, 2), 5.5f);
  EXPECT_EQ(result.get(2, 3), 6.0f);
}

TEST(MatrixTest, MultiplicationByMatrix) {
  Matrix m1(2, 3);
  m1.set(0, 0, 1.0f);
  m1.set(0, 1, 2.0f);
  m1.set(0, 2, 3.0f);
  m1.set(1, 0, 4.0f);
  m1.set(1, 1, 5.0f);
  m1.set(1, 2, 6.0f);

  Matrix m2(3, 2);
  m2.set(0, 0, 7.0f);
  m2.set(0, 1, 8.0f);
  m2.set(1, 0, 9.0f);
  m2.set(1, 1, 10.0f);
  m2.set(2, 0, 11.0f);
  m2.set(2, 1, 12.0f);

  Matrix result = m1 * m2;
  EXPECT_EQ(result.getRows(), 2);
  EXPECT_EQ(result.getCols(), 2);
  EXPECT_EQ(result.get(0, 0), 58.0f);
  EXPECT_EQ(result.get(0, 1), 64.0f);
  EXPECT_EQ(result.get(1, 0), 139.0f);
  EXPECT_EQ(result.get(1, 1), 154.0f);
}