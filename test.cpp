#include <gtest/gtest.h>

#include "my_matrix.h"

double data_massive_1[6] = {1, 2, 3, 4, 5, 6};
double data_massive_2[6] = {1.0000001, 2, 3, 4, 5, 6};
double data_massive_3[1] = {5.25};
double data_massive_4[2] = {5.23, -2.56};
double data_massive_5[6] = {102.455, -455.463, 563.23, 4517.89, 0.398741, 0};
double data_massive_6[9] = {0.0, 0.0, 0.0, 0.0, 0.0,
                            0.0, 0.0, 0.0, 0.0};  // zero
double data_massive_7[9] = {1.0, 0.0, 0.0, 0.0, 1.0,
                            0.0, 0.0, 0.0, 1.0};  // identity
double data_massive_8[9] = {3.5,    -2.0034, 4.007,  5.0067,   4.77,
                            3.0078, 2.4,     -4.567, -5.234567};
double data_massive_9[9] = {25.256, -4.2147,   457.698, -4,   895.962,
                            63.56,  -78.95478, 8.9,     0.245};
double data_massive_10[16] = {2.5,  -4.5, 4.7, -9.5, 0.5,  6.5,  -7.5, 8.5,
                              0.23, 5.5,  1.5, 2.5,  14.5, -9.5, 5.5,  0.0};
double data_massive_11[16] = {-2.5,  4.5,  -4.7, 9.5,  -0.5,  -6.5, +7.5, -8.5,
                              -0.23, -5.5, -1.5, -2.5, -14.5, 9.5,  -5.5, 0.0};

TEST(Create_matrix, default_constructor) {
  MyMatrix m1;
  ASSERT_EQ(m1.get_rows(), 0);
  ASSERT_EQ(m1.get_cols(), 0);
  ASSERT_EQ(m1.get_matrix(), nullptr);
}

TEST(Create_matrix, construstor_with_parameters) {
  MyMatrix m1(3, 4);
  ASSERT_EQ(m1.get_rows(), 3);
  ASSERT_EQ(m1.get_cols(), 4);
  ASSERT_NE(m1.get_matrix(), nullptr);
}

TEST(Create_matrix, construstor_with_parameters_exception) {
  ASSERT_ANY_THROW(MyMatrix m1(-3, 4));
}

TEST(Create_matrix, construstor_through_copy) {
  MyMatrix m1(3, 4);
  MyMatrix m2(m1);
  ASSERT_EQ(m2.get_rows(), 3);
  ASSERT_EQ(m2.get_cols(), 4);
  ASSERT_NE(m2.get_matrix(), nullptr);
}

TEST(Create_matrix, construstor_through_move) {
  MyMatrix m1(3, 4);
  MyMatrix m2(std::move(m1));
  ASSERT_EQ(m2.get_rows(), 3);
  ASSERT_EQ(m2.get_cols(), 4);
  ASSERT_NE(m2.get_matrix(), nullptr);
  ASSERT_EQ(m1.get_rows(), 0);
  ASSERT_EQ(m1.get_cols(), 0);
  ASSERT_EQ(m1.get_matrix(), nullptr);
}

TEST(Compare_matrixes, compare_matrixes_true) {
  MyMatrix m1(2, 3, data_massive_1);
  MyMatrix m2(2, 3, data_massive_1);
  ASSERT_TRUE(m1.EqualMatrix(m2));

  MyMatrix m3(1, 1, data_massive_3);
  MyMatrix m4(1, 1, data_massive_3);
  ASSERT_TRUE(m3.EqualMatrix(m4));

  MyMatrix m5(5, 2);
  MyMatrix m6(5, 2);
  ASSERT_TRUE(m5.EqualMatrix(m6));
}

TEST(Compare_matrixes, compare_matrixes_true_overload) {
  MyMatrix m1(2, 3, data_massive_1);
  MyMatrix m2(2, 3, data_massive_1);
  ASSERT_TRUE(m1 == m2);

  MyMatrix m3(1, 1, data_massive_3);
  MyMatrix m4(1, 1, data_massive_3);
  ASSERT_TRUE(m3 == m4);

  MyMatrix m5(5, 2);
  MyMatrix m6(5, 2);
  ASSERT_TRUE(m5 == m6);
}

