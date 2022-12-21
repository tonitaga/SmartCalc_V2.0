#include "viewdefault.h"

#include <QDesktopServices>
#include <QKeyEvent>
#include <QStandardItemModel>
#include <QUrl>

#include "ui_viewdefault.h"

#define DEFAULT 0
#define CREDIT 1
#define GRAPH 2
#define DEPOSIT 3
#define ENGINEER 4
#define TEMPERATURE 5

#define ANNUITY 0
#define DIFFERENTIATED 1

#define MONTH 0
#define YEAR 1

#define ONCEMONTH 0
#define ONCEQUATER 1
#define ONCEYEAR 2

#define BLACK true
#define LIGHT false

#define CELSIUS 0
#define KELVIN 1
#define FAHRENHEIT 2
#define REUMOR 3

ViewDefault::ViewDefault(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::ViewDefault),
      is_start(true),
      is_black(true),
      is_function(false) {
  ui->setupUi(this);

  setWindowOpacity(0.98);
  setWindowTitle("Калькулятор");

  ui->stackedWidget->setCurrentIndex(DEFAULT);
  ui->graph_widget->setInteraction(QCP::iRangeZoom, true);
  ui->graph_widget->setInteraction(QCP::iRangeDrag, true);

  ConnectDefaultCalc();
  ConnectEngineerCalc();

  SetTheme(BLACK);
  AllocateModelsAndControllers();
}

ViewDefault::~ViewDefault() {
  DeallocateModelsAndControllers();
  delete ui;
}

/****************************************************************************
 *     ©tonitaga                                               ©tonitaga    *
 *                                                                          *
 *          BLOCK OF CODE WORKING ON A PRIVATE SLOTS OF PROGRAM             *
 *                                                                          *
 *     ©tonitaga                                               ©tonitaga    *
 *****************************************************************************/

/*    DEFAULT CACLULATOR PRIVATE SLOTS    */

/**
 * @brief ViewDefault::on_pushButton_caclulate_clicked
 * Функция которая делает вычисления для default_calc
 */
void ViewDefault::on_pushButton_caclulate_clicked() {
  if (!CheckSize(ui->expression_line->text())) {
    on_pushButton_clear_all_clicked();
    return;
  }
  if (ui->saved_label_expression->text().size() != 0u) {
    double result = 0.0;
    QChar last_symbol = ui->saved_label_expression->text().back();
    if (last_symbol == '+' || last_symbol == '-' || last_symbol == '*' ||
        last_symbol == '/') {
      double first_value =
          RemoveLastSimbol(ui->saved_label_expression->text()).toDouble();
      double second_value = ui->expression_line->text().toDouble();

      if (last_symbol == '+')
        result = d_controller->Add(first_value, second_value);
      if (last_symbol == '-')
        result = d_controller->Sub(first_value, second_value);
      if (last_symbol == '*')
        result = d_controller->Multiply(first_value, second_value);
      if (last_symbol == '/')
        result = d_controller->Divide(first_value, second_value);

      ui->saved_label_expression->setText(ui->saved_label_expression->text() +
                                          ui->expression_line->text() + "=");
      ui->expression_line->setText(QString::number(result));
      is_start = true;
    }
  }
}

void ViewDefault::on_digitnumbers_clicked() {
  QPushButton *clicked_button = (QPushButton *)sender();
  if (is_start) {
    if (ui->stackedWidget->currentIndex() == DEFAULT)
      ui->expression_line->setText(clicked_button->text());
    else
      ui->expression_line_engineer->setText(clicked_button->text());
    is_start = false;
  } else {
    if (ui->stackedWidget->currentIndex() == DEFAULT)
      ui->expression_line->setText(ui->expression_line->text() +
                                   clicked_button->text());
    else {
      QChar back = ui->expression_line_engineer->text().back();
      if ((IsOperatorOrOpenBracketOrDigit(back) || IsLetter(back) ||
           back == '.')) {
        ui->expression_line_engineer->setText(
            ui->expression_line_engineer->text() + clicked_button->text());
      }
    }
  }
}

void ViewDefault::on_operators_clicked() {
  if (!CheckSize(ui->expression_line->text())) {
    on_pushButton_clear_all_clicked();
    return;
  }
  QPushButton *clicked_button = (QPushButton *)sender();
  QString operator_;
  if (clicked_button->text() == "+")
    operator_ = "+";
  else if (clicked_button->text() == "-")
    operator_ = "-";
  else if (clicked_button->text() == "×")
    operator_ = "*";
  else if (clicked_button->text() == "÷")
    operator_ = "/";

  WorkingAboutOperator(operator_);
  is_start = true;
}

void ViewDefault::on_operators_engineer_clicked() {
  if (!CheckSize(ui->expression_line_engineer->text())) {
    on_pushButton_clear_all_e_clicked();
    return;
  }
  QPushButton *clicked_button = (QPushButton *)sender();
  QString operator_;
  if (clicked_button->text() == "+")
    operator_ = "+";
  else if (clicked_button->text() == "-")
    operator_ = "-";
  else if (clicked_button->text() == "×")
    operator_ = "*";
  else if (clicked_button->text() == "÷")
    operator_ = "/";
  QChar back = ui->expression_line_engineer->text().back();
  if (!IsOperator(back)) {
    if (back == '(') {
      if (operator_ == "+" || operator_ == "-")
        ui->expression_line_engineer->setText(
            ui->expression_line_engineer->text() + operator_);
    } else {
      ui->expression_line_engineer->setText(
          ui->expression_line_engineer->text() + operator_);
    }
    is_start = false;
  }
}

void ViewDefault::on_pushButton_delete_one_clicked() { DeleteBackFromStr(); }

