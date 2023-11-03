#include <QApplication>
#include "basiccalculator.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    BasicCalculator calculator;
    calculator.show();

    return app.exec();
}
