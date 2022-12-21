#include "engineermodel.h"

bool s21::EngineerModel::CheckForCorrectExpression() {
  std::size_t count_open_brackets = 0u, count_close_brackets = 0u;
  for (auto x : expression) {
    switch (x) {
      case '(':
        count_open_brackets += 1;
        break;
      case ')':
        count_close_brackets += 1;
        break;
      default:
        break;
    }
  }
  return count_close_brackets == count_open_brackets;
}

void s21::EngineerModel::ExpressionToPolishNotation() {
  std::list<ModelParts> output_list;
  std::list<ModelParts> functions_list;

  for (auto i = 0; (std::size_t)i != expression.size(); ++i) {
    char token = expression[i];
    type_t type = Number;
    if (token == 'x') {
      output_list.push_back({x_value, -1, Number});
    } else if (IsDigit(token)) {
      std::string value(1, token);
      while (IsDigit(expression[++i])) value.push_back(expression[i]);
      double number = std::stod(value);
      output_list.push_back({number, GetPriority(token), Number});
      i--;
    } else if (token == '(') {
      functions_list.push_back({'(', GetPriority(token), GetType(token)});

    } else if (IsFunction(&i, &type)) {
      functions_list.push_back({double(type), 4, type});
    } else if (IsSign(token)) {
      while (!functions_list.empty() &&
             functions_list.back().priority >= GetPriority(token)) {
        output_list.push_back(functions_list.back());
        functions_list.pop_back();
      }
      functions_list.push_back(
          {double(token), GetPriority(token), GetType(token)});
    } else if (token == ')') {
      while (functions_list.back().type != OpenBracket) {
        output_list.push_back(functions_list.back());
        functions_list.pop_back();
      }
      functions_list.pop_back();
      if (!functions_list.empty()) {
        type_t function = functions_list.back().type;
        if (CheckFunction(function)) {
          output_list.push_back(functions_list.back());
          functions_list.pop_back();
        }
      }
    }
  }
  while (!functions_list.empty()) {
    type_t function = functions_list.back().type;
    if (CheckFunction(function)) {
      output_list.push_back(functions_list.back());
      functions_list.pop_back();
    } else {
      output_list.push_back(functions_list.back());
      functions_list.pop_back();
    }
  }
  to_calculate = output_list;
  to_calculate.reverse();
}

void s21::EngineerModel::CalculatePolishNotation() {
  std::list<ModelParts> function_list;
  print_to_calculate();
  while (!to_calculate.empty()) {
    type_t type = to_calculate.back().type;
    if (type == Number) {
      function_list.push_back(to_calculate.back());
    } else {
      double first = function_list.back().value;
      function_list.pop_back();
      if (type >= Cos && type <= Log) {
        function_list.push_back({CalculateFunction(first, type), -1, Number});
      }
      if ((type >= Add && type <= Pow) || type == Mod) {
        double second = function_list.back().value;
        function_list.pop_back();
        function_list.push_back(
            {CalculateOperation(first, second, type), -1, Number});
      }
    }
    to_calculate.pop_back();
  }
  answer = function_list.back().value;
  function_list.pop_back();
}

void s21::EngineerModel::PrepareExpression() {
  std::string prepared;
  for (auto i = 0; (std::size_t)i != expression.size(); ++i) {
    char token = expression[i];
    if (token == '-' || token == '+') {
      if (i == 0 || expression[i - 1] == '(') prepared.push_back('0');
    }

    if (token == 'e') {
      std::string value;
      if (expression[i + 1] == '-') {
        i += 2;
        while (isdigit(expression[i])) {
          value.push_back(expression[i]);
          i++;
        }
        if (value.front() == '0' && value.size() != 1u)
          value.erase(value.begin());
        prepared += "*10^(0-" + value + ")";
      } else if (expression[i + 1] == '+') {
        i += 2;
        while (isdigit(expression[i])) {
          value.push_back((expression[i]));
          i++;
        }
        if (value.front() == '0' && value.size() != 1u)
          value.erase(value.begin());
        prepared += "*10^(" + value + ")";
      }
      i -= 1;
    }
    prepared.push_back(token);
  }
  expression.swap(prepared);
}
