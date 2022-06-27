#ifndef SRC_CONTROLLER_CALCULATORCONTROLLER_H_
#define SRC_CONTROLLER_CALCULATORCONTROLLER_H_

#include "../MODEL/calculatorModel.h"
#include "../MODEL/creditModel.h"
#include "../MODEL/depositModel.h"
#include "../MODEL/graphModel.h"

class CalculatorController {
 private:
        CalculatorModel *calculatorModel;
        DepositModel *depositModel;
        CreditModel *creditModel;
        GraphModel *graphModel;

 public:
        explicit CalculatorController(CalculatorModel *calc, DepositModel *dp,
                                      CreditModel *cr, GraphModel *gr)
            : calculatorModel(calc), depositModel(dp), creditModel(cr), graphModel(gr) {}
        ~CalculatorController() {}

        std::string calculateExpression(const std::string &expression);
        std::string getEquationResult(const std::string &expression, double x);

        std::string getMonthlyPayment(double creditSum, int monthTerm, double interestRate, int type);
        std::string getCreditOverpayment(double creditSum, int monthTerm, double interestRate, int type);
        std::string getTotalPayment(double creditSum, int monthTerm, double interestRate, int type);

        void getDepositCalculations(double depositSum, int placementPeriod,
                        double interestRate, double taxRate,
                        int paymentsPeriodicity, int interestCapitalization,
                        const std::map<int, double> &replenishment,
                        const std::map<int, double> &withdraw);
        std::string getDepositAmount();
        std::string getAccruedInterest();
        std::string getTaxAmount();

        void getGraphCalculations(double step, int from, int to, const std::string &expression);
        std::vector<double> getVectorX();
        std::vector<double> getVectorY();
};

#endif  //  SRC_CONTROLLER_CALCULATORCONTROLLER_H_
