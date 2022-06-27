#ifndef SRC_VIEW_CALCULATORVIEW_H_
#define SRC_VIEW_CALCULATORVIEW_H_

#include <QMainWindow>
#include "graphView.h"
#include "creditView.h"
#include "depositView.h"
#include "ui_calculatorView.h"
#include <QMessageBox>
#include <QInputDialog>
#include "CONTROLLER/calculatorController.h"

namespace Ui {
class MainWindow;
}

class CalculatorView : public QMainWindow {
    Q_OBJECT

 public:
    explicit CalculatorView(CalculatorController *controller, QWidget *parent = nullptr);
    ~CalculatorView();

 private:
    Ui::CalculatorView *ui;
    CalculatorController* _controller;
    CreditView *credit;
    GraphView *graph;
    DepositView *deposit;

 private slots:
    void addToString();
    void addPIToString();
    void removeLastSymbol();
    void clearString();
    void getExpressionResult();
    void xExpressionResult();
    void on_comboBox_activated(int index);
    void keyPressEvent(QKeyEvent *e);

 public slots:
    void showWindow();

 signals:
    void signal(QString a);
};
#endif  //  SRC_VIEW_CALCULATORVIEW_H_