void ViewDefault::on_pushButton_clear_all_clicked() {
  if (ui->stackedWidget->currentIndex() == DEFAULT) {
    ui->expression_line->setText("0");
    ui->saved_label_expression->clear();
  } else {
    ui->expression_line_engineer->setText("0");
  }
  is_start = true;
}

void ViewDefault::on_pushButton_save_clear_all_clicked() {
  on_pushButton_clear_all_clicked();
}

void ViewDefault::on_pushButton_percent_clicked() {
  ui->saved_label_expression->clear();
  ui->expression_line->setText(QString::number(
      d_controller->Percent(ui->expression_line->text().toDouble())));
  is_start = true;
}

void ViewDefault::on_pushButton_one_divide_value_clicked() {
  ui->saved_label_expression->setText("1/" + ui->expression_line->text() + "=");
  ui->expression_line->setText(QString::number(
      d_controller->DivideOneToValue(ui->expression_line->text().toDouble())));
  is_start = true;
}

void ViewDefault::on_pushButton_value_pow_two_clicked() {
  ui->saved_label_expression->setText("sqr(" + ui->expression_line->text() +
                                      ")=");
  ui->expression_line->setText(QString::number(
      d_controller->Square(ui->expression_line->text().toDouble())));
  is_start = true;
}

void ViewDefault::on_pushButton_sqrt_value_clicked() {
  ui->saved_label_expression->setText("sqrt(" + ui->expression_line->text() +
                                      ")=");
  ui->expression_line->setText(QString::number(
      d_controller->Sqrting(ui->expression_line->text().toDouble())));
  is_start = true;
}

void ViewDefault::on_pushButton_change_sign_clicked() {
  ui->expression_line->setText(QString::number(
      d_controller->ChangeSign(ui->expression_line->text().toDouble())));
}

void ViewDefault::on_pushButton_point_clicked() {
  if (!ui->expression_line->text().contains('.')) {
    ui->expression_line->setText(ui->expression_line->text() + ".");
    is_start = false;
  }
}

/*    CREDIT CACLULATOR PRIVATE SLOTS    */

void ViewDefault::on_pushButton_caclulate_credit_clicked() {
  int period = 0, type = 0;
  double amount_money = 0.0, percent = 0.0;
  GetCreditDataFromView(&period, &amount_money, &percent, &type);
  if (CheckCreditDataFromView(period, amount_money, percent)) {
    c_controller->CreditStart(amount_money, period, percent, type);
    SetCreditDataToView(type);
    MakeTableForCredit();
    c_controller->Reset();
  }
}

void ViewDefault::on_pushButton_calcru_clicked() {
  QDesktopServices::openUrl(QUrl("https://calcus.ru/kreditnyj-kalkulyator"));
}

/*    DEPOSIT CACLULATOR PRIVATE SLOTS    */

void ViewDefault::on_pushButton_caclulate_deposit_clicked() {
  int period = 0, type = 0, periodically = 0;
  double amount_money = 0.0, percent = 0.0;
  GetDepositDataFromView(&period, &amount_money, &percent, &type,
                         &periodically);
  if (CheckDepositDataFromView(period, amount_money, percent)) {
    dd_controller->DepositStart(amount_money, period, percent, type,
                                periodically);
    SetDepositDataToView();
    MakeTableForDeposit(period, periodically);
    dd_controller->Reset();
  }
}

void ViewDefault::on_pushButton_calcru_deposit_clicked() {
  QDesktopServices::openUrl(QUrl("https://calcus.ru/kalkulyator-vkladov"));
}

/*    ENGINEER CACLULATOR PRIVATE SLOTS    */

void ViewDefault::on_pushButton_caclulate_e_clicked() {
  QChar back = ui->expression_line_engineer->text().back();
  if (!CheckSize(ui->expression_line_engineer->text())) {
    on_pushButton_clear_all_e_clicked();
    return;
  }
  if (ui->expression_line_engineer->text().size() != 0) {
    if (IsLegalToBuildGraph(back)) {
      ui->stackedWidget->setCurrentIndex(GRAPH);
      BuildGraph();
    } else {
      if (IsLegalToCaclulateExpression(back)) {
        double result = e_controller->Calculate(
            ui->expression_line_engineer->text().toStdString(), 0);
        ui->expression_line_engineer->setText(QString::number(result));
        e_controller->Reset();
        if (result == 0.0) {
          on_pushButton_clear_all_e_clicked();
        }
      } else {
        on_pushButton_clear_all_e_clicked();
      }
    }
  }
}

void ViewDefault::on_comboBox_trigonometry_currentIndexChanged(int index) {
  if (index != 0) {
    QChar back = ui->expression_line_engineer->text().back();
    if (is_start) {
      ui->expression_line_engineer->setText(
          ui->comboBox_trigonometry->currentText() + "(");
      is_start = false;
    } else {
      if (IsOperatorOrOpenBracket(back) || back == '0') {
        ui->expression_line_engineer->setText(
            ui->expression_line_engineer->text() +
            ui->comboBox_trigonometry->currentText() + "(");
      }
    }
    ui->comboBox_trigonometry->setCurrentIndex(0);
  }
}

void ViewDefault::on_comboBox_functions_currentIndexChanged(int index) {
  if (index != 0) {
    QString open_bracket;
    QChar back = ui->expression_line_engineer->text().back();
    if (index == 1) open_bracket += "(";
    if (is_start) {
      if (index == 1) {
        ui->expression_line_engineer->setText(
            ui->comboBox_functions->currentText() + open_bracket);
        qDebug() << "index = sqrt and is_start";
        is_start = false;
      }
    } else {
      if (index == 1 && IsOperatorOrOpenBracket(back))
        ui->expression_line_engineer->setText(
            ui->expression_line_engineer->text() +
            ui->comboBox_functions->currentText() + open_bracket);
      else if (index == 2 && (IsOperator(back) || IsDigit(back)))
        ui->expression_line_engineer->setText(
            ui->expression_line_engineer->text() +
            ui->comboBox_functions->currentText() + open_bracket);
      else if (index == 3 && IsDigit(back))
        ui->expression_line_engineer->setText(
            ui->expression_line_engineer->text() +
            ui->comboBox_functions->currentText() + open_bracket);
    }
    ui->comboBox_functions->setCurrentIndex(0);
  }
}

