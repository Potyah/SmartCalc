#ifndef SRC_MODEL_GRAPHMODEL_H_
#define SRC_MODEL_GRAPHMODEL_H_

#include <vector>
#include "calculatorModel.h"

class GraphModel : public CalculatorModel  {
using stack_type = std::pair<std::string, int>;
 private:
    std::vector<double> _vectorX;
    std::vector<double> _vectorY;

 public:
    GraphModel() {}
    ~GraphModel() {}

    void setVectorX(const std::vector<double> &vectorX);
    std::vector<double> getVectorX();

    void setVectorY(const std::vector<double> &vectorY);
    std::vector<double> getVectorY();

    void fillVectors(double step, int from, int to, const std::string &expression);
};
#endif  //  SRC_MODEL_GRAPHMODEL_H_
