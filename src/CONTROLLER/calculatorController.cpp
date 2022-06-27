#include "calculatorController.h"

//  ---------calc-------
std::string CalculatorController::calculateExpression(const std::string &expression) {
    try {
        calculatorModel->calculateExpression(calculatorModel->getMainStack(expression));
        return calculatorModel->getResult();
    } catch (const std::exception& e) {
        return e.what();
    }
}

std::string CalculatorController::getEquationResult(const std::string &expression, double x) {
    try {
        return calculatorModel->getX(expression, x);
    } catch (const std::exception& e) {
        return e.what();
    }
}

//  -------credit---------
std::string CalculatorController::getMonthlyPayment(double creditSum, int monthTerm,
                                                    double interestRate, int type) {
    return creditModel->getMonthlyPayment(creditSum, monthTerm, interestRate, type);
}

std::string CalculatorController::getCreditOverpayment(double creditSum, int monthTerm,
                                              double interestRate, int type) {
    return creditModel->getCreditOverpayment(creditSum, monthTerm, interestRate, type);
}

std::string CalculatorController::getTotalPayment(double creditSum, int monthTerm,
                                                  double interestRate, int type) {
    return creditModel->getTotalPayment(creditSum, monthTerm, interestRate, type);
}

//  ---------deposit--------
void CalculatorController::getDepositCalculations(double depositSum, int placementPeriod,
                                                    double interestRate, double taxRate,
                                                    int paymentsPeriodicity, int interestCapitalization,
                                                    const std::map<int, double> &replenishment,
                                                    const std::map<int, double> &withdraw) {
    depositModel->getDepositCalculations(depositSum, placementPeriod, interestRate, taxRate,
                                paymentsPeriodicity, interestCapitalization,
                                replenishment, withdraw);
}

std::string CalculatorController::getDepositAmount() {
    return depositModel->getDepositAmount();
}

std::string CalculatorController::getAccruedInterest() {
    return depositModel->getAccruedInterest();
}

std::string CalculatorController::getTaxAmount() {
    return depositModel->getTaxAmount();
}

//  ----------graph--------
void CalculatorController::getGraphCalculations(double step, int from, int to,
                                                const std::string &expression) {
    graphModel->fillVectors(step, from, to, expression);
}

std::vector<double> CalculatorController::getVectorX() {
    return graphModel->getVectorX();
}

std::vector<double> CalculatorController::getVectorY() {
    return graphModel->getVectorY();
}
