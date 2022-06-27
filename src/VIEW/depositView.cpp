#include "depositView.h"
#include "ui_depositView.h"

DepositView::DepositView(s21::CalculatorController *controller, QWidget *parent) : QDialog(parent),
                                                                            ui(new Ui::DepositView),
                                                                            _controller(controller) {
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
    setFixedSize(630, 360);
    ui->label_accuredInserts ->setText("");
    ui->label_depositAmount ->setText("");
    ui->label_taxAmount ->setText("");
    ui->doubleSpinBox_depositSum->setRange(0, 100000000000);
    ui->doubleSpinBox_interestRate->setRange(0, 100000000000);
    ui->spinBox_placementPeriod->setRange(0, 1000000);
    ui->doubleSpinBox_taxRate->setRange(0, 100000000000);
    paymentsPeriodicity = 1;
}

DepositView::~DepositView() {
    delete ui;
}

void DepositView::on_pushButton_clicked() {
    double depositSum = ui->doubleSpinBox_depositSum->value();
    double interestRate = ui->doubleSpinBox_interestRate->value();
    double taxRate = ui->doubleSpinBox_taxRate->value();
    int placementPeriod = ui->spinBox_placementPeriod->value();
    int interestCapitalization = ui->comboBox_capitalization->currentIndex();

    _controller->getDepositCalculations(depositSum, placementPeriod, interestRate, taxRate,
                                 paymentsPeriodicity, interestCapitalization,
                                 replenishment, withdrawal);
    ui->label_depositAmount ->setText(QString::fromStdString(_controller->getDepositAmount()));
    ui->label_accuredInserts ->setText(QString::fromStdString(_controller->getAccruedInterest()));
    ui->label_taxAmount ->setText(QString::fromStdString(_controller->getTaxAmount()));
}

void DepositView::on_pushButton_replenishment_clicked() {
    if (ui->spinBox_placementPeriod->value() != 0) {
       createAddWindow(&replenishment);
    }
}

void DepositView::on_pushButton_withdrawal_clicked() {
    if (ui->spinBox_placementPeriod->value() != 0) {
       createAddWindow(&withdrawal);
    }
}

void DepositView::createAddWindow(std::map<int, double> *dataMap) {
    QDialog dialog(this);
    QFormLayout form(&dialog);

    form.addRow(new QLabel("Enter data"));

    QDoubleSpinBox *lineSum = new QDoubleSpinBox(&dialog);
    QString labelSum = QString("Sum");
    lineSum->setRange(0, 100000000000);
    form.addRow(labelSum, lineSum);

    QSpinBox *lineMonth = new QSpinBox(&dialog);
    QString labelMonth = QString("Month");
    lineMonth->setRange(0, 10000000);
    form.addRow(labelMonth, lineMonth);

    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
    Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));
    QMessageBox msgBox;

    if (dialog.exec() == QDialog::Accepted && (lineSum->value() != 0 &&
                                               lineMonth->value() != 0 &&
                                               lineMonth->value() < ui->spinBox_placementPeriod->value())) {
        dataMap->insert({lineMonth->value(), lineSum->value()});
    } else {
        QMessageBox msgeBox;
        msgeBox.setText("Attention!");
        msgeBox.setInformativeText("You enter invalid data");
        msgeBox.setStandardButtons(QMessageBox::Ok);
        msgeBox.setIcon(QMessageBox::Warning);
        msgeBox.exec();
    }
}

void DepositView::on_comboBox_periodisity_activated(int index) {
    if (index == 0) {
        paymentsPeriodicity = 1;
    } else if (index == 1) {
        paymentsPeriodicity = 3;
    } else if (index == 2) {
        paymentsPeriodicity = 6;
    } else if (index == 3) {
        paymentsPeriodicity = 12;
    } else if (index == 4) {
        paymentsPeriodicity = 1;
    }
}

void DepositView::on_pushButton_back_clicked() {
    emit signal();
    this->close();
}

void DepositView::on_pushButton_replenishmentView_clicked() {
    createVectorViewWindow(replenishment);
}

void DepositView::on_pushButton_withdrawalView_clicked() {
    createVectorViewWindow(withdrawal);
}

void DepositView::createVectorViewWindow(std::map<int, double> dataMap) {
    QDialog view(this);
    QFormLayout form(&view);

    if (!dataMap.empty()) {
        for (auto it = dataMap.begin(); it != dataMap.end(); it++) {
            QLabel *lineSum = new QLabel(QString::number(it->second, 'f', 2));
            QLabel *lineMonth = new QLabel(QString::number(it->first));
            QLabel *line = new QLabel("_________________");

            form.addRow("Sum", lineSum);
            form.addRow("Month", lineMonth);
            form.addRow(line);
        }
        } else {
            QLabel *line = new QLabel(&view);
            form.addRow(line);
            line->setText("Empty data");
        }

    view.exec();
}

void DepositView::on_pushButton_clear_clicked() {
    replenishment.clear();
    withdrawal.clear();
    ui->label_accuredInserts ->setText("");
    ui->label_depositAmount ->setText("");
    ui->label_taxAmount ->setText("");
}
