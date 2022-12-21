#ifndef DEPOSITMODEL_H
#define DEPOSITMODEL_H

#include <QDebug>
#include <iostream>
#include <vector>

namespace s21 {
class DepositModel {
 private:
  std::vector<double> added_money;
  std::vector<double> balance;
  std::vector<double> percent_money;

  double total_money;
  double tax;
  double total_percent_money;

  int current_month;

 public:
  explicit DepositModel()
      : total_money(0.0), tax(0.0), total_percent_money(0.0) {}

  void DepositStart(double amount_money, int period, double percent, int type,
                    int periodically) {
    for (int i = 1; i != period + 1; ++i) {
      double added = 0.0;
      if (type != 0) {
        if (i % periodically == 0) {
          added = CalculatePercentAddingMonthly(amount_money, percent,
                                                periodically);
          amount_money += added;
          total_percent_money += added;
          balance.push_back(amount_money);
          added_money.push_back(added);
          percent_money.push_back(added);
        }
      } else {
        if (i % periodically == 0) {
          double percent_add = CalculatePercentAddingMonthly(
              amount_money, percent, periodically);
          balance.push_back(amount_money);
          total_percent_money += percent_add;
          added_money.push_back(0.0);
          percent_money.push_back(percent_add);
        }
      }
    }
    CountTax();
    total_money = amount_money;
    //            for (int i = 0; i != period; ++i) {
    //                double added = 0.0;
    //                if (type != 0) {
    //                    added = CalculatePercentAddingMonthly(amount_money,
    //                    percent); amount_money += added; total_percent_money
    //                    += added; balance.push_back(amount_money);
    //                    added_money.push_back(added);
    //                    percent_money.push_back(added);
    //                } else {
    //                    double percent_add =
    //                    CalculatePercentAddingMonthly(amount_money, percent);
    //                    balance.push_back(amount_money);
    //                    total_percent_money += percent_add;
    //                    added_money.push_back(0.0);
    //                    percent_money.push_back(percent_add);
    //                }
    //            }
    //            CountTax();
    //            total_money = amount_money;
  }

  double GetTax() { return tax; }
  double GetTotalPercentMoney() { return total_percent_money; }
  double GetTotalMoney() { return total_money; }

  std::vector<double> GetAddedMoneyV() { return added_money; }
  std::vector<double> GetBalanceV() { return balance; }
  std::vector<double> GetPercentMoneyV() { return percent_money; }

  void Reset() {
    current_month = 0;
    total_money = 0.0;
    tax = 0.0;
    total_percent_money = 0.0;
    added_money.clear();
    balance.clear();
    percent_money.clear();
  }

 private:
  double CalculatePercentAddingMonthly(double current_money, double percent,
                                       int periodicaly) {
    double result = current_money * (percent / (1200 / periodicaly));
    return result;
  }

  void CountTax() {
    double untaxed_money = 1e6 * 0.075;
    if (total_percent_money >= untaxed_money)
      tax = (total_percent_money - untaxed_money) * 0.13;
  }
};
}  // namespace s21

#endif  // DEPOSITMODEL_H
