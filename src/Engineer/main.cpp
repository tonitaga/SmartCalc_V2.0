#include "engineercontroller.h"

int main() {
    s21::EngineerModel model;
    s21::EngineerController controller(&model);
    double result = controller.Calculate("2*(-2)+6/56*sin(1)", 0);
    std::cout << result << std::endl;
}
