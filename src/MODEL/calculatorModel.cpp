#include "calculatorModel.h"

std::string CalculatorModel::getResult() {
    return _result;
}

void CalculatorModel::setResult(const std::string &result) {
    _result = result;
}

std::stack <stack_type> CalculatorModel::getMainStack(const std::string &expression) {
    setlocale(LC_ALL, "POSIX");
    if (expression.size() > 256) {
        throw std::invalid_argument("Expression size must be < 256");
    }

    std::stack <stack_type> mainStack{};
    std::stack <stack_type> operatorStack{};

    for (size_t i = 0; i < expression.size(); i++) {
        if (!isNumber(expression, &i, &mainStack) &&
            !isX(expression, i, &mainStack) &&
            !isFunction(expression, &i, &operatorStack) &&
            !isOpenBracket(expression, i, &operatorStack) &&
            !isOperator(expression, &i, &mainStack, &operatorStack) &&
            !isCloseBracket(expression, i, &mainStack, &operatorStack)) {
                throw std::invalid_argument("Uncorrect expression");
        }
    }

    changeLastStackItems(&mainStack, &operatorStack);
    reverseStack(&mainStack);

    return mainStack;
}

void CalculatorModel::changeLastStackItems(std::stack <stack_type> *mainStack,
                                           std::stack <stack_type> *operatorStack) {
    while (!operatorStack->empty()) {
        std::string lexem = operatorStack->top().first;

        if (lexem == "(") {
            throw std::invalid_argument("Missing closing bracket");
        }

        if (operatorStack->top().second == 4 || operatorStack->top().second == 5) {
            mainStack->push({lexem.data(), 3});
        } else {
            mainStack->push({lexem.data(), 2});
        }

        operatorStack->pop();
    }
}

bool CalculatorModel::isCloseBracket(std::string expression, const size_t position,
                                     std::stack<stack_type> *postfixStack,
                                     std::stack<stack_type> *operatorStack) {
    if (expression[position] == ')' && !operatorStack->empty()) {
        if (position != expression.length() && (expression[position+1] == '('
                                                || isdigit(expression[position+1]))) {
            throw std::invalid_argument("Missing operator");
        }

        if (operatorStack->top().first != "(") {
            changeStackAfterCloseBracket(postfixStack, operatorStack);
        } else {
            operatorStack->pop();
        }

        return true;
    }

    return false;
}

void CalculatorModel::changeStackAfterCloseBracket(std::stack<stack_type> *mainStack,
                                                   std::stack<stack_type> *operatorStack) {
    if (!operatorStack->empty()) {
        std::string lexem = operatorStack->top().first;

        while (lexem != "(") {
            if (operatorStack->top().second == 4 || operatorStack->top().second == 5) {
                mainStack->push({lexem, 3});
            } else {
                mainStack->push({lexem, 2});
            }

            operatorStack->pop();

            if (!operatorStack->empty()) {
                lexem = operatorStack->top().first;
            } else {
                throw std::invalid_argument("Missing opening bracket");
            }
        }

        operatorStack->pop();

        if (!operatorStack->empty() && operatorStack->top().second == 5) {
            lexem = operatorStack->top().first;
            operatorStack->pop();
            mainStack->push({lexem, 3});
        }
    }
}