void ViewDefault::on_pushButton_clear_all_e_clicked() {
  on_pushButton_clear_all_clicked();
}

void ViewDefault::on_pushButton_delete_one_e_clicked() {
  QChar back = ui->expression_line_engineer->text().back();
  if (back == '(') {
    while (!IsOperator(back) && back != '0') {
      DeleteBackFromStr();
      back = ui->expression_line_engineer->text().back();
    }
  } else if (IsLetter(back)) {
    while (!IsDigit(back)) {
      DeleteBackFromStr();
      back = ui->expression_line_engineer->text().back();
    }
  } else {
    DeleteBackFromStr();
  }
}

void ViewDefault::on_pushButton_brackets_clicked() {
  QChar back = ui->expression_line_engineer->text().back();
  if (is_start) {
    ui->expression_line_engineer->setText("(");
    is_start = false;
  } else if (OpenBracketsGreaterCloseBrackets(
                 ui->expression_line_engineer->text())) {
    if (back == ')' || IsDigit(back))
      ui->expression_line_engineer->setText(
          ui->expression_line_engineer->text() + ")");
    if (IsOperator(back)) {
      ui->expression_line_engineer->setText(
          ui->expression_line_engineer->text() + "(");
    }
  } else if (OpenBracketsEqualCloseBrackets(
                 ui->expression_line_engineer->text())) {
    if (IsOperator(back))
      ui->expression_line_engineer->setText(
          ui->expression_line_engineer->text() + "(");
  }
}

void ViewDefault::on_pushButton_percent_e_clicked() {
  bool only_digits = true;
  if (!is_start) {
    if (ui->expression_line_engineer->text().toDouble() == 0)
      only_digits = false;
    if (only_digits) {
      ui->expression_line_engineer->setText(
          QString::number(e_controller->Percent(
              ui->expression_line_engineer->text().toDouble())));
    } else {
      if (ui->expression_line_engineer->text() != "0") {
        if (!IsOperator(ui->expression_line_engineer->text().back()))
          ui->expression_line_engineer->setText(
              "(" + ui->expression_line_engineer->text() + ")*0.01");
      }
    }
  }
}

void ViewDefault::on_pushButton_function_clicked() {
  if (is_function) {
    ui->label_function->clear();
    on_pushButton_clear_all_e_clicked();
    is_function = false;
  } else {
    ui->label_function->setText("f(x)=");
    is_function = true;
  }
}

void ViewDefault::on_pushButton_x_clicked() {
  if (is_start) {
    ui->expression_line_engineer->setText("x");
    is_start = false;
  } else {
    QChar back = ui->expression_line_engineer->text().back();
    if (IsOperatorOrOpenBracket(back))
      ui->expression_line_engineer->setText(
          ui->expression_line_engineer->text() + "x");
  }
}

void ViewDefault::on_pushButton_point_e_clicked() {
  QChar back = ui->expression_line_engineer->text().back();
  qsizetype count_points_in_digit = 0;
  if (is_start) {
    ui->expression_line_engineer->setText(ui->expression_line_engineer->text() +
                                          '.');
    is_start = false;
  }

  for (auto it = ui->expression_line_engineer->text().end(); !IsOperator(*it);
       it--) {
    if (*it == '.') count_points_in_digit += 1;
  }

  if (count_points_in_digit == 0)
    if (!IsOperatorOrOpenBracket(back))
      ui->expression_line_engineer->setText(
          ui->expression_line_engineer->text() + '.');
}

/*    GRAPH CACLULATOR PRIVATE SLOTS    */

void ViewDefault::BuildGraph() {
  ui->graph_widget->clearGraphs();
  ui->graph_widget->replot();

  QString expression = ui->expression_line_engineer->text();
  double x_min = ui->spinBox_xmin->text().toDouble();
  double x_max = ui->spinBox_xmax->text().toDouble();

  if (x_min - x_max != 0.0) {
    double step = 0.001 * (fabs(x_min) + fabs(x_max));
    g_controller->CaclulateGraph(expression.toStdString(), x_min, x_max, step);
    auto x_points = g_controller->GetXPoints();
    auto y_points = g_controller->GetYPoints();

    if (x_min < x_max) {
      ui->graph_widget->xAxis->setRange(x_min, x_max);
      ui->graph_widget->yAxis->setRange(
          *(std::min_element(y_points.begin(), y_points.end())),
          *(std::max_element(y_points.begin(), y_points.end())));
    } else {
      ui->graph_widget->xAxis->setRange(x_max, x_min);
      ui->graph_widget->yAxis->setRange(
          *(std::min_element(y_points.begin(), y_points.end())),
          *(std::max_element(y_points.begin(), y_points.end())));
    }

    QPen pen;
    pen.setWidth(2.0);
    pen.setColor(QColor(23, 171, 234));
    ui->graph_widget->addGraph()->setPen(pen);
    for (auto i = 0u; i != g_controller->GetXPoints().size(); ++i) {
      ui->graph_widget->graph(0)->addData(x_points[i], y_points[i]);
    }

    ui->graph_widget->replot();
    g_controller->Reset();
  }
}

void ViewDefault::on_pushButton_graph_clear_clicked() {
  ui->graph_widget->clearGraphs();
  ui->graph_widget->replot();
  on_pushButton_clear_all_e_clicked();
  on_pushButton_function_clicked();
}

