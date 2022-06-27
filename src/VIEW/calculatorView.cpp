#include "calculatorView.h"

CalculatorView::CalculatorView(CalculatorController *controller, QWidget *parent) : QMainWindow(parent),
                                                                                ui(new Ui::CalculatorView),
                                                                                _controller(controller) {
    ui->setupUi(this);
    ui->comboBox->setCurrentIndex(0);

    connect(ui -> pushButton_0, SIGNAL(clicked()), this, SLOT(addToString()));
    connect(ui -> pushButton_1, SIGNAL(clicked()), this, SLOT(addToString()));
    connect(ui -> pushButton_2, SIGNAL(clicked()), this, SLOT(addToString()));
    connect(ui -> pushButton_3, SIGNAL(clicked()), this, SLOT(addToString()));
    connect(ui -> pushButton_4, SIGNAL(clicked()), this, SLOT(addToString()));
    connect(ui -> pushButton_5, SIGNAL(clicked()), this, SLOT(addToString()));
    connect(ui -> pushButton_6, SIGNAL(clicked()), this, SLOT(addToString()));
    connect(ui -> pushButton_7, SIGNAL(clicked()), this, SLOT(addToString()));
    connect(ui -> pushButton_8, SIGNAL(clicked()), this, SLOT(addToString()));
    connect(ui -> pushButton_9, SIGNAL(clicked()), this, SLOT(addToString()));
    connect(ui -> pushButton_x, SIGNAL(clicked()), this, SLOT(addToString()));
    connect(ui -> pushButton_pound, SIGNAL(clicked()), this, SLOT(addToString()));
    connect(ui -> pushButton_openedBracket, SIGNAL(clicked()), this, SLOT(addToString()));
    connect(ui -> pushButton_closedBracket, SIGNAL(clicked()), this, SLOT(addToString()));
    connect(ui -> pushButton_div, SIGNAL(clicked()), this, SLOT(addToString()));
    connect(ui -> pushButton_mult, SIGNAL(clicked()), this, SLOT(addToString()));
    connect(ui -> pushButton_minus, SIGNAL(clicked()), this, SLOT(addToString()));
    connect(ui -> pushButton_plus, SIGNAL(clicked()), this, SLOT(addToString()));
    connect(ui -> pushButton_pow, SIGNAL(clicked()), this, SLOT(addToString()));
    connect(ui -> pushButton_mod, SIGNAL(clicked()), this, SLOT(addToString()));
    connect(ui -> pushButton_PI, SIGNAL(clicked()), this, SLOT(addPIToString()));
    connect(ui -> pushButton_exp, SIGNAL(clicked()), this, SLOT(addToString()));
    connect(ui -> pushButton_sin, SIGNAL(clicked()), this, SLOT(addToString()));
    connect(ui -> pushButton_cos, SIGNAL(clicked()), this, SLOT(addToString()));
    connect(ui -> pushButton_tan, SIGNAL(clicked()), this, SLOT(addToString()));
    connect(ui -> pushButton_sqrt, SIGNAL(clicked()), this, SLOT(addToString()));
    connect(ui -> pushButton_asin, SIGNAL(clicked()), this, SLOT(addToString()));
    connect(ui -> pushButton_acos, SIGNAL(clicked()), this, SLOT(addToString()));
    connect(ui -> pushButton_atan, SIGNAL(clicked()), this, SLOT(addToString()));
    connect(ui -> pushButton_log, SIGNAL(clicked()), this, SLOT(addToString()));
    connect(ui -> pushButton_ln, SIGNAL(clicked()), this, SLOT(addToString()));
    connect(ui -> pushButton_back, SIGNAL(clicked()), this, SLOT(removeLastSymbol()));
    connect(ui -> pushButton_AC, SIGNAL(clicked()), this, SLOT(clearString()));
    connect(ui -> pushButton_equal, SIGNAL(clicked()), this, SLOT(getExpressionResult()));
}

CalculatorView::~CalculatorView() {
    delete ui;
}

void CalculatorView::addPIToString() {
    if (ui->resultLabel->text() == "0") {
        ui -> resultLabel -> setText("3.14159265358979323846");
    } else {
        ui -> resultLabel -> setText(ui->resultLabel->text() + "3.14159265358979323846");
    }
}

void CalculatorView::addToString() {
    QPushButton *pressedButton = (QPushButton *) sender();

    if (ui->resultLabel->text() == "0" && pressedButton->text() == ".") {
        ui -> resultLabel -> setText(ui->resultLabel->text() + pressedButton->text());
    } else if (ui->resultLabel->text() == "0") {
        ui -> resultLabel -> setText(pressedButton->text());
    } else {
        ui -> resultLabel -> setText(ui->resultLabel->text() + pressedButton->text());
    }
}

void CalculatorView::removeLastSymbol() {
      QString newText = ui->resultLabel->text();
      newText.chop(1);
      ui -> resultLabel -> setText(newText);
}

void CalculatorView::clearString() {
      ui -> resultLabel -> setText("0");
}

void CalculatorView::getExpressionResult() {
    if (ui->resultLabel->text().contains('x')) {
        xExpressionResult();
    } else {
        std::string result = _controller->calculateExpression(ui->resultLabel->text().toStdString());
        ui -> resultLabel -> setText(result.c_str());
    }
}

