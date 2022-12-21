#ifndef DEPOSITCONTROLLER_H
#define DEPOSITCONTROLLER_H

#include "depositmodel.h"

namespace s21 {
class DepositController {
 private:
  DepositModel *model;

 public:
  explicit DepositController() {}
  DepositController(DepositModel *depositmodel) : model(depositmodel) {}

  void DepositStart(double amount_money, int period, double percent, int type,
                    int periodically) {
    model->DepositStart(amount_money, period, percent, type, periodically);
  }

  double GetTax() { return model->GetTax(); }
  double GetTotalPercentMoney() { return model->GetTotalPercentMoney(); }
  double GetTotalMoney() { return model->GetTotalMoney(); }

  std::vector<double> GetAddedMoneyV() { return model->GetAddedMoneyV(); }
  std::vector<double> GetBalanceV() { return model->GetBalanceV(); }
  std::vector<double> GetPercentMoneyV() { return model->GetPercentMoneyV(); }

  void Reset() { model->Reset(); }
};
}  // namespace s21

#endif  // DEPOSITCONTROLLER_H