void ViewDefault::on_pushButton_addGraph_clicked() {
  on_pushButton_graph_clear_clicked();
  if (!is_function) on_pushButton_function_clicked();
  ui->stackedWidget->setCurrentIndex(ENGINEER);
}

void ViewDefault::on_spinBox_xmin_valueChanged(int arg1) {
  BuildGraph();
  (void)arg1;
}

void ViewDefault::on_spinBox_xmax_valueChanged(int arg1) {
  on_spinBox_xmin_valueChanged(arg1);
}

/****************************************************************************
 *     ©tonitaga                                               ©tonitaga    *
 *                                                                          *
 *          BLOCK OF CODE WORKING ON A CONNECTION SLOTS OF PROGRAM          *
 *                                                                          *
 *     ©tonitaga                                               ©tonitaga    *
 *****************************************************************************/

void ViewDefault::ConnectDefaultCalc() {
  connect(ui->pushButton_zero, SIGNAL(clicked()), this,
          SLOT(on_digitnumbers_clicked()));
  connect(ui->pushButton_one, SIGNAL(clicked()), this,
          SLOT(on_digitnumbers_clicked()));
  connect(ui->pushButton_two, SIGNAL(clicked()), this,
          SLOT(on_digitnumbers_clicked()));
  connect(ui->pushButton_three, SIGNAL(clicked()), this,
          SLOT(on_digitnumbers_clicked()));
  connect(ui->pushButton_four, SIGNAL(clicked()), this,
          SLOT(on_digitnumbers_clicked()));
  connect(ui->pushButton_five, SIGNAL(clicked()), this,
          SLOT(on_digitnumbers_clicked()));
  connect(ui->pushButton_six, SIGNAL(clicked()), this,
          SLOT(on_digitnumbers_clicked()));
  connect(ui->pushButton_seven, SIGNAL(clicked()), this,
          SLOT(on_digitnumbers_clicked()));
  connect(ui->pushButton_eight, SIGNAL(clicked()), this,
          SLOT(on_digitnumbers_clicked()));
  connect(ui->pushButton_nine, SIGNAL(clicked()), this,
          SLOT(on_digitnumbers_clicked()));

  connect(ui->pushButton_add, SIGNAL(clicked()), this,
          SLOT(on_operators_clicked()));
  connect(ui->pushButton_sub, SIGNAL(clicked()), this,
          SLOT(on_operators_clicked()));
  connect(ui->pushButton_multiply, SIGNAL(clicked()), this,
          SLOT(on_operators_clicked()));
  connect(ui->pushButton_divide, SIGNAL(clicked()), this,
          SLOT(on_operators_clicked()));
}

void ViewDefault::ConnectEngineerCalc() {
  connect(ui->pushButton_zero_e, SIGNAL(clicked()), this,
          SLOT(on_digitnumbers_clicked()));
  connect(ui->pushButton_one_e, SIGNAL(clicked()), this,
          SLOT(on_digitnumbers_clicked()));
  connect(ui->pushButton_two_e, SIGNAL(clicked()), this,
          SLOT(on_digitnumbers_clicked()));
  connect(ui->pushButton_three_e, SIGNAL(clicked()), this,
          SLOT(on_digitnumbers_clicked()));
  connect(ui->pushButton_four_e, SIGNAL(clicked()), this,
          SLOT(on_digitnumbers_clicked()));
  connect(ui->pushButton_five_e, SIGNAL(clicked()), this,
          SLOT(on_digitnumbers_clicked()));
  connect(ui->pushButton_six_e, SIGNAL(clicked()), this,
          SLOT(on_digitnumbers_clicked()));
  connect(ui->pushButton_seven_e, SIGNAL(clicked()), this,
          SLOT(on_digitnumbers_clicked()));
  connect(ui->pushButton_eight_e, SIGNAL(clicked()), this,
          SLOT(on_digitnumbers_clicked()));
  connect(ui->pushButton_nine_e, SIGNAL(clicked()), this,
          SLOT(on_digitnumbers_clicked()));

  connect(ui->pushButton_add_e, SIGNAL(clicked()), this,
          SLOT(on_operators_engineer_clicked()));
  connect(ui->pushButton_sub_e, SIGNAL(clicked()), this,
          SLOT(on_operators_engineer_clicked()));
  connect(ui->pushButton_multiply_e, SIGNAL(clicked()), this,
          SLOT(on_operators_engineer_clicked()));
  connect(ui->pushButton_divide_e, SIGNAL(clicked()), this,
          SLOT(on_operators_engineer_clicked()));
}

/****************************************************************************
 *     ©tonitaga                                               ©tonitaga    *
 *                                                                          *
 *           BLOCK OF CODE WORKING ON A TRIGGER OF MENU ACTIONS             *
 *                                                                          *
 *     ©tonitaga                                               ©tonitaga    *
 *****************************************************************************/

void ViewDefault::on_action_default_triggered() {
  ui->stackedWidget->setCurrentIndex(DEFAULT);
  ui->menu_text->setTitle("Обычный");
  is_start = true;
}

void ViewDefault::on_action_engineer_triggered() {
  ui->stackedWidget->setCurrentIndex(ENGINEER);
  ui->menu_text->setTitle("Инженерный");
  is_start = true;
}

void ViewDefault::on_action_graph_triggered() {
  ui->stackedWidget->setCurrentIndex(GRAPH);
  ui->menu_text->setTitle("Построение функций");
}

void ViewDefault::on_action_credit_triggered() {
  ui->stackedWidget->setCurrentIndex(CREDIT);
  ui->menu_text->setTitle("Кредитный");
}

