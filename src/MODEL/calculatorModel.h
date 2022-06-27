#ifndef SRC_MODEL_CALCULATORMODEL_H_
#define SRC_MODEL_CALCULATORMODEL_H_

#include <stack>
#include <cmath>
#include <iostream>
#include <sstream>
#include <array>

#define PI 3.14159265358979323846

using stack_type = std::pair<std::string, int>;
const std::array<std::string, 9> FUNCTIONS = {"atan", "asin", "acos", "sqrt", "sin",
                                              "cos", "tan", "ln", "log" };
class CalculatorModel {
 private:
    std::string _result;

    void setResult(const std::string &result);

    bool isNumber(std::string expression, size_t *position, std::stack<stack_type> *mainStack);
    bool isFunction(std::string expression, size_t *position, std::stack<stack_type> *operatorStack);
    bool isOperator(std::string expression, size_t *position, std::stack<stack_type> *mainStack,
                    std::stack<stack_type> *operatorStack);
    bool isOperatorCheck(std::string expression, const size_t position);
    bool isUnaryOpetator(std::string expression, const size_t position);
    bool isCloseBracket(std::string expression, const size_t position,
                        std::stack<stack_type> *mainStack, std::stack<stack_type> *operatorStack);
    bool isOpenBracket(std::string expression, const size_t position, std::stack<stack_type>  *operatorStack);
    bool isX(std::string expression, const size_t position, std::stack<stack_type>  *mainStack);

    void checkCorrectOpenBracket(char prev, char next, const size_t position);
    void parseNumber(std::string expression, std::string *lexem, size_t *position, bool pound);
    void parseExponent(std::string expression, std::string *lexem, size_t *position);
    void reverseStack(std::stack<stack_type> *srcStack);
    void firstAndLastSymbolCheck(size_t currentSymbol, size_t length);
    void checkCorrectX(char prev, char next);
    void changeStackItems(std::stack<stack_type> *resultStack, double x);
    void changeStackTopItem(std::stack<stack_type> *resultStack, double x);
    void changeStackData(std::stack<stack_type> *mainStack, std::stack<stack_type> *operatorStack,
                         stack_type data);
    void changeStackAfterCloseBracket(std::stack<stack_type> *mainStack,
                                      std::stack<stack_type> *operatorStack);
    void changeLastStackItems(std::stack<stack_type>  *mainStack, std::stack<stack_type>  *operatorStack);
    void calculateWithBinaryOperator(std::stack<stack_type> *resultStack,
                                     std::stack<stack_type>  *calculationStack);
    void calculateWithFunction(std::stack<stack_type>  *resultStack,
                               std::stack<stack_type>  *calculationStack);
    void cutZero(std::string *string);
    std::string convertDoubleToString(long double result);

 public:
    CalculatorModel() {}
    ~CalculatorModel() {}

    std::string getResult();
    long double  calculateExpressionWithX(std::stack<stack_type> copyStack, double x);
    void calculateExpression(std::stack <stack_type> mainStack);
    std::stack <stack_type> getMainStack(const std::string &expression);
    std::string getX(const std::string &expression, double x);
};

#endif  //  SRC_MODEL_CALCULATORMODEL_H_