bool CalculatorModel::isOperator(std::string expression, size_t *position,
                                 std::stack<stack_type> *mainStack,
                                 std::stack<stack_type> *operatorStack) {
    if (expression[*position] == '+') {
        if (!isUnaryOpetator(expression, *position)) {
            stack_type data = {"+", 1};
            firstAndLastSymbolCheck(*position, expression.length() - 1);
            changeStackData(mainStack, operatorStack, data);
        }
    } else if (expression[*position] == '-') {
        if (isUnaryOpetator(expression, *position)) {
            bool minusFlag = true;

            for (int i = *position + 1; expression[i] == '-' || expression[i] == '+'; i++) {
                if (expression[i] == '-') {
                    minusFlag = !minusFlag;
                }

                *position += 1;
            }

            if (minusFlag) {
                stack_type data = {"~", 4};
                changeStackData(mainStack, operatorStack, data);
            }
        } else {
            stack_type data = {"-", 1};
            changeStackData(mainStack, operatorStack, data);
        }
    } else if (expression[*position] == '*' && isOperatorCheck(expression, *position-1)) {
        stack_type data = {"*", 2};
        firstAndLastSymbolCheck(*position, expression.length() - 1);
        changeStackData(mainStack, operatorStack, data);
    } else if (expression[*position] == '/' && isOperatorCheck(expression, *position-1)) {
        stack_type data = {"/", 2};
        firstAndLastSymbolCheck(*position, expression.length() - 1);
        changeStackData(mainStack, operatorStack, data);
    } else if (expression.find("mod") == *position && isOperatorCheck(expression, *position-1)) {
        stack_type data = {"mod", 2};
        firstAndLastSymbolCheck(*position, expression.length() - 1);
        changeStackData(mainStack, operatorStack, data);
        *position += 2;
    } else if (expression[*position] == '^' && isOperatorCheck(expression, *position-1)) {
        stack_type data = {"^", 3};
        firstAndLastSymbolCheck(*position, expression.length() - 1);
        changeStackData(mainStack, operatorStack, data);
    } else {
        return false;
    }

    return true;
}

void CalculatorModel::firstAndLastSymbolCheck(size_t currentSymbol, size_t length) {
    if (currentSymbol == 0) {
        throw std::invalid_argument("Operator cannot appear at the beginning of expression");
    }

    if (currentSymbol == length) {
        throw std::invalid_argument("Operator cannot appear at the ending of expression");
    }
}

bool CalculatorModel::isOperatorCheck(std::string expression, const size_t position) {
    if (expression[position ] == '+' || expression[position] == '-' ||
        expression[position] == '*' || expression[position] == '/' ||
        expression[position] == 'd' || expression[position] == '(' ||
        expression[position] == '^') {
            throw std::invalid_argument("Two operands in a row");
    }

    return true;
}

bool CalculatorModel::isUnaryOpetator(std::string infix, const size_t position) {
    return ((position == 0) || (infix[position - 1] == '(') || (infix[position - 1] == '+' ||
              infix[position - 1] == '-') || (infix[position - 1] != ')' &&
              infix[position - 1] != 'x' && !isdigit(infix[position - 1])));
}

void CalculatorModel::changeStackData(std::stack<stack_type> *mainStack,
                                      std::stack<stack_type> *operatorStack,
                                      stack_type data) {
    while (!operatorStack->empty() && operatorStack->top().second >= data.second &&
           operatorStack->top().first != "(") {
        std::string lexem = operatorStack->top().first;

        if (operatorStack->top().second == 4 || operatorStack->top().second == 5) {
            mainStack->push({lexem, 3});
        } else {
            mainStack->push({lexem, 2});
        }

        operatorStack->pop();

        if (!operatorStack->empty()) {
            lexem = operatorStack->top().first;
        }
    }

    operatorStack->push(data);
}

bool CalculatorModel::isNumber(std::string expression, size_t *position,
                               std::stack<stack_type> *mainStack) {
    if (isdigit(expression[*position])) {
        std::string lexem;
        parseNumber(expression, &lexem, position, false);

        if (expression[*position] == 'e') {
            parseExponent(expression, &lexem, position);
        }

        *position -= 1;
        mainStack->push({lexem, 0});
    } else if (expression.find("PI") == *position) {
        mainStack->push({"3.14159265358979323846", 0});
        *position += 1;
    } else {
        return false;
    }

    return true;
}

void CalculatorModel::parseNumber(std::string expression, std::string *lexem, size_t *position, bool pound) {
    while (isdigit(expression[*position]) || expression[*position] == '.') {
        if (expression[*position] == '.' && !pound) {
            pound = true;
        } else if (expression[*position] == '.' && pound) {
            throw std::invalid_argument("A number can have only one point");
        }

        lexem->push_back(expression[*position]);
        *position += 1;
    }
}

