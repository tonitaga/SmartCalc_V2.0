#include <cmath>
#include <cstring>
#include <iostream>
#include <list>
#include <string>
#include <vector>

namespace s21 {
class EngineerModel {
 private:
  typedef enum {
    OpenBracket,
    CloseBracket,
    Number,
    X,
    Add,
    Sub,
    Mul,
    Div,
    Pow,
    Cos,
    Sin,
    Tan,
    Acos,
    Asin,
    Atan,
    Sqrt,
    Ln,
    Log,
    Mod
  } type_t;
  struct ModelParts {
    double value;
    int priority;
    type_t type;
  };
  std::string expression;
  std::list<ModelParts> to_calculate;
  double answer;
  double x_value;
  std::vector<double> x_points;
  std::vector<double> y_points;

 public:
  EngineerModel() : expression(), answer(0.0), x_value(0.0) {}

  bool Calculate() {
    bool result = true;
    if (CheckForCorrectExpression()) {
      PrepareExpression();
      ExpressionToPolishNotation();
      CalculatePolishNotation();
    } else {
      result = false;
    }
    return result;
  }

  bool CalculateGraph(double x_min, double x_max, double step) {
    for (double x = x_min; x <= x_max; x += step) {
      SetX(x);
      if (Calculate()) {
        x_points.push_back(x);
        y_points.push_back(GetAnswer());
      } else {
        return false;
      }
    }
    return true;
  }

  void SetExpression(const std::string &expr) { expression = expr; }
  void SetX(const double &x) { x_value = x; }
  std::string GetExpression() const { return expression; }

  double GetAnswer() const { return answer; }
  std::vector<double> GetXPoints() const { return x_points; }
  std::vector<double> GetYPoints() const { return y_points; }

  void Reset() {
    answer = 0.0;
    x_value = 0.0;
    to_calculate.clear();
    expression.clear();
    x_points.clear();
    y_points.clear();
  }

  void Percent(double value = 0.0) { answer = value * 0.01; }

 private:
  bool CheckForCorrectExpression();
  void ExpressionToPolishNotation();
  void CalculatePolishNotation();
  void PrepareExpression();

  static bool IsDigit(char token) {
    bool result = false;
    if ((token >= '0' && token <= '9') || token == '.') {
      result = true;
    }
    return result;
  }

  static bool IsSign(char token) {
    bool result = false;
    if (token == '+' || token == '-' || token == '*' || token == '/' ||
        token == '^')
      result = true;
    return result;
  }

  static bool CheckFunction(type_t type) {
    bool result = false;
    for (type_t i = Cos; i <= Mod && !result; i = type_t(i + 1))
      if (type == i) result = true;
    return result;
  }

  static int GetPriority(char token) {
    int result = -2;
    if (IsDigit(token))
      result = -1;
    else if (token == '(' || token == ')')
      result = 0;
    else if (token == '+' || token == '-')
      result = 1;
    else if (token == '*' || token == '/')
      result = 2;
    else if (token == '^')
      result = 3;
    return result;
  }

  static type_t GetType(char token) {
    type_t result = Number;
    if (IsDigit(token))
      result = Number;
    else if (token == '+')
      result = Add;
    else if (token == '-')
      result = Sub;
    else if (token == '*')
      result = Mul;
    else if (token == '/')
      result = Div;
    else if (token == '(')
      result = OpenBracket;
    else if (token == ')')
      result = CloseBracket;
    else if (token == '^')
      result = Pow;
    return result;
  }

  static double CalculateOperation(double first, double second, type_t type) {
    double result = 0.0;
    switch (type) {
      case Add:
        result = second + first;
        break;
      case Sub:
        result = second - first;
        break;
      case Mul:
        result = second * first;
        break;
      case Div:
        result = second / first;
        break;
      case Mod:
        result = fmod(second, first);
        break;
      case Pow:
        if (first == 0.0)
          result = 1.0;
        else
          result = pow(second, first);
        break;
      default:
        break;
    }
    return result;
  }

  static double CalculateFunction(double first, type_t type) {
    double result = 0.0;
    switch (type) {
      case Sin:
        result = sin(first);
        break;
      case Cos:
        result = cos(first);
        break;
      case Tan:
        result = tan(first);
        break;
      case Asin:
        result = asin(first);
        break;
      case Acos:
        result = acos(first);
        break;
      case Atan:
        result = atan(first);
        break;
      case Sqrt:
        result = sqrt(first);
        break;
      case Ln:
        result = log(first);
        break;
      case Log:
        result = log10(first);
        break;
      default:
        break;
    }
    return result;
  }

  bool IsFunction(int *index, type_t *type) {
    bool result = false;
    if (strncmp(expression.c_str() + *index, "sin", 3) == 0) {
      *type = Sin;
      result = true;
      *index += 2;
    } else if (strncmp(expression.c_str() + *index, "cos", 3) == 0) {
      *type = Cos;
      result = true;
      *index += 2;
    } else if (strncmp(expression.c_str() + *index, "tan", 3) == 0) {
      *type = Tan;
      result = true;
      *index += 2;
    } else if (strncmp(expression.c_str() + *index, "acos", 4) == 0) {
      *type = Acos;
      result = true;
      *index += 3;
    } else if (strncmp(expression.c_str() + *index, "asin", 4) == 0) {
      *type = Asin;
      result = true;
      *index += 3;
    } else if (strncmp(expression.c_str() + *index, "atan", 4) == 0) {
      *type = Atan;
      result = true;
      *index += 3;
    } else if (strncmp(expression.c_str() + *index, "sqrt", 4) == 0) {
      *type = Sqrt;
      result = true;
      *index += 3;
    } else if (strncmp(expression.c_str() + *index, "ln", 2) == 0) {
      *type = Ln;
      result = true;
      *index += 1;
    } else if (strncmp(expression.c_str() + *index, "log", 3) == 0) {
      *type = Log;
      result = true;
      *index += 2;
    } else if (strncmp(expression.c_str() + *index, "mod", 3) == 0) {
      *type = Mod;
      result = true;
      *index += 2;
    }
    return result;
  }

  void print_to_calculate() {
    std::list<ModelParts> tmp(to_calculate);
    while (!tmp.empty()) {
      type_t type = tmp.back().type;
      switch (type) {
        case Number:
          std::cout << tmp.back().value;
          break;
        case Add:
          std::cout << "+";
          break;
        case Sub:
          std::cout << "-";
          break;
        case Mul:
          std::cout << "*";
          break;
        case Div:
          std::cout << "/";
          break;
        case Pow:
          std::cout << "^";
          break;
        case OpenBracket:
          break;
        case CloseBracket:
          break;
        case Cos:
          std::cout << "cos";
          break;
        case Sin:
          std::cout << "sin";
          break;
        case Tan:
          std::cout << "tan";
          break;
        case Acos:
          std::cout << "acos";
          break;
        case Asin:
          std::cout << "asin";
          break;
        case Atan:
          std::cout << "atan";
          break;
        case Sqrt:
          std::cout << "sqrt";
          break;
        case Ln:
          std::cout << "ln";
          break;
        case Log:
          std::cout << "log";
          break;
        case Mod:
          std::cout << "mod";
          break;
        default:
          break;
      }
      std::cout << " ";
      tmp.pop_back();
    }
    std::cout << "\n";
  }
};
}  // namespace s21