void ViewDefault::on_action_deposit_triggered() {
  ui->stackedWidget->setCurrentIndex(DEPOSIT);
  ui->menu_text->setTitle("Депозитный");
}

void ViewDefault::on_action_about_triggered() {
  QDesktopServices::openUrl(QUrl("https://github.com/tonitaga"));
}

void ViewDefault::on_action_light_triggered() {
  if (is_black) {
    SetTheme(LIGHT);
    is_black = false;
  }
}

void ViewDefault::on_action_black_triggered() {
  if (!is_black) {
    SetTheme(BLACK);
    is_black = true;
  }
}

/****************************************************************************
 *     ©tonitaga                                               ©tonitaga    *
 *                                                                          *
 *                BLOCK OF CODE WORKING ON A CALCULATOR THEME               *
 *                                                                          *
 *     ©tonitaga                                               ©tonitaga    *
 *****************************************************************************/

void ViewDefault::SetTheme(bool black) {
  s21::Theme mainwindow(black);
  setStyleSheet(mainwindow.main_sheet);
  s21::Theme theme(black);
  SetThemeDefault(theme);
  SetThemeEngineer(theme);
  SetThemeCredit(theme);
  SetThemeDeposit(theme);
  SetThemeGraph(theme);
  SetThemeGraphWidget(black);
}

void ViewDefault::SetThemeDefault(s21::Theme theme) {
  ui->default_calc->setStyleSheet(theme.main_sheet);
  ui->expression_line->setStyleSheet(theme.main_label);

  ui->pushButton_zero->setStyleSheet(theme.but_color_digits);
  ui->pushButton_one->setStyleSheet(theme.but_color_digits);
  ui->pushButton_two->setStyleSheet(theme.but_color_digits);
  ui->pushButton_three->setStyleSheet(theme.but_color_digits);
  ui->pushButton_four->setStyleSheet(theme.but_color_digits);
  ui->pushButton_five->setStyleSheet(theme.but_color_digits);
  ui->pushButton_six->setStyleSheet(theme.but_color_digits);
  ui->pushButton_seven->setStyleSheet(theme.but_color_digits);
  ui->pushButton_eight->setStyleSheet(theme.but_color_digits);
  ui->pushButton_nine->setStyleSheet(theme.but_color_digits);
  ui->pushButton_change_sign->setStyleSheet(theme.but_color_digits);
  ui->pushButton_point->setStyleSheet(theme.but_color_digits);

  ui->pushButton_add->setStyleSheet(theme.but_color_operations);
  ui->pushButton_sub->setStyleSheet(theme.but_color_operations);
  ui->pushButton_multiply->setStyleSheet(theme.but_color_operations);
  ui->pushButton_divide->setStyleSheet(theme.but_color_operations);
  ui->pushButton_delete_one->setStyleSheet(theme.but_color_operations);
  ui->pushButton_clear_all->setStyleSheet(theme.but_color_operations);
  ui->pushButton_save_clear_all->setStyleSheet(theme.but_color_operations);
  ui->pushButton_one_divide_value->setStyleSheet(theme.but_color_operations);
  ui->pushButton_percent->setStyleSheet(theme.but_color_operations);
  ui->pushButton_sqrt_value->setStyleSheet(theme.but_color_operations);
  ui->pushButton_value_pow_two->setStyleSheet(theme.but_color_operations);
}

void ViewDefault::SetThemeEngineer(s21::Theme theme) {
  ui->engineer_calc->setStyleSheet(theme.main_sheet);
  ui->expression_line_engineer->setStyleSheet(theme.main_label_engineer);
  ui->comboBox_functions->setStyleSheet(theme.combo_box);
  ui->comboBox_trigonometry->setStyleSheet(theme.combo_box);

  ui->pushButton_zero_e->setStyleSheet(theme.but_color_digits_engineer);
  ui->pushButton_one_e->setStyleSheet(theme.but_color_digits_engineer);
  ui->pushButton_two_e->setStyleSheet(theme.but_color_digits_engineer);
  ui->pushButton_three_e->setStyleSheet(theme.but_color_digits_engineer);
  ui->pushButton_four_e->setStyleSheet(theme.but_color_digits_engineer);
  ui->pushButton_five_e->setStyleSheet(theme.but_color_digits_engineer);
  ui->pushButton_six_e->setStyleSheet(theme.but_color_digits_engineer);
  ui->pushButton_seven_e->setStyleSheet(theme.but_color_digits_engineer);
  ui->pushButton_eight_e->setStyleSheet(theme.but_color_digits_engineer);
  ui->pushButton_nine_e->setStyleSheet(theme.but_color_digits_engineer);
  ui->pushButton_brackets->setStyleSheet(theme.but_color_digits_engineer);
  ui->pushButton_point_e->setStyleSheet(theme.but_color_digits_engineer);

  ui->pushButton_add_e->setStyleSheet(theme.but_color_oper_engineer);
  ui->pushButton_sub_e->setStyleSheet(theme.but_color_oper_engineer);
  ui->pushButton_multiply_e->setStyleSheet(theme.but_color_oper_engineer);
  ui->pushButton_divide_e->setStyleSheet(theme.but_color_oper_engineer);
  ui->pushButton_delete_one_e->setStyleSheet(theme.but_color_oper_engineer);
  ui->pushButton_clear_all_e->setStyleSheet(theme.but_color_oper_engineer);
  ui->pushButton_percent_e->setStyleSheet(theme.but_color_oper_engineer);
  ui->pushButton_function->setStyleSheet(theme.but_color_oper_engineer);
  ui->pushButton_x->setStyleSheet(theme.but_color_oper_engineer);
}

void ViewDefault::SetThemeCredit(s21::Theme theme) {
  ui->credit_calc->setStyleSheet(theme.main_sheet);
  ui->tableView->setStyleSheet(theme.table_view);
  ui->comboBox_period->setStyleSheet(theme.combo_box);
  ui->comboBox_type->setStyleSheet(theme.combo_box);
}