void CalculatorModel::parseExponent(std::string expression, std::string *lexem, size_t *position) {
    std::string order;
    long double result = 0;
    bool minus = false;

    *position += 1;

    if (expression[*position] == '-') {
        minus = true;
        *position += 1;
    }

    if (isdigit(expression[*position])) {
        parseNumber(expression, &order, position, true);
    }

    if (minus) {
        result = std::stold(*lexem) * pow(10, std::stold(order) * -1);
    } else {
        result = std::stold(*lexem) * pow(10, std::stold(order));
    }

    *lexem = std::to_string(result);
    cutZero(lexem);
}

bool CalculatorModel::isOpenBracket(std::string expression, const size_t position,
                                    std::stack<stack_type> *operatorStack) {
    if (expression[position] == '(') {
        checkCorrectOpenBracket(expression[position - 1], expression[position + 1], position);

        operatorStack->push({"(", 6});

        return true;
    }

    return false;
}

void CalculatorModel::checkCorrectOpenBracket(char prev, char next, const size_t position) {
    if (next == ')') {
        throw std::invalid_argument("Brackets cannot be empty");
    }

    if (position != 0 && isdigit(prev)) {
            throw std::invalid_argument("The opening bracket must be preceded by the operator");
    }
}

bool CalculatorModel::isFunction(std::string expression, size_t *position,
                                 std::stack<stack_type> *operatorStack) {
    std::string buff = expression.substr(*position);

    for (auto it = FUNCTIONS.begin(); it != FUNCTIONS.end(); it++) {
        if (buff.find(*it) == 0) {
            if ((expression[*position - 1] == ')' || isdigit(expression[*position - 1]))) {
                throw std::invalid_argument("Missing operator");
            }

            operatorStack->push({*it, 5});
            *position += it->length() - 1;

            if (expression[*position + 1] != '(') {
                throw std::invalid_argument("After function must be open bracket");
            }

            return true;
        }
    }

    return false;
}

void CalculatorModel::reverseStack(std::stack<stack_type> *srcStack) {
    std::stack<stack_type> dstStack{};

    while (!srcStack->empty()) {
        dstStack.push(srcStack->top());
        srcStack->pop();
    }

    *srcStack = std::move(dstStack);
}

void CalculatorModel::calculateExpression(std::stack <stack_type> mainStack) {
    std::stack<stack_type> resultStack{};

    while (!mainStack.empty()) {
        if (mainStack.top().second == 0) {
            resultStack.push(mainStack.top());
            mainStack.pop();
        } else if (mainStack.top().second == 2) {
            calculateWithBinaryOperator(&resultStack, &mainStack);
        } else if (mainStack.top().second == 3) {
            calculateWithFunction(&resultStack, &mainStack);
        }
    }

    setResult(resultStack.top().first);
}

void CalculatorModel::calculateWithFunction(std::stack<stack_type> *resultStack,
                                            std::stack<stack_type> *calculationStack) {
    long double doubleResult = stold(resultStack->top().first);
    resultStack->pop();

    if (calculationStack->top().first == "~") {
        doubleResult *= -1;
    } else if (calculationStack->top().first == "sin") {
       doubleResult = sin(doubleResult);
    } else if (calculationStack->top().first == "asin") {
       doubleResult = asin(doubleResult);
    } else if (calculationStack->top().first == "cos") {
        doubleResult = cos(doubleResult);
    } else if (calculationStack->top().first == "acos") {
        doubleResult = acos(doubleResult);
    } else if (calculationStack->top().first == "tan") {
        doubleResult = tan(doubleResult);
    } else if (calculationStack->top().first == "atan") {
        doubleResult = atan(doubleResult);
    } else if (calculationStack->top().first == "sqrt") {
        doubleResult = sqrt(doubleResult);
    } else if (calculationStack->top().first == "ln") {
        doubleResult = log(doubleResult);
    } else if (calculationStack->top().first == "log") {
        doubleResult = log10(doubleResult);
    }

    calculationStack->pop();
    resultStack->push({convertDoubleToString(doubleResult), 0});
}

