#ifndef SRC_VIEW_GRAPHVIEW_H_
#define SRC_VIEW_GRAPHVIEW_H_

#include <QDialog>
#include <QVector>
#include <QtPrintSupport>
#include "QCUSTOMPLOT/qcustomplot.h"
#include "CONTROLLER/calculatorController.h"

namespace Ui {
class GraphView;
}

class GraphView : public QDialog {
    Q_OBJECT

 public:
    explicit GraphView(s21::CalculatorController *controller, QWidget *parent = nullptr);
    ~GraphView();

 private:
    Ui::GraphView *ui;
    s21::CalculatorController* _controller;

 public slots:
    void setExpressionSlot(QString expressinon);
    void buildGraph();
    bool correctDataCheck(int from, int to);

 private slots:
    void on_pushButton_build_clicked();
};

#endif  // SRC_VIEW_GRAPHVIEW_H_