void ViewDefault::SetThemeDeposit(s21::Theme theme) {
  ui->deposit_calc->setStyleSheet(theme.main_sheet);
  ui->tableViewDeposit->setStyleSheet(theme.table_view);
  ui->comboBox_period_d->setStyleSheet(theme.combo_box);
  ui->comboBox_periodically->setStyleSheet(theme.combo_box);
}

void ViewDefault::SetThemeGraph(s21::Theme theme) {
  ui->graph_calc->setStyleSheet(theme.main_sheet);
  ui->spinBox_xmax->setStyleSheet(theme.spin_box);
  ui->spinBox_xmin->setStyleSheet(theme.spin_box);
  ui->pushButton_graph_clear->setStyleSheet(theme.but_color_digits_engineer);
}

void ViewDefault::SetThemeGraphWidget(bool black) {
  if (black)
    ui->graph_widget->setBackground(QColor(31, 31, 31));
  else
    ui->graph_widget->setBackground(QColor(230, 230, 230));

  ui->graph_widget->xAxis->setTickLabelColor(QColor(3, 144, 252));
  ui->graph_widget->xAxis->setBasePen(QPen(QColor(3, 144, 252)));
  ui->graph_widget->xAxis->setLabelColor(QColor(3, 144, 252));
  ui->graph_widget->xAxis->setTickPen(QPen(QColor(3, 144, 252)));
  ui->graph_widget->xAxis->setSubTickPen(QColor(3, 144, 252));

  ui->graph_widget->yAxis->setTickLabelColor(QColor(3, 144, 252));
  ui->graph_widget->yAxis->setBasePen(QPen(QColor(3, 144, 252)));
  ui->graph_widget->yAxis->setLabelColor(QColor(3, 144, 252));
  ui->graph_widget->yAxis->setTickPen(QPen(QColor(3, 144, 252)));
  ui->graph_widget->yAxis->setSubTickPen(QColor(3, 144, 252));
}

/****************************************************************************
 *     ©tonitaga                                               ©tonitaga    *
 *                                                                          *
 *                   CODE BLOCK FOR KEYBOARD OPERATIONS                     *
 *                                                                          *
 *     ©tonitaga                                               ©tonitaga    *
 *****************************************************************************/

void ViewDefault::keyPressEvent(QKeyEvent *e) {
  if (ui->stackedWidget->currentIndex() == DEFAULT)
    keyPressEventDefault(e);
  else if (ui->stackedWidget->currentIndex() == ENGINEER)
    keyPressEventEngineer(e);
}

void ViewDefault::keyPressEventDefault(QKeyEvent *e) {
  switch (e->key()) {
    case Qt::Key_0:
      emit ui->pushButton_zero->clicked();
      break;
    case Qt::Key_1:
      emit ui->pushButton_one->clicked();
      break;
    case Qt::Key_2:
      emit ui->pushButton_two->clicked();
      break;
    case Qt::Key_3:
      emit ui->pushButton_three->clicked();
      break;
    case Qt::Key_4:
      emit ui->pushButton_four->clicked();
      break;
    case Qt::Key_5:
      emit ui->pushButton_five->clicked();
      break;
    case Qt::Key_6:
      emit ui->pushButton_six->clicked();
      break;
    case Qt::Key_7:
      emit ui->pushButton_seven->clicked();
      break;
    case Qt::Key_8:
      emit ui->pushButton_eight->clicked();
      break;
    case Qt::Key_9:
      emit ui->pushButton_nine->clicked();
      break;
    case Qt::Key_Plus:
      emit ui->pushButton_add->clicked();
      break;
    case Qt::Key_Minus:
      emit ui->pushButton_sub->clicked();
      break;
    case 42:
      emit ui->pushButton_multiply->clicked();
      break; /*  (*)  */
    case 47:
      emit ui->pushButton_divide->clicked();
      break; /*  (/)  */
    case 61:
      emit ui->pushButton_caclulate->clicked();
      break; /*  (=)  */
    case 16777220:
      emit ui->pushButton_caclulate->clicked();
      break; /*  (Enter)  */
    case Qt::Key_Backspace:
      emit ui->pushButton_delete_one->clicked();
      break;
    case Qt::Key_Delete:
      emit ui->pushButton_clear_all->clicked();
      break;
    case Qt::Key_Percent:
      emit ui->pushButton_percent->clicked();
      break;
    case 46:
      emit ui->pushButton_point->clicked();
      break;
  }
}

void ViewDefault::keyPressEventEngineer(QKeyEvent *e) {
  switch (e->key()) {
    case Qt::Key_0:
      emit ui->pushButton_zero_e->clicked();
      break;
    case Qt::Key_1:
      emit ui->pushButton_one_e->clicked();
      break;
    case Qt::Key_2:
      emit ui->pushButton_two_e->clicked();
      break;
    case Qt::Key_3:
      emit ui->pushButton_three_e->clicked();
      break;
    case Qt::Key_4:
      emit ui->pushButton_four_e->clicked();
      break;
    case Qt::Key_5:
      emit ui->pushButton_five_e->clicked();
      break;
    case Qt::Key_6:
      emit ui->pushButton_six_e->clicked();
      break;
    case Qt::Key_7:
      emit ui->pushButton_seven_e->clicked();
      break;
    case Qt::Key_8:
      emit ui->pushButton_eight_e->clicked();
      break;
    case Qt::Key_9:
      emit ui->pushButton_nine_e->clicked();
      break;
    case Qt::Key_Plus:
      emit ui->pushButton_add_e->clicked();
      break;
    case Qt::Key_Minus:
      emit ui->pushButton_sub_e->clicked();
      break;
    case 42:
      emit ui->pushButton_multiply_e->clicked();
      break; /*  (*)  */
    case 47:
      emit ui->pushButton_divide_e->clicked();
      break; /*  (/)  */
    case 61:
      emit ui->pushButton_caclulate_e->clicked();
      break; /*  (=)  */
    case 16777220:
      emit ui->pushButton_caclulate_e->clicked();
      break; /*  (Enter)  */
    case Qt::Key_Backspace:
      emit ui->pushButton_delete_one_e->clicked();
      break;
    case Qt::Key_Delete:
      emit ui->pushButton_clear_all_e->clicked();
      break;
    case Qt::Key_Percent:
      emit ui->pushButton_percent_e->clicked();
      break;
    case 46:
      emit ui->pushButton_point_e->clicked();
      break;
    default:
      qDebug() << e->key();
      break;
  }
}

