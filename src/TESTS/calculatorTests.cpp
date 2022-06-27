#include "../CONTROLLER/calculatorController.h"
#include <gtest/gtest.h>

s21::CalculatorModel calc = s21::CalculatorModel();
s21::DepositModel dep = s21::DepositModel();
s21::CreditModel cred = s21::CreditModel();
s21::GraphModel graph = s21::GraphModel();
s21::CalculatorController controller(&calc, &dep, &cred, &graph);

namespace s21 {
//-------Bracket tests-------
TEST(calcTest, test1_bracket) {
    std::string expression = "(1)";
    ASSERT_EQ(controller.calculateExpression(expression), "1");
}

TEST(calcTest, test2_bracket) {
    std::string expression = "((1))";
    ASSERT_EQ(controller.calculateExpression(expression), "1");
}

TEST(calcTest, test3_bracket) {
    std::string expression = "((1)+7)";
    ASSERT_EQ(controller.calculateExpression(expression), "8");
}

TEST(calcTest, test4_bracket) {
    std::string expression = "4*(1+7)";
    ASSERT_EQ(controller.calculateExpression(expression), "32");
}

TEST(calcTest, test5_bracket) {
    std::string expression = "-4*(1+(7))";
    ASSERT_EQ(controller.calculateExpression(expression), "-32");
}

TEST(calcTest, test6_bracket) {
    std::string expression = "-4*(1+(7))+2";
    ASSERT_EQ(controller.calculateExpression(expression), "-30");
}

TEST(calcTest, test7_bracket) {
    std::string expression = "-4*()";
    ASSERT_EQ(controller.calculateExpression(expression), "Brackets cannot be empty");
}

TEST(calcTest, test8_bracket) {
    std::string expression = "-4(45)";
    ASSERT_EQ(controller.calculateExpression(expression), "The opening bracket must be preceded by the operator");
}

TEST(calcTest, test10_bracket) {
    std::string expression = "-445)";
    ASSERT_EQ(controller.calculateExpression(expression), "Missing opening bracket");
}

TEST(calcTest, test11_bracket) {
    std::string expression = "-4*(445";
    ASSERT_EQ(controller.calculateExpression(expression), "Missing closing bracket");
}

TEST(calcTest, test12_bracket) {
    std::string expression = "(1)(1)";
    ASSERT_EQ(controller.calculateExpression(expression), "Missing operator");
}

TEST(calcTest, test13_bracket) {
    std::string expression = "(1)1";
    ASSERT_EQ(controller.calculateExpression(expression), "Missing operator");
}

TEST(calcTest, test14_bracket) {
    std::string expression = "sin(1)5";
    ASSERT_EQ(controller.calculateExpression(expression), "Missing operator");
}

//-------Sum tests-------
TEST(calcTest, test1_sum) {
    std::string expression = "-4+2";
    ASSERT_EQ(controller.calculateExpression(expression), "-2");
}

TEST(calcTest, test2_sum) {
    std::string expression = "((4+2)+(5+3))";
    ASSERT_EQ(controller.calculateExpression(expression), "14");
}

TEST(calcTest, test3_sum) {
    std::string expression = "+4+2+5+3";
    ASSERT_EQ(controller.calculateExpression(expression), "14");
}

TEST(calcTest, test4_sum) {
    std::string expression = "4+-2";
    ASSERT_EQ(controller.calculateExpression(expression), "2");
}

TEST(calcTest, test5_sum) {
    std::string expression = "+4+-2";
    ASSERT_EQ(controller.calculateExpression(expression), "2");
}

//-------Diff tests-------
TEST(calcTest, test1_diff) {
    std::string expression = "4-2.5";
    ASSERT_EQ(controller.calculateExpression(expression), "1.5");
}

TEST(calcTest, test2_diff) {
    std::string expression = "-4-(-2.5-0.75)--5";
    ASSERT_EQ(controller.calculateExpression(expression), "4.25");
}

TEST(calcTest, test3_diff) {
    std::string expression = "-4--5";
    ASSERT_EQ(controller.calculateExpression(expression), "1");
}

TEST(calcTest, test4_diff) {
    std::string expression = "4-+5.5555";
    ASSERT_EQ(controller.calculateExpression(expression), "-1.5555");
}

//-------Mult tests-------
TEST(calcTest, test1_mult) {
    std::string expression = "+4*-5.5555";
    ASSERT_EQ(controller.calculateExpression(expression), "-22.222");
}

TEST(calcTest, test2_mult) {
    std::string expression = "4.456*0";
    ASSERT_EQ(controller.calculateExpression(expression), "0");

}

TEST(calcTest, test3_mult) {
    std::string expression = "0*0*0";
    ASSERT_EQ(controller.calculateExpression(expression), "0");
}

TEST(calcTest, test4_mult) {
    std::string expression = "3*(6+8.54)-(3.43*4.5)";
    ASSERT_EQ(controller.calculateExpression(expression), "28.185");
}

//-------Exp tests-------
TEST(calcTest, test1_exp) {
    std::string expression = "2*(1e-3+7)";
    ASSERT_EQ(controller.calculateExpression(expression), "14.002");
}

TEST(calcTest, test2_exp) {
    std::string expression = "2*(0.01e3+7)";
    ASSERT_EQ(controller.calculateExpression(expression), "34");
}

//-------Div tests-------
TEST(calcTest, test1_div) {
    std::string expression = "3*(6+8.54)/(3.43*4.5)";
    ASSERT_EQ(controller.calculateExpression(expression), "2.826044704");
}

TEST(calcTest, test2_div) {
    std::string expression = "3/(1)";
    ASSERT_EQ(controller.calculateExpression(expression), "3");
}

TEST(calcTest, test3_div) {
    std::string expression = "3.4567/2*0.7";
    ASSERT_EQ(controller.calculateExpression(expression), "1.209845");
}

//-------Pow tests-------
TEST(calcTest, test1_pow) {
    std::string expression = "3.4567^0.7";
    ASSERT_EQ(controller.calculateExpression(expression), "2.382666083");
}

TEST(calcTest, test2_pow) {
    std::string expression = "3*(6+8.54)/(3.43*4.5)^3.2";
    ASSERT_EQ(controller.calculateExpression(expression), "0.006862217");
}

TEST(calcTest, test3_pow) {
    std::string expression = "3^0";
    ASSERT_EQ(controller.calculateExpression(expression), "1");
}

//-------Mod tests-------
TEST(calcTest, test1_mod) {
    std::string expression = "3mod1";
    ASSERT_EQ(controller.calculateExpression(expression), "0");
}

TEST(calcTest, test2_mod) {
    std::string expression = "3mod4";
    ASSERT_EQ(controller.calculateExpression(expression), "3");
}

//-------Cos tests-------
TEST(calcTest, test1_cos) {
    std::string expression = "-cos(PI/2)";
    ASSERT_EQ(controller.calculateExpression(expression), "0");
}

TEST(calcTest, test2_cos) {
    std::string expression = "cos(0)";
    ASSERT_EQ(controller.calculateExpression(expression), "1");
}

TEST(calcTest, test3_cos) {
    std::string expression = "cos(PI/3)";
    ASSERT_EQ(controller.calculateExpression(expression), "0.5");
}

//-------Sin tests-------
TEST(calcTest, test1_sin) {
    std::string expression = "sin(PI/6)";
    ASSERT_EQ(controller.calculateExpression(expression), "0.5");
}

TEST(calcTest, test2_sin) {
    std::string expression = "sin(0)";
    ASSERT_EQ(controller.calculateExpression(expression), "0");
}

//-------Tan tests-------
TEST(calcTest, test1_tan) {
    std::string expression = "tan(PI)";
    ASSERT_EQ(controller.calculateExpression(expression), "0");
}

//-------Atan tests-------
TEST(calcTest, test1_atan) {
    std::string expression = "atan(tan(PI/4))";
    ASSERT_EQ(controller.calculateExpression(expression), "0.785398163");
}

//-------Asin tests-------
TEST(calcTest, test1_asin) {
    std::string expression = "-asin(-1)";
    ASSERT_EQ(controller.calculateExpression(expression), "1.570796327");
}

TEST(calcTest, test2_asin) {
    std::string expression = "asin(0)";
    ASSERT_EQ(controller.calculateExpression(expression), "0");
}

//-------Acos tests-------
TEST(calcTest, test1_acos) {
    std::string expression = "acos(-1)";
    ASSERT_EQ(controller.calculateExpression(expression), "3.141592654");
}

TEST(calcTest, test2_acos) {
    std::string expression = "acos(0)";
    ASSERT_EQ(controller.calculateExpression(expression), "1.570796327");
}

//-------Sqrt tests-------
TEST(calcTest, test1_sqrt) {
    std::string expression = "sqrt(3*(6+8.54)/(3.43*4.5))";
    ASSERT_EQ(controller.calculateExpression(expression), "1.681084383");
}

TEST(calcTest, test2_sqrt) {
    std::string expression = "sqrt(sqrt(3/1))";
    ASSERT_EQ(controller.calculateExpression(expression), "1.316074013");
}

//-------Log tests-------
TEST(calcTest, test1_log) {
    std::string expression = "log(3.4567/2*0.7)";
    ASSERT_EQ(controller.calculateExpression(expression), "0.082729734");
}

//-------Ln tests-------
TEST(calcTest, test1_ln) {
    std::string expression = "ln(3.4567/2*0.7)";
    ASSERT_EQ(controller.calculateExpression(expression), "0.190492252");
}

//-------Unary tests-------
TEST(calcTest, test1_unary) {
    std::string expression = "--7+6";
    ASSERT_EQ(controller.calculateExpression(expression), "13");
}

TEST(calcTest, test2_unary) {
    std::string expression = "---5+---+6";
    ASSERT_EQ(controller.calculateExpression(expression), "-11");
}

//-------Fail tests-------
TEST(failTest, test1_fail) {
    std::string expression = "4.346-5+";
    ASSERT_EQ(controller.calculateExpression(expression), "Operator cannot appear at the ending of expression");
}

TEST(failTest, test2_fail) {
    std::string expression = "*5+6*34";
    ASSERT_EQ(controller.calculateExpression(expression), "Operator cannot appear at the beginning of expression");
}

TEST(failTest, test3_fail) {
    std::string expression = "5,5+5.6";
    ASSERT_EQ(controller.calculateExpression(expression), "Uncorrect expression");
}

TEST(failTest, test7_fail) {
    std::string expression = "5*sin5-cos(PI)";
    ASSERT_EQ(controller.calculateExpression(expression), "After function must be open bracket");
}

TEST(failTest, test8_fail) {
    std::string expression = "5.3.3*-cos(PI)";
    ASSERT_EQ(controller.calculateExpression(expression), "A number can have only one point");
}

TEST(failTest, test9_fail) {
    std::string expression = "5.3*/-cos(PI)";
    ASSERT_EQ(controller.calculateExpression(expression), "Two operands in a row");
}

TEST(failTest, test10_fail) {
    std::string expression = "1e256";
    ASSERT_EQ(controller.calculateExpression(controller.calculateExpression(expression) + "1"), "Expression size must be < 256");
}

TEST(failTest, test11_fail) {
    std::string expression = "sin(1)cos(1)";
    ASSERT_EQ(controller.calculateExpression(controller.calculateExpression(expression)), "Uncorrect expression");
}

TEST(failTest, test12_fail) {
    std::string expression = "56cos(1)";
    ASSERT_EQ(controller.calculateExpression(controller.calculateExpression(expression)), "Uncorrect expression");
}

TEST(failTest, test13_fail) {
    std::string expression = "6++";
    ASSERT_EQ(controller.calculateExpression(controller.calculateExpression(expression)), "Uncorrect expression");
}

//-------X tests-------
TEST(xTest, test1_x) {
    std::string expression = "(x)";
    ASSERT_EQ(controller.getEquationResult(expression, 7.456), "7.456");
}

TEST(xTest, test2_x) {
    std::string expression = "x+x*2-x*-3";
    ASSERT_EQ(controller.getEquationResult(expression, 4), "24");
}

TEST(xTest, test3_x) {
    std::string expression = "5x";
    ASSERT_EQ(controller.getEquationResult(expression, 4), "Number cannot be before x");
}

TEST(xTest, test4_x) {
    std::string expression = "x5";
    ASSERT_EQ(controller.getEquationResult(expression, 4), "Number cannot be after x");
}

TEST(xTest, test5_x) {
    std::string expression = "7*32353+xx";
    ASSERT_EQ(controller.getEquationResult(expression, 4), "Number cannot be after x");
}

TEST(xTest, test6_x) {
    std::string expression = "7*32353+X";
    ASSERT_EQ(controller.getEquationResult(expression, 4), "Uncorrect expression");
}

//-------Vector tests-------
TEST(vectorTest, test1_vector) {
    std::string expression = "x*2";
    controller.getGraphCalculations(1, 5, 8, expression);
    ASSERT_EQ(*controller.getVectorX().begin(), 5);
    ASSERT_EQ(*--controller.getVectorX().end(), 7);
    ASSERT_EQ(*controller.getVectorY().begin(), 10);
    ASSERT_EQ(*--controller.getVectorY().end(), 14);
}

//-------Credit tests-------
TEST(creditTest, test1_credit) {
    ASSERT_EQ(controller.getMonthlyPayment(100000, 6, 6, 0), "16959.55");
    ASSERT_EQ(controller.getCreditOverpayment(100000, 6, 6, 0), "1757.27");
    ASSERT_EQ(controller.getTotalPayment(100000, 6, 6, 0), "101757.27");
}

TEST(creditTest, test2_credit) {
    ASSERT_EQ(controller.getMonthlyPayment(100000, 6, 6, 1), "17166.67...16750.00");
    ASSERT_EQ(controller.getCreditOverpayment(100000, 6, 6, 1), "1750.00");
    ASSERT_EQ(controller.getTotalPayment(100000, 6, 6, 1), "101750.00");
}

//-------Deposit tests-------
TEST(depositTest, test1_deposit) {
    std::map<int, double> replenishment = {{1, 300}};
    std::map<int, double> withdraw = {{2, 800}};
    controller.getDepositCalculations(100000, 12, 20, 13, 12, 1, replenishment, withdraw);

    ASSERT_EQ(controller.getAccruedInterest(), "19900.00");
    ASSERT_EQ(controller.getDepositAmount(), "119400.00");
    ASSERT_EQ(controller.getTaxAmount(), "0.00");
}

TEST(depositTest, test2_deposit) {
    std::map<int, double> replenishment = {{1, 300}};
    std::map<int, double> withdraw = {{2, 800}};
    controller.getDepositCalculations(10000000000000, 12, 20, 13, 12, 0, replenishment, withdraw);

    ASSERT_EQ(controller.getAccruedInterest(), "1999999999913.33");
    ASSERT_EQ(controller.getDepositAmount(), "11740000025424.60");
    ASSERT_EQ(controller.getTaxAmount(), "259999973988.73");
}

TEST(depositTest, test3_deposit) {
    std::map<int, double> replenishment = {{1, 300}};
    std::map<int, double> withdraw = {{2, 100000000}};
    controller.getDepositCalculations(100000, 12, 20, 13, 12, 1, replenishment, withdraw);

    ASSERT_EQ(controller.getAccruedInterest(), "Withdraw can`t");
    ASSERT_EQ(controller.getTaxAmount(), "more than");
    ASSERT_EQ(controller.getDepositAmount(), "you have deposited");
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
}
