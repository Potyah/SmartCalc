#include "creditView.h"
#include "ui_creditView.h"

CreditView::CreditView(CalculatorController *controller, QWidget *parent) : QDialog(parent),
                                                                             ui(new Ui::CreditWindow),
                                                                             _controller(controller) {
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
    setFixedSize(630, 360);
    ui->label_MonthlyPament ->setText("");
    ui->label_Overpayment ->setText("");
    ui->label_Total ->setText("");
    ui->doubleSpinBox_Sum->setRange(0, 100000000000);
    ui->spinBox_term->setRange(0, 1000000);
    ui->doubleSpinBox_rate->setRange(0, 100000000000);
}

CreditView::~CreditView() {
    delete ui;
}

void CreditView::on_pushButton_clicked() {
    double creditSum = ui->doubleSpinBox_Sum->value();
    int monthTerm = ui->spinBox_term->value();
    double interestRate = ui->doubleSpinBox_rate->value();
    int type = ui->comboBox_creditType->currentIndex();

    ui->label_MonthlyPament ->setText(_controller->getMonthlyPayment(creditSum, monthTerm,
                                                                     interestRate, type).c_str());
    ui->label_Overpayment ->setText(_controller->getCreditOverpayment(creditSum, monthTerm,
                                                                      interestRate, type).c_str());
    ui->label_Total ->setText(_controller->getTotalPayment(creditSum, monthTerm, interestRate, type).c_str());
}

void CreditView::on_pushButton_back_clicked() {
    emit signal();
    this->close();
}