/****************************************************************************
 *     ©tonitaga                                               ©tonitaga    *
 *                                                                          *
 *                CODE BLOCK FOR SUPPORT FUNCTIONS OF PROGRAM               *
 *                                                                          *
 *     ©tonitaga                                               ©tonitaga    *
 *****************************************************************************/

void ViewDefault::AllocateModelsAndControllers() {
  d_model = new s21::SimpleModel;
  d_controller = new s21::SimpleController(d_model);
  c_model = new s21::CreditModel;
  c_controller = new s21::CreditController(c_model);
  dd_model = new s21::DepositModel;
  dd_controller = new s21::DepositController(dd_model);
  e_model = new s21::EngineerModel;
  e_controller = new s21::EngineerController(e_model);
  g_controller = new s21::GraphController(e_model);
}

void ViewDefault::DeallocateModelsAndControllers() {
  if (d_model) delete d_model;
  if (d_controller) delete d_controller;
  if (c_model) delete c_model;
  if (c_controller) delete c_controller;
  if (dd_model) delete dd_model;
  if (dd_controller) delete dd_controller;
  if (e_model) delete e_model;
  if (e_controller) delete e_controller;
  if (g_controller) delete g_controller;
}

void ViewDefault::DeleteBackFromStr() {
  if (ui->stackedWidget->currentIndex() == DEFAULT) {
    if (ui->expression_line->text().size() != 0) {
      QString new_expression(ui->expression_line->text());
      new_expression.chop(1);

      if (new_expression.size() == 0) {
        new_expression.push_back('0');
        ui->saved_label_expression->clear();
        is_start = true;
      }
      ui->expression_line->setText(new_expression);
    }
  } else {
    if (ui->expression_line_engineer->text().size() != 0) {
      QString new_expression(ui->expression_line_engineer->text());
      new_expression.chop(1);

      if (new_expression.size() == 0) {
        new_expression.push_back('0');
        is_start = true;
      }
      ui->expression_line_engineer->setText(new_expression);
    }
  }
}

bool ViewDefault::IsOperatorOrOpenBracket(QChar token) {
  bool result = false;
  if (token == '(' || IsOperator(token)) result = true;
  return result;
}

bool ViewDefault::IsOperatorOrOpenBracketOrDigit(QChar token) {
  bool result = IsOperatorOrOpenBracket(token);
  if ((token >= '0' && token <= '9') || token == 'x') result = true;
  return result;
}

bool ViewDefault::IsLetter(QChar token) {
  bool result = false;
  if (token >= 'a' && token <= 'z') result = true;
  if (token == 'x') result = false;
  return result;
}

bool ViewDefault::IsOperator(QChar token) {
  bool result = false;
  if (token == '*' || token == '/' || token == '+' || token == '-' ||
      token == '^')
    result = true;
  return result;
}

bool ViewDefault::IsDigit(QChar token) {
  bool result = false;
  if ((token >= '0' && token <= '9') || token == 'x') result = true;
  return result;
}

bool ViewDefault::OpenBracketsEqualCloseBrackets(QString str) {
  int count_1 = 0, count_2 = 0;
  for (auto x : str) {
    if (x == '(') count_1 += 1;
    if (x == ')') count_2 += 1;
  }
  return count_1 == count_2;
}

bool ViewDefault::OpenBracketsGreaterCloseBrackets(QString str) {
  int count_1 = 0, count_2 = 0;
  for (auto x : str) {
    if (x == '(') count_1 += 1;
    if (x == ')') count_2 += 1;
  }
  return count_1 > count_2;
}

bool ViewDefault::IsLegalToBuildGraph(QChar back) {
  bool result = false;
  if (is_function && ui->expression_line_engineer->text().contains('x') &&
      !IsLetter(back) && !IsOperatorOrOpenBracket(back) &&
      OpenBracketsEqualCloseBrackets(ui->expression_line_engineer->text()))
    result = true;
  return result;
}

bool ViewDefault::IsLegalToCaclulateExpression(QChar back) {
  bool result = false;
  if (!ui->expression_line_engineer->text().contains('x') && !IsLetter(back) &&
      !IsOperator(back))
    result = true;
  return result;
}

void ViewDefault::GetCreditDataFromView(int *period, double *amount_money,
                                        double *percent, int *type) {
  if (ui->comboBox_period->currentIndex() == MONTH)
    *period = ui->lineEdit_period->text().toInt();
  else
    *period = 12 * ui->lineEdit_period->text().toInt();
  *amount_money = ui->lineEdit_total_money->text().toDouble();
  *percent = ui->lineEdit_percent->text().toDouble();
  if (ui->comboBox_type->currentIndex() == ANNUITY)
    *type = ANNUITY;
  else
    *type = DIFFERENTIATED;
}

bool ViewDefault::CheckCreditDataFromView(int period, double amount_money,
                                          double percent) {
  bool result = true;
  if (period <= 0 || amount_money <= 0.0 || percent <= 0.0) result = false;
  return result;
}

