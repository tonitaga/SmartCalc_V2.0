#include "theme.h"

s21::Theme::Theme() : black(true), mainwindow(true) {}

s21::Theme::Theme(bool is_black, bool is_mainwindow)
    : black(is_black), mainwindow(is_mainwindow) {
  InitializeTheme();
}

void s21::Theme::InitializeTheme() {
  QString window;
  if (mainwindow)
    window = "QMainWindow {\n";
  else
    window = "QWidget {\n";

  if (black) {
    main_sheet =
        window +
        "background-color: rgb(31,31,31);\n"
        "}\n"
        "\n\nQLineEdit {\n	"
        "background-color: rgb(9,9,9);\n	color: "
        "rgb(255,255,255);\n	"
        "font-size: 20px;\n	qproperty-frame: false;\n}\n\nQLabel "
        "{\n	"
        "background-color: rgb(31,31,31);\n	color: "
        "rgb(255,255,255);\n	"
        "font-size: 18px;\n}\n\nQMenuBar {\n	"
        "background-color: rgb(31,31,31);\n	color: "
        "rgb(255,255,255);\n	"
        "font-size: 14px;\n}\n\nQMenuBar::item:selected {\n	"
        "background-color: rgb(19, 19, 19);\n	color: rgb(255, 255, 255);\n"
        "}\n\nQMenu {\n	background-color: rgb(31,31,31);\n	"
        "color: rgb(255,255,255);\n	font-size: "
        "14px;\n}\n\nQMenu::item{\n	"
        "background-color: rgb(31,31,31);\n	color: rgb(255, 255, 255);\n "
        "}\n\nQMenu::item:selected{\n	background-color: rgb(19, 19, "
        "19);\n	"
        "color: rgb(255, 255, 255);\n	font-size: 15px;\n} ";
    but_color_operations =
        "background-color: rgb(19, 19, 19);\ncolor: rgb(255,255,255);\n"
        "font-size: 24px;";
    but_color_oper_engineer =
        "background-color: rgb(19, 19, 19);\ncolor: rgb(255,255,255);\n"
        "font-size: 18px;";
    but_color_digits =
        "background-color: rgb(6, 6, 6);\ncolor: "
        "rgb(255,255,255);\nfont-size: 24px;";
    but_color_digits_engineer =
        "background-color: rgb(6, 6, 6);\ncolor: "
        "rgb(255,255,255);\nfont-size: 18px;";
    main_label =
        "QLabel {\n	background-color: rgb(31,31,31);\n	"
        "color: rgb(255,255,255);\n	font-size: 46px;\n}";
    main_label_engineer =
        "QLabel {\n	background-color: rgb(31,31,31);\n	"
        "color: rgb(255,255,255);\n	font-size: 34px;\n}";
    combo_box =
        "QComboBox {\n		border: 1px solid rgb(19,19,19);\n        "
        "background-color: rgb(19,19,19);\n        color: "
        "rgb(255,255,255);\n		"
        "font-size: 20px;\n}\nQComboBox QAbstractItemView {\n		"
        "border: 1px solid rgb(19,19,19);\n        background-color: "
        "rgb(19,19,19);\n        "
        "color: rgb(255,255,255);\n		font-size: 20px;\n}";
    table_view =
        "QTableView {\n	background-color: rgb(31,31,31);\n	"
        "color: rgb(255,255,255);\n	border: 1px solid rgb(62, 61, 105);;\n}"
        "\n\nQTableView::item {\n	background-color: "
        "rgb(31,31,31);\n	color: "
        "rgb(255,255,255);\n}\n\nQHeaderView::section {\n	"
        "background-color: "
        "rgb(31,31,31);\n	color: rgb(255,255,255);\n}\n\nQTableView "
        "QTableCornerButton::section {\n	"
        "background-color: rgb(31,31,31);\n	color: "
        "rgb(255,255,255);	\n}\n\nQScrollBar:vertical "
        "{\nborder: none;\nbackground-color: rgb(31,31,31);;\nwidth: "
        "10px;\nmargin: 25px 0 0px 0;\n}"
        "\nQScrollBar::handle:vertical {\nborder-radius: 4px;\nborder-color: "
        "rgba(62, 61, 105,75%);"
        "\nborder-width: 1px; \nborder-style: solid; \nbackground-color: "
        "rgba(62, 61, 105,75%); "
        "\nmin-height: 25px;\n}\nQScrollBar::add-line:vertical{\nwidth: "
        "0px;\nheight: 0px;\n}"
        "\nQScrollBar::sub-line:vertical{\nwidth: 0px;\nheight: "
        "0px;\n}\nQScrollBar::add-page:vertical"
        "{\nbackground-color: "
        "transparent;\n}\nQScrollBar::sub-page:vertical{\nbackground-color: "
        "transparent;"
        "\n}\nQScrollBar:horizontal {\nborder: none;\nbackground-color: "
        "rgb(31,31,31);;\nwidth: 10px;"
        "\nmargin: 25px 0 0px 0;\n}\nQScrollBar::handle:horizontal "
        "{\nborder-radius: 4px;\nborder-color: "
        "rgba(62, 61, 105,75%);\nborder-width: 1px; \nborder-style: solid; "
        "\nbackground-color: "
        "rgba(62, 61, 105,75%); \nmin-height: "
        "25px;\n}\nQScrollBar::add-line:horizontal{\nwidth: "
        "0px;\nheight: 0px;\n}\nQScrollBar::sub-line:horizontal{\nwidth: "
        "0px;\nheight: 0px;\n}"
        "\nQScrollBar::add-page:vertical{\nbackground-color: "
        "transparent;\n}\nQScrollBar::"
        "sub-page:vertical{\nbackground-color: transparent;\n}\n";
    spin_box =
        "QSpinBox {\n	background-color: rgb(19,19,19);\n	color: "
        "rgb(255,255,255);\n	font-size: 20px;\n}";
  } else {
    main_sheet =
        window +
        "background-color: rgb(230,230,230);\n"
        "}\n"
        "\n\n\nQLineEdit {\n	"
        "background-color: rgb(207,207,207);\n	color: rgb(0,0,0);\n	"
        "font-size: 20px;\n	qproperty-frame: false;\n}\n\nQLabel "
        "{\n	"
        "background-color: rgb(230,230,230);\n	color: rgb(0,0,0);\n	"
        "font-size: 18px;\n}\n\nQMenuBar {\n	"
        "background-color: rgb(230,230,230);\n	color: rgb(0,0,0);\n	"
        "font-size: 14px;\n}\n\nQMenuBar::item:selected {\n	"
        "background-color: rgb(207,207,207);\n	color: rgb(0,0,0);\n"
        "}\n\nQMenu {\n	background-color: rgb(230,230,230);\n	"
        "color: rgb(0,0,0);\n	font-size: 14px;\n}\n\nQMenu::item{\n	"
        "background-color: rgb(230,230,230);\n	color: rgb(0,0,0);\n "
        "}\n\nQMenu::item:selected{\n	background-color: "
        "rgb(207,207,207);\n	"
        "color: rgb(0,0,0);\n	font-size: 15px;\n} ";
    but_color_operations =
        "background-color: rgb(240,240,240);\ncolor: rgb(0,0,0);\n"
        "font-size: 24px;";
    but_color_oper_engineer =
        "background-color: rgb(240,240,240);\ncolor: rgb(0,0,0);\n"
        "font-size: 18px;";
    but_color_digits =
        "background-color: rgb(250,250,250);\ncolor: "
        "rgb(0,0,0);\nfont-size: 24px;\n";
    but_color_digits_engineer =
        "background-color: rgb(250,250,250);\ncolor: "
        "rgb(0,0,0);\nfont-size: 18px;\n";
    main_label =
        "QLabel {\n	background-color: rgb(230,230,230);\n	"
        "color: rgb(0,0,0);\n	font-size: 46px;\n}";
    main_label_engineer =
        "QLabel {\n	background-color: rgb(230,230,230);\n	"
        "color: rgb(0,0,0);\n	font-size: 34px;\n}";
    combo_box =
        "QComboBox {\n		border: 1px solid rgb(200,200,200);\n        "
        "background-color: rgb(230,230,230);\n        "
        "color: rgb(0,0,0);\n		font-size: 20px;\n}\nQComboBox "
        "QAbstractItemView {\n		"
        "border: 1px solid rgb(230,230,230);\n        background-color: "
        "rgb(230,230,230);\n        "
        "color: rgb(0,0,0);\n		font-size: 20px;\n}";
    table_view =
        "QTableView {\n	background-color: rgb(230,230,230);\n	"
        "color: rgb(0,0,0);\n	border: 1px solid rgb(62, 61, 105);;\n}"
        "\n\nQTableView::item {\n	background-color: "
        "rgb(230,230,230);\n	color: "
        "rgb(0,0,0);\n}\n\nQHeaderView::section {\n	background-color: "
        "rgb(230,230,230);\n	color: rgb(0,0,0);\n}\n\nQTableView "
        "QTableCornerButton::section {\n	"
        "background-color: rgb(230,230,230);\n	color: rgb(0,0,0);	"
        "\n}\n\nQScrollBar:vertical "
        "{\nborder: none;\nbackground-color: rgb(230,230,230);;\nwidth: "
        "10px;\nmargin: 25px 0 0px 0;\n}"
        "\nQScrollBar::handle:vertical {\nborder-radius: 4px;\nborder-color: "
        "rgba(62, 61, 105,75%);"
        "\nborder-width: 1px; \nborder-style: solid; \nbackground-color: "
        "rgba(62, 61, 105,75%); "
        "\nmin-height: 25px;\n}\nQScrollBar::add-line:vertical{\nwidth: "
        "0px;\nheight: 0px;\n}"
        "\nQScrollBar::sub-line:vertical{\nwidth: 0px;\nheight: "
        "0px;\n}\nQScrollBar::add-page:vertical"
        "{\nbackground-color: "
        "transparent;\n}\nQScrollBar::sub-page:vertical{\nbackground-color: "
        "transparent;"
        "\n}\nQScrollBar:horizontal {\nborder: none;\nbackground-color: "
        "rgb(230,230,230);;\nwidth: 10px;"
        "\nmargin: 25px 0 0px 0;\n}\nQScrollBar::handle:horizontal "
        "{\nborder-radius: 4px;\nborder-color: "
        "rgba(62, 61, 105,75%);\nborder-width: 1px; \nborder-style: solid; "
        "\nbackground-color: "
        "rgba(62, 61, 105,75%); \nmin-height: "
        "25px;\n}\nQScrollBar::add-line:horizontal{\nwidth: "
        "0px;\nheight: 0px;\n}\nQScrollBar::sub-line:horizontal{\nwidth: "
        "0px;\nheight: 0px;\n}"
        "\nQScrollBar::add-page:vertical{\nbackground-color: "
        "transparent;\n}\nQScrollBar::"
        "sub-page:vertical{\nbackground-color: transparent;\n}\n";
    spin_box =
        "QSpinBox {\n	background-color: rgb(240,240,240);\n	color: "
        "rgb(0,0,0);\n	font-size: 20px;\n}";
  }
}
