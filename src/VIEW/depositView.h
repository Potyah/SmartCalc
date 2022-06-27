#ifndef SRC_VIEW_DEPOSITVIEW_H_
#define SRC_VIEW_DEPOSITVIEW_H_

#include <QDialog>
#include <QInputDialog>
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QMessageBox>
#include "CONTROLLER/calculatorController.h"

namespace Ui {
class DepositView;
}

class DepositView : public QDialog {
    Q_OBJECT

 public:
    explicit DepositView(s21::CalculatorController *controller, QWidget *parent = nullptr);
    ~DepositView();

 private:
    Ui::DepositView *ui;
    int interestCapitalization;
    std::map<int, double> replenishment;
    std::map<int, double>  withdrawal;
    int paymentsPeriodicity;
    s21::CalculatorController* _controller;

 signals:
    void signal();

 private slots:
    void on_pushButton_clicked();
    void on_pushButton_replenishment_clicked();
    void on_pushButton_withdrawal_clicked();
    void on_comboBox_periodisity_activated(int index);
    void on_pushButton_back_clicked();
    void on_pushButton_replenishmentView_clicked();
    void on_pushButton_withdrawalView_clicked();
    void on_pushButton_clear_clicked();
    void createAddWindow(std::map<int, double> *dataMap);
    void createVectorViewWindow(std::map<int, double> dataMap);
};

#endif  //  SRC_VIEW_DEPOSITVIEW_H_