void ViewDefault::SetCreditDataToView(int type) {
  ui->label_total_overpayment->setText(
      QString::number(c_controller->GetOverpayment()) + " ₽");
  ui->label_total_payment->setText(
      QString::number(c_controller->GetTotalPayment()) + " ₽");
  auto payment = c_controller->GetMonthlyPayment();
  if (type == ANNUITY) {
    ui->label_monthly_payment->setText(QString::number(payment.at(0)) + " ₽");
  } else {
    ui->label_monthly_payment->setText(
        QString::number(payment.at(0)) + " ₽..." +
        QString::number(payment.back()) + " ₽");
  }
}

void ViewDefault::GetDepositDataFromView(int *period, double *amount_money,
                                         double *percent, int *type,
                                         int *periodically) {
  if (ui->comboBox_periodically->currentIndex() == ONCEMONTH) *periodically = 1;
  if (ui->comboBox_periodically->currentIndex() == ONCEQUATER)
    *periodically = 4;
  if (ui->comboBox_periodically->currentIndex() == ONCEYEAR) *periodically = 12;
  if (ui->comboBox_period_d->currentIndex() == MONTH) {
    *period = ui->lineEdit_period_d->text().toInt();
  } else {
    *period = 12 * ui->lineEdit_period_d->text().toInt();
  }
  *amount_money = ui->lineEdit_total_money_d->text().toDouble();
  *percent = ui->lineEdit_percent_d->text().toDouble();
  if (ui->checkBox_type->isChecked())
    *type = 1;
  else
    *type = 0;
}

bool ViewDefault::CheckDepositDataFromView(int period, double amount_money,
                                           double percent) {
  bool result = true;
  if (period <= 0.0 || amount_money <= 0.0 || percent <= 0.0) result = false;
  return result;
}

void ViewDefault::SetDepositDataToView() {
  ui->label_deposit_amount->setText(
      QString::number(dd_controller->GetTotalMoney()) + " ₽");
  ui->label_total_tax->setText(QString::number(dd_controller->GetTax()) +
                               " ₽");
  ui->label_total_percent->setText(
      QString::number(dd_controller->GetTotalPercentMoney()) + " ₽");
}

bool ViewDefault::CheckSize(QString str) {
  return str.size() <= 255 ? true : false;
}

QString ViewDefault::RemoveLastSimbol(QString str) {
  QString result(str);
  result.chop(1);
  return result;
}

/**
 * @brief ViewDefault::WorkingAboutOperator Функция для default_calc
 * @param operator_ текущий нажатый оператор (+-*||)
 */
void ViewDefault::WorkingAboutOperator(QString operator_) {
  if (ui->saved_label_expression->text().size() == 0u) {
    ui->saved_label_expression->setText(ui->expression_line->text() +
                                        operator_);
  } else {
    if (ui->saved_label_expression->text().back() != operator_.at(0)) {
      if (ui->saved_label_expression->text().back() == '=') {
        ui->saved_label_expression->setText(ui->expression_line->text() +
                                            operator_);
      } else {
        ui->saved_label_expression->setText(
            RemoveLastSimbol(ui->saved_label_expression->text()) + operator_);
      }
    }
  }
}

void ViewDefault::MakeTableForCredit() {
  double period = ui->lineEdit_period->text().toDouble();
  if (ui->comboBox_period->currentIndex() == YEAR) period *= 12;
  QStandardItemModel *model = new QStandardItemModel(period, 3, this);

  auto payment = c_controller->GetMonthlyPayment();
  auto percent = c_controller->GetPercentPayment();
  auto balance = c_controller->GetBalance();

  int current = 0;

  for (auto row = 0; row != model->rowCount(); ++row) {
    for (auto col = 0; col != model->columnCount(); ++col) {
      QModelIndex index = model->index(row, col);
      switch (col) {
        case 0:
          model->setData(index, payment[current] < 0.0 ? 0 : payment[current]);
          break;
        case 1:
          model->setData(index, percent[current] < 0.0 ? 0 : percent[current]);
          break;
        case 2:
          model->setData(index, balance[current] < 0.0 ? 0 : balance[current]);
        default:
          break;
      }
    }
    current++;
  }
  model->setHeaderData(0, Qt::Horizontal, "Сумма\nпогашения");
  model->setHeaderData(1, Qt::Horizontal, "Выплата\nпроцентов");
  model->setHeaderData(2, Qt::Horizontal, "Остаток");
  ui->tableView->setModel(model);
  ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void ViewDefault::MakeTableForDeposit(int period, int periodically) {
  QStandardItemModel *model =
      new QStandardItemModel(period / periodically, 3, this);

  auto balance = dd_controller->GetBalanceV();
  auto percent = dd_controller->GetPercentMoneyV();
  auto added = dd_controller->GetAddedMoneyV();

  int current = 0;
  for (auto row = 0; row != model->rowCount(); ++row) {
    for (auto col = 0; col != model->columnCount(); ++col) {
      QModelIndex index = model->index(row, col);
      switch (col) {
        case 0:
          model->setData(index, percent.at(current));
          break;
        case 1:
          model->setData(index, added.at(current));
          break;
        case 2:
          model->setData(index, balance.at(current));
          break;
        default:
          break;
      }
    }
    current++;
  }
  model->setHeaderData(0, Qt::Horizontal, "Начислено\nпроцентов");
  model->setHeaderData(1, Qt::Horizontal, "Вклад\nпополнен");
  model->setHeaderData(2, Qt::Horizontal, "Остаток\nна вкладе");
  ui->tableViewDeposit->setModel(model);
  ui->tableViewDeposit->setEditTriggers(QAbstractItemView::NoEditTriggers);
}
