#include "Engineer/engineercontroller.h"
#include "gtest/gtest.h"

s21::EngineerModel model;
s21::EngineerController controller(&model);

TEST(Test1, calc_pluc) {
  double answer = 5;
  double result = controller.Calculate("1.5+3.5", 0);
  ASSERT_EQ(answer, result);
}

TEST(Test2, calc_minus) {
  double answer = -2;
  double result = controller.Calculate("1.5-3.5", 0);
  ASSERT_EQ(answer, result);
}

TEST(Test3, calc_multiply) {
  double answer = 6;
  double result = controller.Calculate("1.5*4", 0);
  ASSERT_EQ(answer, result);
}

TEST(Test4, calc_division) {
  double answer = 10;
  double result = controller.Calculate("90/9.0", 0);
  ASSERT_EQ(answer, result);
}

TEST(Test5, calc_mod) {
  double answer = 0;
  double result = controller.Calculate("10mod5", 0);
  ASSERT_EQ(answer, result);
}

TEST(Test6, calc_brackets) {
  double answer = 0;
  double result = controller.Calculate("1-(1-(1-1))", 0);
  ASSERT_EQ(answer, result);
}

TEST(Test7, calc_pow) {
  double answer = 1024;
  double result = controller.Calculate("2^10", 0);
  ASSERT_EQ(answer, result);
}

TEST(Test8, calc_sin) {
  double answer = sin(1);
  double result = controller.Calculate("sin(1)", 0);
  ASSERT_EQ(answer, result);
}

TEST(Test9, calc_sin) {
  double answer = cos(1);
  double result = controller.Calculate("cos(1)", 0);
  ASSERT_EQ(answer, result);
}

TEST(Test10, calc_tan) {
  double answer = tan(0);
  double result = controller.Calculate("tan(0)", 0);
  ASSERT_EQ(answer, result);
}

TEST(Test11, calc_asin) {
  double answer = asin(0.34);
  double result = controller.Calculate("asin(0.34)", 0);
  ASSERT_EQ(answer, result);
}

TEST(Test12, calc_acos) {
  double answer = acos(0.34);
  double result = controller.Calculate("acos(0.34)", 0);
  ASSERT_EQ(answer, result);
}

TEST(Test13, calc_atan) {
  double answer = atan(-0.669);
  double result = controller.Calculate("atan(-0.669)", 0);
  ASSERT_EQ(answer, result);
}

TEST(Test14, calc_ln) {
  double answer = log(2.718281828904590);
  double result = controller.Calculate("ln(2.718281828904590)", 0);
  ASSERT_EQ(answer, result);
}

TEST(Test15, calc_log) {
  double answer = log10(100);
  double result = controller.Calculate("log(100)", 0);
  ASSERT_EQ(answer, result);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}