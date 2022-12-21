#include <QApplication>

#include "viewdefault.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  ViewDefault w;
  w.show();
  return a.exec();
}
