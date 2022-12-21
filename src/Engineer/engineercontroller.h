#ifndef SRC_ENGINEERCONTROLLER_H
#define SRC_ENGINEERCONTROLLER_H

#include "engineermodel.h"

namespace s21 {
class EngineerController {
 private:
  EngineerModel *model;

 public:
  explicit EngineerController(EngineerModel *engineermodel)
      : model(engineermodel) {}
  ~EngineerController() = default;

  double Calculate(const std::string &expression, double x_value) {
    model->SetExpression(expression);
    model->SetX(x_value);
    model->Calculate();
    return model->GetAnswer();
  }

  void Reset() { model->Reset(); }

  double Percent(double value = 0.0) {
    model->Percent(value);
    return model->GetAnswer();
  }
};
}  // namespace s21

#endif  // !SRC_ENGINEERCONTROLLER_H
