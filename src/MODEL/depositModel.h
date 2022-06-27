#ifndef SRC_MODEL_DEPOSITMODEL_H_
#define SRC_MODEL_DEPOSITMODEL_H_

#include <math.h>
#include <map>
#include <iostream>
#include <sstream>

class DepositModel {
 private:
    std::string _depositAmount;
    std::string _accruedInterest;
    std::string _taxAmount;
 public:
    void getDepositCalculations(double depositSum, int placementPeriod, double interestRate, double taxRate,
                                int paymentsPeriodicity, int interestCapitalization,
                                const std::map <int, double> &replenishment,
                                const std::map <int, double> &withdraw);

    void calculateReplenishmentAndWithdraw(double *depositSum, std::map<int, double> replenishment,
                                           std::map<int, double> withdraw, int month);

    std::string getDepositAmount();
    std::string getAccruedInterest();
    std::string getTaxAmount();

 private:
    std::string convertToString(const double & x);
    void setDepositAmount(double depositAmount);
    void setAccruedInterest(double accruedInterest);
    void setTaxAmount(double taxAmount);
};

#endif  //  SRC_MODEL_DEPOSITMODEL_H_
