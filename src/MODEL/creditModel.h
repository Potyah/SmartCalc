#ifndef SRC_MODEL_CREDITMODEL_H_
#define SRC_MODEL_CREDITMODEL_H_

#include <math.h>
#include <iostream>
#include <sstream>

class CreditModel {
 public:
    CreditModel() {}
    ~CreditModel() {}

    std::string getMonthlyPayment(double creditSum, int monthTerm, double interestRate, int type);
    std::string getCreditOverpayment(double creditSum, int monthTerm, double interestRate, int type);
    std::string getTotalPayment(double creditSum, int monthTerm, double interestRate, int type);

 private:
    double calculateAnnuityMonthlyPayment(double creditSum, int monthTerm, double interestRate);
    double calculateCreditOverpayment(double creditSum, int monthTerm, double interestRate, int type);
    double calculateTotalPayment(double creditSum, int monthTerm, double interestRate, int type);
    std::string convertToString(const double & x);
};

#endif  //  SRC_MODEL_CREDITMODEL_H_
