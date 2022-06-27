#ifndef SRC_VIEW_CREDITVIEW_H_
#define SRC_VIEW_CREDITVIEW_H_
#include <QDialog>
#include <QMessageBox>
#include "CONTROLLER/calculatorController.h"

namespace Ui {
class CreditWindow;
}

class CreditView : public QDialog {
    Q_OBJECT

 public:
    explicit CreditView(s21::CalculatorController *controller, QWidget *parent = nullptr);
    ~CreditView();

 private:
    Ui::CreditWindow *ui;
    s21::CalculatorController* _controller;

 signals:
    void signal();

 private slots:
    void on_pushButton_clicked();
    void on_pushButton_back_clicked();
};
#endif  //  SRC_VIEW_CREDITVIEW_H_