void CalculatorView::xExpressionResult() {
    QMessageBox msgBox;
    msgBox.setText("Choose action");
    msgBox.setInformativeText("Do you want build a graph?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setIcon(QMessageBox::Question);

    int res = msgBox.exec();
    if (res == QMessageBox::Yes) {
        bool ok;
        QString(_controller->getEquationResult(ui->resultLabel->text().toStdString(),
                                                                1).c_str()).toDouble(&ok);

        if (ok) {
            graph = new GraphView(_controller);
            connect(this, &CalculatorView::signal, graph, &GraphView::setExpressionSlot);
            emit signal(ui ->resultLabel->text());
            graph -> setModal(true);
            graph -> exec();
        } else {
            ui -> resultLabel -> setText("Incorrect exception");
        }
    } else {
        double valueX = QInputDialog::getDouble(this, tr("Enter number"), tr("x value:"),
                                                0.0, -2147483647, 2147483647, 7);
        ui -> resultLabel -> setText(_controller->getEquationResult(ui->resultLabel->text().toStdString(),
                                                                    valueX).c_str());
    }
}

void CalculatorView::on_comboBox_activated(int index) {
    if (index == 1) {
        this -> hide();
        credit = new CreditView(_controller);
        connect(credit, &CreditView::signal, this, &CalculatorView::showWindow);
        credit -> setModal(true);
        credit -> exec();
    } else if (index == 2) {
        this -> hide();
        deposit = new DepositView(_controller);
        connect(deposit, &DepositView::signal, this, &CalculatorView::showWindow);
        deposit -> setModal(true);
        deposit -> exec();
    }
}

void CalculatorView::showWindow() {
    this->show();
    ui->comboBox->setCurrentIndex(0);
}

void CalculatorView::keyPressEvent(QKeyEvent *e) {
    switch (e->key()) {
    case Qt::Key_Return:
        getExpressionResult();
        break;
    case Qt::Key_0:
        ui -> pushButton_0->click();
        break;
    case Qt::Key_1:
        ui -> pushButton_1->click();
        break;
    case Qt::Key_2:
        ui -> pushButton_2->click();
        break;
    case Qt::Key_3:
        ui -> pushButton_3->click();
        break;
    case Qt::Key_4:
        ui -> pushButton_4->click();
        break;
    case Qt::Key_5:
        ui -> pushButton_5->click();
        break;
    case Qt::Key_6:
        ui -> pushButton_6->click();
        break;
    case Qt::Key_7:
        ui -> pushButton_7->click();
        break;
    case Qt::Key_8:
        ui -> pushButton_8->click();
        break;
    case Qt::Key_9:
        ui -> pushButton_9->click();
        break;
    case Qt::Key_Percent:
        ui -> pushButton_mod->click();
        break;
    case Qt::Key_Comma:
        ui -> pushButton_pound->click();
        break;
    case Qt::Key_Period:
        ui -> pushButton_pound->click();
        break;
    case Qt::Key_Plus:
        ui -> pushButton_plus->click();
        break;
    case Qt::Key_Minus:
        ui -> pushButton_minus->click();
        break;
    case Qt::Key_Asterisk:
        ui -> pushButton_mult->click();
        break;
    case Qt::Key_Slash:
        ui -> pushButton_div->click();
        break;
    case Qt::Key_Escape:
        clearString();
        break;
    case Qt::Key_Backspace:
        removeLastSymbol();
        break;
    case Qt::Key_X:
        ui -> pushButton_x->click();
        break;
    case Qt::Key_S:
        ui -> resultLabel -> setText(ui->resultLabel->text() + "s");
        break;
    case Qt::Key_I:
        ui -> resultLabel ->setText(ui->resultLabel->text() + "i");
        break;
    case Qt::Key_N:
        ui -> resultLabel ->setText(ui->resultLabel->text() + "n");
        break;
    case Qt::Key_C:
        ui -> resultLabel ->setText(ui->resultLabel->text() + "c");
        break;
    case Qt::Key_O:
        ui -> resultLabel ->setText(ui->resultLabel->text() + "o");
        break;
    case Qt::Key_T:
        ui -> resultLabel ->setText(ui->resultLabel->text() + "t");
        break;
    case Qt::Key_A:
        ui -> resultLabel ->setText(ui->resultLabel->text() + "a");
        break;
    case Qt::Key_Q:
        ui -> resultLabel ->setText(ui->resultLabel->text() + "q");
        break;
    case Qt::Key_R:
        ui -> resultLabel ->setText(ui->resultLabel->text() + "r");
        break;
    case Qt::Key_L:
        ui -> resultLabel ->setText(ui->resultLabel->text() + "l");
        break;
    case Qt::Key_G:
        ui -> resultLabel ->setText(ui->resultLabel->text() + "g");
        break;
    case Qt::Key_M:
        ui -> resultLabel ->setText(ui->resultLabel->text() + "m");
        break;
    case Qt::Key_D:
        ui -> resultLabel ->setText(ui->resultLabel->text() + "d");
        break;
    case Qt::Key_E:
        ui -> resultLabel ->setText(ui->resultLabel->text() + "e");
        break;
    case Qt::Key_P:
        ui -> resultLabel ->setText(ui->resultLabel->text() + "p");
        break;
    case Qt::Key_ParenLeft:
        ui -> pushButton_openedBracket->click();
        break;
    case Qt::Key_ParenRight:
        ui -> pushButton_closedBracket->click();
        break;
    }
}
