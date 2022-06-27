#include "VIEW/calculatorView.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    CalculatorModel calc = CalculatorModel();
    DepositModel dep = DepositModel();
    CreditModel cred = CreditModel();
    GraphModel graph = GraphModel();
    CalculatorController controller(&calc, &dep, &cred, &graph);
    CalculatorView view(&controller);

    view.setFixedSize(630, 360);
    view.setWindowTitle("Smart Calc v2");
    view.show();

    return a.exec();
}
