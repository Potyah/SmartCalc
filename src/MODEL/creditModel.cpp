#include "creditModel.h"

std::string CreditModel::convertToString(const double & x) {
    static std::ostringstream stream;
    stream.str("");
    stream.precision(2);
    stream << std::fixed << x;

    return stream.str();
}

std::string CreditModel::getMonthlyPayment(double creditSum, int monthTerm, double interestRate, int type) {
    if (!type) {
        return convertToString(calculateAnnuityMonthlyPayment(creditSum, monthTerm, interestRate));
    } else {
        double monthinterestRate = (interestRate / 12) * 1e-2;
        double first = (creditSum / monthTerm) + (creditSum * monthinterestRate);
        double last = first - (creditSum - ((creditSum / monthTerm))) * (interestRate / 12) * 1e-2;

        return convertToString(first) + "..." + convertToString(last);
    }
}

double CreditModel::calculateAnnuityMonthlyPayment(double creditSum, int monthTerm, double interestRate) {
    double monthinterestRate = (interestRate / 12) * 1e-2;
    return creditSum *((monthinterestRate * pow(1 + monthinterestRate, monthTerm))
                 / (pow(1 + monthinterestRate, monthTerm) -1));
}

std::string CreditModel::getCreditOverpayment(double creditSum, int monthTerm,
                                         double interestRate, int type) {
    return convertToString(calculateCreditOverpayment(creditSum, monthTerm, interestRate, type));
}

double CreditModel::calculateCreditOverpayment(double creditSum, int monthTerm,
                                               double interestRate, int type) {
    double result = 0;

    if (type == 0) {
        result = calculateAnnuityMonthlyPayment(creditSum, monthTerm, interestRate)
                * monthTerm - creditSum;
    } else {
        for (int i = 0; i < monthTerm; i++) {
            result += (creditSum - ((creditSum / monthTerm) * i)) * (interestRate / 12) * 1e-2;
        }
    }

    return result;
}

std::string CreditModel::getTotalPayment(double creditSum, int monthTerm,
                                         double interestRate, int type) {
    return convertToString(calculateTotalPayment(creditSum, monthTerm, interestRate, type));
}

double CreditModel::calculateTotalPayment(double creditSum, int monthTerm,
                                          double interestRate, int type) {
    double result = 0;

    if (type == 0) {
        result = creditSum + calculateCreditOverpayment(creditSum, monthTerm, interestRate, type);
    } else {
        for (int i = 0; i < monthTerm; i++) {
            result = creditSum + calculateCreditOverpayment(creditSum, monthTerm, interestRate, type);
        }
    }

    return result;
}
