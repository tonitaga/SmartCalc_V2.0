#ifndef VIEWDEFAULT_H
#define VIEWDEFAULT_H

#include <QMainWindow>

#include "../Engineer/engineercontroller.h"
#include "../Engineer/graphcontroller.h"
#include "creditcontroller.h"
#include "depositcontroller.h"
#include "simplecontroller.h"
#include "theme.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class ViewDefault;
}
QT_END_NAMESPACE

class ViewDefault : public QMainWindow {
  Q_OBJECT

 public:
  ViewDefault(QWidget *parent = nullptr);
  ~ViewDefault();

 private slots:
  void on_digitnumbers_clicked();
  void on_operators_clicked();
  void on_operators_engineer_clicked();
  void on_action_default_triggered();
  void on_action_engineer_triggered();
  void on_action_graph_triggered();
  void on_action_credit_triggered();
  void on_action_deposit_triggered();
  void on_action_about_triggered();
  void on_action_light_triggered();
  void on_action_black_triggered();
  void on_pushButton_clear_all_clicked();
  void on_pushButton_caclulate_clicked();
  void on_pushButton_delete_one_clicked();
  void on_pushButton_save_clear_all_clicked();
  void on_pushButton_percent_clicked();
  void on_pushButton_one_divide_value_clicked();
  void on_pushButton_value_pow_two_clicked();
  void on_pushButton_sqrt_value_clicked();
  void on_pushButton_change_sign_clicked();
  void on_pushButton_point_clicked();

  void on_pushButton_caclulate_credit_clicked();
  void on_pushButton_calcru_clicked();

  void on_pushButton_caclulate_deposit_clicked();
  void on_pushButton_calcru_deposit_clicked();

  void on_comboBox_trigonometry_currentIndexChanged(int index);
  void on_comboBox_functions_currentIndexChanged(int index);
  void on_pushButton_clear_all_e_clicked();
  void on_pushButton_delete_one_e_clicked();
  void on_pushButton_caclulate_e_clicked();
  void on_pushButton_brackets_clicked();
  void on_pushButton_percent_e_clicked();
  void on_pushButton_function_clicked();
  void on_pushButton_x_clicked();
  void on_pushButton_point_e_clicked();

  void on_pushButton_graph_clear_clicked();
  void on_pushButton_addGraph_clicked();
  void on_spinBox_xmin_valueChanged(int arg1);
  void on_spinBox_xmax_valueChanged(int arg1);

 private:
  Ui::ViewDefault *ui;

  s21::SimpleController *d_controller;    // default controller
  s21::SimpleModel *d_model;              // default model
  s21::CreditController *c_controller;    // credit controller
  s21::CreditModel *c_model;              // credit model
  s21::DepositController *dd_controller;  // deposit controller
  s21::DepositModel *dd_model;            // deposit model
  s21::EngineerController *e_controller;  // engineer controller
  s21::EngineerModel *e_model;            // engineer model
  s21::GraphController *g_controller;     // graph controller

  bool is_start;
  bool is_black;
  bool is_function;

  void keyPressEvent(QKeyEvent *);
  void keyPressEventDefault(QKeyEvent *);
  void keyPressEventEngineer(QKeyEvent *);

  /* BLOCK OF PRIVATE FUNCTIONS OF DEFAULT CALCULATOR */

  bool CheckSize(QString);
  QString RemoveLastSimbol(QString);
  void WorkingAboutOperator(QString);

  /* BLOCK OF PRIVATE FUNCTIONS OF ENGINEER CALCULATOR */

  /* BLOCK OF PRIVATE FUNCTIONS OF CREDIT CALCULATOR */

  void MakeTableForCredit();
  void GetCreditDataFromView(int *period, double *amount_money, double *percent,
                             int *type);
  bool CheckCreditDataFromView(int period, double amount_money, double percent);
  void SetCreditDataToView(int type);

  /* BLOCK OF PRIVATE FUNCTIONS OF DEPOSIT CALCULATOR */

  void MakeTableForDeposit(int period, int periodically);
  void GetDepositDataFromView(int *period, double *amount_money,
                              double *percent, int *type, int *periodically);
  bool CheckDepositDataFromView(int period, double amount_money,
                                double percent);
  void SetDepositDataToView();

  /* BLOCK OF PRIVATE FUNCTIONS OF GRAPH CALCULATOR */

  void BuildGraph();

  /* BLOCK OF PRIVATE FUNCTIONS OF CONNECTION SIGNALS */

  void ConnectDefaultCalc();
  void ConnectEngineerCalc();

  /* BLOCK OF PRIVATE FUNCTIONS OF THEME WORK */

  void SetTheme(bool black = true);
  void SetThemeDefault(s21::Theme theme);
  void SetThemeEngineer(s21::Theme theme);
  void SetThemeCredit(s21::Theme theme);
  void SetThemeDeposit(s21::Theme theme);
  void SetThemeGraph(s21::Theme theme);
  void SetThemeGraphWidget(bool black);

  /* BLOCK OF PRIVATE FUNCTIONS OF (DE)ALLOCATING MEMORY */

  void AllocateModelsAndControllers();
  void DeallocateModelsAndControllers();

  void DeleteBackFromStr();
  bool IsOperatorOrOpenBracket(QChar token);
  bool IsOperatorOrOpenBracketOrDigit(QChar token);
  bool IsLetter(QChar token);
  bool IsOperator(QChar token);
  bool IsDigit(QChar token);
  bool OpenBracketsEqualCloseBrackets(QString str);
  bool OpenBracketsGreaterCloseBrackets(QString str);
  bool IsLegalToBuildGraph(QChar back);
  bool IsLegalToCaclulateExpression(QChar back);
  void SetEToString();
};
#endif  // VIEWDEFAULT_H