TEST(Compare_matrixes, compare_matrixes_false) {
  MyMatrix m1(2, 3, data_massive_1);
  MyMatrix m2(2, 3, data_massive_2);
  ASSERT_FALSE(m1.EqualMatrix(m2));

  MyMatrix m3(1, 1, data_massive_3);
  MyMatrix m4(1, 5, data_massive_3);
  ASSERT_FALSE(m3.EqualMatrix(m4));

  MyMatrix m5(1, 3);
  MyMatrix m6(1, 2);
  ASSERT_FALSE(m5.EqualMatrix(m6));
}

TEST(Sum_Sub_matrixes, sum_matrixes) {
  MyMatrix m1(4, 4, data_massive_10);
  MyMatrix m2(4, 4, data_massive_11);
  m2.SumMatrix(m1);
  double original_m2[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  ASSERT_EQ(m2.get_rows(), 4);
  ASSERT_EQ(m2.get_cols(), 4);
  ASSERT_NE(m2.get_matrix(), nullptr);
  for (int i = 0; i < m2.get_rows(); i++) {
    for (int j = 0; j < m2.get_cols(); j++) {
      ASSERT_DOUBLE_EQ(m2(i, j), original_m2[i * m2.get_cols() + j]);
    }
  }

  MyMatrix m3(3, 2, data_massive_1);
  MyMatrix m4(3, 2, data_massive_1);
  m3.SumMatrix(m4);
  double original_m3[6] = {2, 4, 6, 8, 10, 12};
  ASSERT_EQ(m3.get_rows(), 3);
  ASSERT_EQ(m3.get_cols(), 2);
  ASSERT_NE(m3.get_matrix(), nullptr);
  for (int i = 0; i < m3.get_rows(); i++) {
    for (int j = 0; j < m3.get_cols(); j++) {
      ASSERT_DOUBLE_EQ(m3(i, j), original_m3[i * m3.get_cols() + j]);
    }
  }
}

TEST(Sum_Sub_matrixes, sum_matrixes_exception) {
  MyMatrix m1(4, 5, data_massive_10);
  MyMatrix m2(3, 4, data_massive_11);
  ASSERT_ANY_THROW(m2.SumMatrix(m1));
}

TEST(Sum_Sub_matrixes, sum_matrixes_overload) {
  MyMatrix m1(4, 4, data_massive_10);
  MyMatrix m2(4, 4, data_massive_11);
  MyMatrix Result = m2 + m1;
  double original_Result[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  ASSERT_EQ(Result.get_rows(), 4);
  ASSERT_EQ(Result.get_cols(), 4);
  ASSERT_NE(Result.get_matrix(), nullptr);
  for (int i = 0; i < Result.get_rows(); i++) {
    for (int j = 0; j < Result.get_cols(); j++) {
      ASSERT_DOUBLE_EQ(Result(i, j),
                       original_Result[i * Result.get_cols() + j]);
    }
  }

  MyMatrix m3(3, 2, data_massive_1);
  MyMatrix m4(3, 2, data_massive_1);
  m3 += m4;
  double original_m3[6] = {2, 4, 6, 8, 10, 12};
  ASSERT_EQ(m3.get_rows(), 3);
  ASSERT_EQ(m3.get_cols(), 2);
  ASSERT_NE(m3.get_matrix(), nullptr);
  for (int i = 0; i < m3.get_rows(); i++) {
    for (int j = 0; j < m3.get_cols(); j++) {
      ASSERT_DOUBLE_EQ(m3(i, j), original_m3[i * m3.get_cols() + j]);
    }
  }
}

TEST(Sum_Sub_matrixes, sub_matrixes) {
  MyMatrix m1(3, 3, data_massive_7);
  MyMatrix m2(3, 3, data_massive_8);
  m2.SubMatrix(m1);
  double original_m2[9] = {2.5,    -2.0034, 4.007,  5.0067,   3.77,
                           3.0078, 2.4,     -4.567, -6.234567};
  ASSERT_EQ(m2.get_rows(), 3);
  ASSERT_EQ(m2.get_cols(), 3);
  ASSERT_NE(m2.get_matrix(), nullptr);
  for (int i = 0; i < m2.get_rows(); i++) {
    for (int j = 0; j < m2.get_cols(); j++) {
      ASSERT_DOUBLE_EQ(m2(i, j), original_m2[i * m2.get_cols() + j]);
    }
  }
}

TEST(Sum_Sub_matrixes, sub_matrixes_exception) {
  MyMatrix m1(4, 5, data_massive_10);
  MyMatrix m2(3, 4, data_massive_11);
  ASSERT_ANY_THROW(m2.SubMatrix(m1));
}

TEST(Sum_Sub_matrixes, sub_matrixes_overload) {
  MyMatrix m1(3, 3, data_massive_7);
  MyMatrix m2(3, 3, data_massive_8);
  MyMatrix Result = m2 - m1;
  double original_Result[9] = {2.5,    -2.0034, 4.007,  5.0067,   3.77,
                               3.0078, 2.4,     -4.567, -6.234567};
  ASSERT_EQ(Result.get_rows(), 3);
  ASSERT_EQ(Result.get_cols(), 3);
  ASSERT_NE(Result.get_matrix(), nullptr);
  for (int i = 0; i < Result.get_rows(); i++) {
    for (int j = 0; j < Result.get_cols(); j++) {
      ASSERT_DOUBLE_EQ(Result(i, j),
                       original_Result[i * Result.get_cols() + j]);
    }
  }

  MyMatrix m3(1, 1, data_massive_3);
  MyMatrix m4(1, 1, data_massive_3);
  m3 -= m4;
  ASSERT_EQ(m3.get_rows(), 1);
  ASSERT_EQ(m3.get_cols(), 1);
  ASSERT_NE(m3.get_matrix(), nullptr);
  ASSERT_DOUBLE_EQ(m3(0, 0), 0);
}

TEST(Mul_both_matrixes, mul_matrixes) {
  MyMatrix m1(3, 2, data_massive_5);
  MyMatrix m2(2, 3, data_massive_1);
  m1.MulMatrix(m2);
  double original_m1[9] = {-1719.397, -2072.405, -2425.413, 18634.79, 23715.91,
                           28797.03,  0.398741,  0.797482,  1.196223};
  ASSERT_EQ(m1.get_rows(), 3);
  ASSERT_EQ(m1.get_cols(), 3);
  ASSERT_NE(m1.get_matrix(), nullptr);
  for (int i = 0; i < m1.get_rows(); i++) {
    for (int j = 0; j < m1.get_cols(); j++) {
      ASSERT_DOUBLE_EQ(m1(i, j), original_m1[i * m1.get_cols() + j]);
    }
  }
}

TEST(Mul_both_matrixes, mul_matrixes_exception) {
  MyMatrix m1(3, 2, data_massive_5);
  MyMatrix m2(2, 1, data_massive_1);
  ASSERT_ANY_THROW(m2.MulMatrix(m1));
}

TEST(Mul_both_matrixes, mul_matrixes_overload) {
  MyMatrix m1(3, 2, data_massive_5);
  MyMatrix m2(2, 3, data_massive_1);
  m1 *= m2;
  double original_m1[9] = {-1719.397, -2072.405, -2425.413, 18634.79, 23715.91,
                           28797.03,  0.398741,  0.797482,  1.196223};
  ASSERT_EQ(m1.get_rows(), 3);
  ASSERT_EQ(m1.get_cols(), 3);
  ASSERT_NE(m1.get_matrix(), nullptr);
  for (int i = 0; i < m1.get_rows(); i++) {
    for (int j = 0; j < m1.get_cols(); j++) {
      ASSERT_DOUBLE_EQ(m1(i, j), original_m1[i * m1.get_cols() + j]);
    }
  }

  MyMatrix m3(3, 3, data_massive_8);
  MyMatrix m4(3, 3, data_massive_9);
  MyMatrix Result = m3 * m4;
  double original_Result[9] = {-219.962203, -1774.059421, 1475.588611,
                               -130.110972, 4279.406422,  2595.474688,
                               492.176486,  -4148.561380, 806.914211};
  ASSERT_EQ(Result.get_rows(), 3);
  ASSERT_EQ(Result.get_cols(), 3);
  ASSERT_NE(Result.get_matrix(), nullptr);
  for (int i = 0; i < Result.get_rows(); i++) {
    for (int j = 0; j < Result.get_cols(); j++) {
      ASSERT_NEAR(Result(i, j), original_Result[i * Result.get_cols() + j],
                  1e-6);
    }
  }
}

TEST(Mul_num_matrix, mul_num_matrix) {
  MyMatrix m1(3, 3, data_massive_7);
  double original_m1[9] = {3.5, 0, 0, 0, 3.5, 0, 0, 0, 3.5};
  m1.MulNumber(3.5);
  ASSERT_EQ(m1.get_rows(), 3);
  ASSERT_EQ(m1.get_cols(), 3);
  ASSERT_NE(m1.get_matrix(), nullptr);
  for (int i = 0; i < m1.get_rows(); i++) {
    for (int j = 0; j < m1.get_cols(); j++) {
      ASSERT_DOUBLE_EQ(m1(i, j), original_m1[i * m1.get_cols() + j]);
    }
  }

  MyMatrix m2(3, 3, data_massive_7);
  double original_m2[9] = {-2.57, 0, 0, 0, -2.57, 0, 0, 0, -2.57};
  m2.MulNumber(-2.57);
  ASSERT_EQ(m2.get_rows(), 3);
  ASSERT_EQ(m2.get_cols(), 3);
  ASSERT_NE(m2.get_matrix(), nullptr);
  for (int i = 0; i < m2.get_rows(); i++) {
    for (int j = 0; j < m2.get_cols(); j++) {
      ASSERT_DOUBLE_EQ(m2(i, j), original_m2[i * m2.get_cols() + j]);
    }
  }
}

TEST(Mul_num_matrix, mul_num_matrix_overload) {
  MyMatrix m1(3, 3, data_massive_7);
  double original_m1[9] = {3.5, 0, 0, 0, 3.5, 0, 0, 0, 3.5};
  m1 *= 3.5;
  ASSERT_EQ(m1.get_rows(), 3);
  ASSERT_EQ(m1.get_cols(), 3);
  ASSERT_NE(m1.get_matrix(), nullptr);
  for (int i = 0; i < m1.get_rows(); i++) {
    for (int j = 0; j < m1.get_cols(); j++) {
      ASSERT_DOUBLE_EQ(m1(i, j), original_m1[i * m1.get_cols() + j]);
    }
  }

  MyMatrix m3(3, 3, data_massive_7);
  double original_Result_1[9] = {3.5, 0, 0, 0, 3.5, 0, 0, 0, 3.5};
  MyMatrix Result_1 = m3 * 3.5;
  ASSERT_EQ(Result_1.get_rows(), 3);
  ASSERT_EQ(Result_1.get_cols(), 3);
  ASSERT_NE(Result_1.get_matrix(), nullptr);
  for (int i = 0; i < Result_1.get_rows(); i++) {
    for (int j = 0; j < Result_1.get_cols(); j++) {
      ASSERT_DOUBLE_EQ(Result_1(i, j),
                       original_Result_1[i * Result_1.get_cols() + j]);
    }
  }

  MyMatrix m4(3, 3, data_massive_7);
  double original_Result_2[9] = {-2.57, 0, 0, 0, -2.57, 0, 0, 0, -2.57};
  MyMatrix Result_2 = -2.57 * m4;
  ASSERT_EQ(Result_2.get_rows(), 3);
  ASSERT_EQ(Result_2.get_cols(), 3);
  ASSERT_NE(Result_2.get_matrix(), nullptr);
  for (int i = 0; i < Result_2.get_rows(); i++) {
    for (int j = 0; j < Result_2.get_cols(); j++) {
      ASSERT_DOUBLE_EQ(Result_2(i, j),
                       original_Result_2[i * Result_2.get_cols() + j]);
    }
  }
}

TEST(Transpose_matrix, transpose_matrix_test) {
  MyMatrix m1(3, 2, data_massive_5);
  MyMatrix Result = m1.Transpose();
  double original_Result[6] = {102.455, 563.23, 0.398741, -455.463, 4517.89, 0};
  ASSERT_EQ(Result.get_rows(), 2);
  ASSERT_EQ(Result.get_cols(), 3);
  ASSERT_NE(Result.get_matrix(), nullptr);
  for (int i = 0; i < Result.get_rows(); i++) {
    for (int j = 0; j < Result.get_cols(); j++) {
      ASSERT_NEAR(Result(i, j), original_Result[i * Result.get_cols() + j],
                  1e-6);
    }
  }
}

TEST(Inverse_matrix, inverse_matrix_test) {
  MyMatrix m1(3, 3, data_massive_8);
  MyMatrix Result_1 = m1.InverseMatrix();
  double original_Result_1[9] = {0.046076,  0.118088,  0.103125,
                                 -0.137121, 0.114605,  -0.039112,
                                 0.140760,  -0.045847, -0.109632};
  ASSERT_EQ(Result_1.get_rows(), 3);
  ASSERT_EQ(Result_1.get_cols(), 3);
  ASSERT_NE(Result_1.get_matrix(), nullptr);
  for (int i = 0; i < Result_1.get_rows(); i++) {
    for (int j = 0; j < Result_1.get_cols(); j++) {
      ASSERT_NEAR(Result_1(i, j),
                  original_Result_1[i * Result_1.get_cols() + j], 1e-6);
    }
  }

  MyMatrix m2(4, 4, data_massive_10);
  MyMatrix Result_2 = m2.InverseMatrix();
  double original_Result_2[16] = {0.10776,   0.109029,  0.038789, 0.046011,
                                  0.1045,    0.076287,  0.137723, -0.022832,
                                  -0.103594, -0.155671, 0.135623, 0.021078,
                                  -0.177657, -0.08446,  0.012068, 0.033352};
  ASSERT_EQ(Result_2.get_rows(), 4);
  ASSERT_EQ(Result_2.get_cols(), 4);
  ASSERT_NE(Result_2.get_matrix(), nullptr);
  for (int i = 0; i < Result_2.get_rows(); i++) {
    for (int j = 0; j < Result_2.get_cols(); j++) {
      ASSERT_NEAR(Result_2(i, j),
                  original_Result_2[i * Result_2.get_cols() + j], 1e-6);
    }
  }
}

TEST(Inverse_matrix, inverse_matrix_exception) {
  MyMatrix m1(3, 5, data_massive_8);
  ASSERT_ANY_THROW(MyMatrix Result_1 = m1.InverseMatrix());

  MyMatrix m2(3, 3, data_massive_6);
  ASSERT_ANY_THROW(MyMatrix Result_2 = m2.InverseMatrix());
}

TEST(Setters, set_rows_test) {
  MyMatrix m1(3, 2, data_massive_1);
  m1.set_rows(4);
  ASSERT_EQ(m1.get_rows(), 4);
  ASSERT_EQ(m1.get_cols(), 2);
  ASSERT_NE(m1.get_matrix(), nullptr);

  m1.set_rows(1);
  ASSERT_EQ(m1.get_rows(), 1);
  ASSERT_EQ(m1.get_cols(), 2);
  ASSERT_NE(m1.get_matrix(), nullptr);
}

TEST(Setters, set_rows_test_exception) {
  MyMatrix m1(3, 2, data_massive_1);
  ASSERT_ANY_THROW(m1.set_rows(-4));
}

TEST(Setters, set_cols_test) {
  MyMatrix m1(3, 2, data_massive_1);
  m1.set_cols(4);
  ASSERT_EQ(m1.get_rows(), 3);
  ASSERT_EQ(m1.get_cols(), 4);
  ASSERT_NE(m1.get_matrix(), nullptr);

  m1.set_cols(1);
  ASSERT_EQ(m1.get_rows(), 3);
  ASSERT_EQ(m1.get_cols(), 1);
  ASSERT_NE(m1.get_matrix(), nullptr);
}

TEST(Setters, set_cols_test_exception) {
  MyMatrix m1(3, 2, data_massive_1);
  ASSERT_ANY_THROW(m1.set_cols(-5));
}

TEST(Overload_functions_other, operator_eq_test) {
  MyMatrix m1(3, 2, data_massive_1);
  MyMatrix m2(1, 2, data_massive_4);
  m1 = m2;
  ASSERT_EQ(m1.get_rows(), 1);
  ASSERT_EQ(m1.get_cols(), 2);
  ASSERT_NE(m1.get_matrix(), nullptr);
  for (int i = 0; i < m1.get_rows(); i++) {
    for (int j = 0; j < m1.get_cols(); j++) {
      ASSERT_NEAR(m1(i, j), data_massive_4[i * m1.get_cols() + j], 1e-6);
    }
  }
}

TEST(Overload_functions_other, operator_index_exception) {
  MyMatrix m1(3, 2, data_massive_1);
  ASSERT_ANY_THROW(m1(-2, 1));
  ASSERT_ANY_THROW(m1(3, 1));
}

int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
