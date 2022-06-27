#include "VIEW/calculatorView.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    s21::CalculatorModel calc = s21::CalculatorModel();
    s21::DepositModel dep = s21::DepositModel();
    s21::CreditModel cred = s21::CreditModel();
    s21::GraphModel graph = s21::GraphModel();
    s21::CalculatorController controller(&calc, &dep, &cred, &graph);
    CalculatorView view(&controller);

    view.setFixedSize(630, 360);
    view.setWindowTitle("Smart Calc v2");
    view.show();

    return a.exec();
}
