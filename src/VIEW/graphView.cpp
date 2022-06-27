#include "graphView.h"
#include "ui_graphView.h"
#include <QVector>

GraphView::GraphView(CalculatorController *controller, QWidget *parent) : QDialog(parent),
                                                                          ui(new Ui::GraphView),
                                                                          _controller(controller) {
    ui->setupUi(this);
    ui->spinBox_from->setRange(-1000000, 1000000);
    ui->spinBox_from->setValue(-10);
    ui->spinBox_to->setRange(-1000000, 1000000);
    ui->spinBox_to->setValue(10);
    setFixedSize(403, 436);
    QLinearGradient plotGradient;
    plotGradient.setStart(0, 0);
    plotGradient.setFinalStop(0, 350);
    plotGradient.setColorAt(0, QColor(234, 242, 245));
    plotGradient.setColorAt(1, QColor(234, 242, 245));
    ui->graphWidget-> setBackground(plotGradient);
    ui->graphWidget->xAxis->setRange(-10, 10);
    ui->graphWidget->yAxis->setRange(-10, 10);
    this->setAttribute(Qt::WA_DeleteOnClose);
}

GraphView::~GraphView() {
    delete ui;
}

void GraphView::setExpressionSlot(QString expressinon) {
    ui->graphLabel->setText(expressinon);
}

void GraphView::buildGraph() {
    ui->graphWidget->setInteraction(QCP::iRangeZoom, true);
    ui->graphWidget->setInteraction(QCP::iRangeDrag, true);

    int from = ui->spinBox_from->value();
    int to = ui->spinBox_to->value();

    if (correctDataCheck(from, to)) {
        _controller->getGraphCalculations(0.05, from, to, ui->graphLabel->text().toStdString());

        std::vector<double> stdX = _controller->getVectorX();
        QVector<double> x = QVector<double>(stdX.begin(), stdX.end());

        std::vector<double> stdY = _controller->getVectorY();
        QVector<double> y = QVector<double>(stdY.begin(), stdY.end());

        ui->graphWidget->addGraph();
        ui->graphWidget->graph(0)->setLineStyle(QCPGraph::lsNone);
        ui->graphWidget->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 6));
        ui->graphWidget->graph(0)->addData(x, y);
        ui->graphWidget->replot();
    }
}

bool GraphView::correctDataCheck(int from, int to) {
    if ((from >= to) || (from < -1000000) || (to > 1000000) || (from - to == 0)) {
        QMessageBox msgBox;
        msgBox.setText("Attention!");
        msgBox.setInformativeText("You enter invalid data");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.exec();

        return false;
     }

    return true;
}

void GraphView::on_pushButton_build_clicked() {
    ui->graphWidget->clearGraphs();
    buildGraph();
}
