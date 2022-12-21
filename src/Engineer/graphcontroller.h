#ifndef CPP3_SMARTCALC_V2_0_GRAPHCONTROLLER_H
#define CPP3_SMARTCALC_V2_0_GRAPHCONTROLLER_H

#include "engineercontroller.h"

namespace s21 {
class GraphController {
 private:
  EngineerModel *model;

 public:
  GraphController(EngineerModel *engineermodel) : model(engineermodel) {}
  void CaclulateGraph(const std::string &expression, double x_min, double x_max,
                      double step) {
    model->SetExpression(expression);
    model->CalculateGraph(x_min, x_max, step);
  }

  std::vector<double> GetXPoints() { return model->GetXPoints(); }
  std::vector<double> GetYPoints() { return model->GetYPoints(); }

  void Reset() { model->Reset(); }
};
}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_GRAPHCONTROLLER_H
