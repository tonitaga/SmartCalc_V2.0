#ifndef SIMPLECONTROLLER_H
#define SIMPLECONTROLLER_H

#include "simplemodel.h"

namespace s21 {
class SimpleController {
 private:
  SimpleModel *simple_model;

 public:
  SimpleController(SimpleModel *model) : simple_model(model) {}

  double Add(double value1, double value2) {
    simple_model->Add(value1, value2);
    return simple_model->GetData();
  }

  double Sub(double value1, double value2) {
    simple_model->Sub(value1, value2);
    return simple_model->GetData();
  }

  double Multiply(double value1, double value2) {
    simple_model->Multiply(value1, value2);
    return simple_model->GetData();
  }

  double Divide(double value1, double value2) {
    simple_model->Divide(value1, value2);
    return simple_model->GetData();
  }

  double Percent(double value) {
    simple_model->Percent(value);
    return simple_model->GetData();
  }

  double Sqrting(double value) {
    simple_model->Sqrting(value);
    return simple_model->GetData();
  }

  double Square(double value) {
    simple_model->Square(value);
    return simple_model->GetData();
  }

  double DivideOneToValue(double value) {
    simple_model->DivideOneToValue(value);
    return simple_model->GetData();
  }

  double ChangeSign(double value) {
    simple_model->ChangeSign(value);
    return simple_model->GetData();
  }

  void Reset() { simple_model->Reset(); }
};
}  // namespace s21

#endif  // SIMPLECONTROLLER_H
