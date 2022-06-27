#include "depositModel.h"

std::string DepositModel::convertToString(const double & x) {
    static std::ostringstream stream;
    stream.str("");
    stream.precision(2);
    stream << std::fixed << x;

    return stream.str();
}

void DepositModel::getDepositCalculations(double depositSum, int placementPeriod,
                                          double interestRate, double taxRate,
                                          int paymentsPeriodicity, int interestCapitalization,
                                          const std::map <int, double> &replenishment,
                                          const std::map <int, double> &withdraw) {
    interestRate *= 1e-2;
    double depositAmount = 0;
    double accruedInterest = 0;
    double taxAmount = 0;

    if (interestCapitalization == 0) {
        for (int i = 1; i <= placementPeriod; i++) {
            calculateReplenishmentAndWithdraw(&depositSum, replenishment, withdraw, i);
            accruedInterest += interestRate / 12.0 * depositSum;
        }

        depositAmount = accruedInterest + depositSum;
    } else {
        int lastpay = 0;

        for (int i = 1; i <= placementPeriod; i++) {
            calculateReplenishmentAndWithdraw(&depositSum, replenishment, withdraw, i);

            if (i % paymentsPeriodicity == 0) {
                accruedInterest += (interestRate / 12.0) * paymentsPeriodicity *
                (depositSum + accruedInterest);
                lastpay = i;
            } else if (i == placementPeriod) {
                accruedInterest += (interestRate / 12.0) * (i - lastpay) * (depositSum + accruedInterest);
            }
        }

        depositAmount = accruedInterest + depositSum;
    }

    double nonTaxableIncomeSum = 1000000 * 0.2;

    if (accruedInterest > nonTaxableIncomeSum) {
        double sumDifference = accruedInterest - nonTaxableIncomeSum;
        taxAmount = sumDifference * (taxRate * 1e-2);
    } else {
        taxAmount = 0;
    }

    if (depositAmount < 0) {
        _accruedInterest = "Withdraw can`t";
        _taxAmount = "more than";
        _depositAmount = "you have deposited";
    } else {
        setDepositAmount(depositAmount - taxAmount);
        setAccruedInterest(accruedInterest);
        setTaxAmount(taxAmount);
    }
}

void DepositModel::calculateReplenishmentAndWithdraw(double *depositSum, std::map<int, double> replenishment,
                                                     std::map<int, double> withdraw, int month) {
    if (replenishment.count(month) != 0) {
        *depositSum += replenishment.at(month);
    }

    if (withdraw.count(month) != 0) {
        *depositSum -= withdraw.at(month);
    }
}

std::string DepositModel::getDepositAmount() {
    return _depositAmount;
}

std::string DepositModel::getAccruedInterest() {
    return _accruedInterest;
}

std::string DepositModel::getTaxAmount() {
    return _taxAmount;
}

void DepositModel::setDepositAmount(double depositAmount) {
    _depositAmount = convertToString(depositAmount);
}

void DepositModel::setAccruedInterest(double accruedInterest) {
    _accruedInterest = convertToString(accruedInterest);
}

void DepositModel::setTaxAmount(double taxAmount) {
    _taxAmount = convertToString(taxAmount);
}
