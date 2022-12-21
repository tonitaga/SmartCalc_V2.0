#ifndef CREDITCONTROLLER_H
#define CREDITCONTROLLER_H

#include "creditmodel.h"

namespace s21 {
class CreditController {
 private:
  CreditModel *model;

 public:
  CreditController() {}
  CreditController(CreditModel *creditmodel = nullptr) : model(creditmodel) {}

  void CreditStart(double amount_money, int period, double percent, int type) {
    model->CreditStart(amount_money, period, percent, type);
  }

  double GetTotalPayment() { return model->GetTotalPayment(); }
  double GetOverpayment() { return model->GetOverpayment(); }
  std::vector<double> GetMonthlyPayment() { return model->GetMonthlyPayment(); }
  std::vector<double> GetPercentPayment() { return model->GetPercentPayment(); }
  std::vector<double> GetBalance() { return model->GetBalance(); }

  void Reset() { model->Reset(); }
};
}  // namespace s21

#endif  // CREDITCONTROLLER_H
