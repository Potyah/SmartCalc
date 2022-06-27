#include "graphModel.h"

void GraphModel::setVectorX(const std::vector<double> &vectorX) {
    _vectorX = vectorX;
}

std::vector<double> GraphModel::getVectorX() {
    return _vectorX;
}

void GraphModel::setVectorY(const std::vector<double> &vectorY) {
    _vectorY = vectorY;
}

std::vector<double> GraphModel::getVectorY() {
    return _vectorY;
}

void GraphModel::fillVectors(double step, int from, int to, const std::string &expression) {
    std::stack<stack_type> mainStack = getMainStack(expression);

    std::vector<double> vectorX;
    std::vector<double> vectorY;

    for (double i = from; i < to; i+=step) {
        std::stack<stack_type> copyStack(mainStack);
        vectorX.push_back(i);
        vectorY.push_back(calculateExpressionWithX(copyStack, i));
    }

    setVectorX(vectorX);
    setVectorY(vectorY);
    mainStack = std::stack<stack_type>();
}
