#ifndef CREDITMODEL_H
#define CREDITMODEL_H

#include <QDebug>
#include <cmath>
#include <iostream>
#include <vector>

namespace s21 {
class CreditModel {
 private:
  double total_payment;
  double overpayment;
  std::vector<double> monthly_payment;
  std::vector<double> percent_payment;
  std::vector<double> balance;

  int current_month;

 public:
  CreditModel() : total_payment(0.0), overpayment(0.0), current_month(0) {}

  void CreditStart(double amount_money, int period, double percent, int type) {
    double total_money = amount_money;
    for (int i = 0; i != period; ++i) {
      double payment =
          CaclulateMonthlyPayment(total_money, period, percent, type);
      monthly_payment.push_back(payment);
      double percent_money =
          amount_money * (1 + (percent / 1200)) - amount_money;
      percent_payment.push_back(percent_money);
      double balance_money = amount_money - payment + percent_money;
      balance.push_back(balance_money);
      amount_money = balance_money;
    }
    CaclulateOverpaymentTotalPayment(total_money);
  }

  double GetTotalPayment() { return total_payment; }
  double GetOverpayment() { return overpayment; }
  std::vector<double> GetMonthlyPayment() { return monthly_payment; }
  std::vector<double> GetPercentPayment() { return percent_payment; }
  std::vector<double> GetBalance() { return balance; }

  void Reset() {
    total_payment = 0.0;
    overpayment = 0.0;
    current_month = 0;
    monthly_payment.clear();
    percent_payment.clear();
    balance.clear();
  }

 private:
  double CaclulateMonthlyPayment(double amount_money, int period,
                                 double percent, int type) {
    double result = 0.0;
    if (type == 0) {
      double monthly_percent = percent / (12 * 100.0);
      result = amount_money * monthly_percent;
      double tmp = 1 - pow(1 + monthly_percent, -period);
      result /= tmp;
    } else {
      double main_payment = amount_money / period;
      result = main_payment + ((amount_money - main_payment * current_month) *
                               (percent / 100) / 12);
      current_month++;
    }
    return result;
  }

  void CaclulateOverpaymentTotalPayment(double amount_money) {
    for (auto i : monthly_payment) total_payment += i;
    overpayment = total_payment - amount_money;
  }
};
}  // namespace s21

#endif  // CREDITMODEL_H