void CalculatorModel::calculateWithBinaryOperator(std::stack<stack_type> *resultStack,
                                                  std::stack<stack_type> *calculationStack) {
    if (resultStack->size() >= 2) {
        long double number2 = stold(resultStack->top().first);
        resultStack->pop();
        long double number1 = stold(resultStack->top().first);
        resultStack->pop();
        long double doubleResult = 0;

        if (calculationStack->top().first == "+") {
            doubleResult = number1 + number2;
        } else if (calculationStack->top().first == "-") {
        doubleResult = number1 - number2;
        } else if (calculationStack->top().first == "*") {
            doubleResult = number1 * number2;
        } else if (calculationStack->top().first == "/") {
            doubleResult = number1 / number2;
        } else if (calculationStack->top().first == "mod") {
            doubleResult = fmod(number1, number2);
        } else if (calculationStack->top().first == "^") {
            doubleResult = pow(number1, number2);
        }

        calculationStack->pop();
        resultStack ->push({convertDoubleToString(doubleResult), 0});
    } else {
        throw std::invalid_argument("Uncorrect expression");
    }
}

std::string CalculatorModel::convertDoubleToString(long double result) {
    std::stringstream stream;
    stream.precision(9);
    stream << std::fixed;
    stream << result;
    std::string stringResult = stream.str();
    cutZero(&stringResult);
    return stringResult;
}

void CalculatorModel::cutZero(std::string *string) {
    while (string->back() == '0') {
        string->resize(string->length() - 1);

        if (string->back() == '.') {
            string->resize(string->length() - 1);
            break;
        }
    }

    if (*string == "-0") {
        *string = "0";
    }
}

std::string CalculatorModel::getX(const std::string &expression, double x) {
        std::stack<stack_type> mainStack = getMainStack(expression);
        std::string result = std::to_string(calculateExpressionWithX(mainStack, x));
        cutZero(&result);
        return result;
}

long double CalculatorModel::calculateExpressionWithX(std::stack<stack_type> copyStack, double x) {
    std::stack<stack_type> resultStack{};

    while (!copyStack.empty()) {
        if (copyStack.top().second == 0) {
            changeStackTopItem(&copyStack, x);
            resultStack.push(copyStack.top());
            copyStack.pop();
        } else if (copyStack.top().second == 2) {
            changeStackItems(&resultStack, x);
            calculateWithBinaryOperator(&resultStack, &copyStack);
        } else if (copyStack.top().second == 3) {
            changeStackTopItem(&resultStack, x);
            calculateWithFunction(&resultStack, &copyStack);
        }
    }

    return stold(resultStack.top().first);
}

void CalculatorModel::changeStackItems(std::stack<stack_type> *resultStack, double x) {
    changeStackTopItem(resultStack, x);

    stack_type bufferItem = resultStack->top();
    resultStack->pop();

    changeStackTopItem(resultStack, x);

    resultStack->push(bufferItem);
}

void CalculatorModel::changeStackTopItem(std::stack<stack_type> *resultStack, double x) {
    if (resultStack->top().first == "x") {
        resultStack->top().first = std::to_string(x);
    }
}

bool CalculatorModel::isX(std::string expression, const size_t position,
                          std::stack<stack_type> *mainStack) {
    if (expression[position] == 'x') {
        checkCorrectX(expression[position - 1], expression[position + 1]);
        mainStack->push({"x", 0});

        return true;
    }

    return false;
}

void CalculatorModel::checkCorrectX(char prev, char next) {
    if (isdigit(prev) || prev == 'x') {
        throw std::invalid_argument("Number cannot be before x");
    }

    if (isdigit(next) || next == 'x') {
        throw std::invalid_argument("Number cannot be after x");
    }
}
}
