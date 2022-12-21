#ifndef SIMPLEMODEL_H
#define SIMPLEMODEL_H

#include <cmath>

namespace s21 {
class SimpleModel {
 private:
  double data;

 public:
  SimpleModel() : data(0.0) {}

  void Add(double value1, double value2) { data = value1 + value2; }
  void Sub(double value1, double value2) { data = value1 - value2; }
  void Multiply(double value1, double value2) { data = value1 * value2; }
  void Divide(double value1, double value2) { data = value1 / value2; }
  void Percent(double value) { data = value / 100; }
  void Sqrting(double value) { data = sqrt(value); }
  void Square(double value) { data = pow(value, 2); }
  void OneDivideValue(double value) { data = 1 / value; }
  void Reset() { data = 0.0; }
  void ChangeSign(double value) { data = -value; }
  void DivideOneToValue(double value) { data = 1 / value; }
  double GetData() { return data; }
};
}  // namespace s21

#endif  // SIMPLEMODEL_H
