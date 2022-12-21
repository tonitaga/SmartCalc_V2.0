#ifndef THEME_H
#define THEME_H

#include <QString>

namespace s21 {
class Theme {
 public:
  Theme();
  Theme(bool is_black, bool is_mainwindow = true);

  QString main_sheet;
  QString but_color_operations;
  QString main_label;
  QString but_color_digits;
  QString combo_box;
  QString table_view;
  QString main_label_engineer;
  QString but_color_digits_engineer;
  QString but_color_oper_engineer;
  QString spin_box;

 private:
  bool black;
  bool mainwindow;
  void InitializeTheme();
};
}  // namespace s21

#endif  // THEME_H
