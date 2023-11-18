#ifndef BASICCALCULATOR_H
#define BASICCALCULATOR_H

#include <QWidget>
#include <cstdbool>

class QLabel;
class QString;
class QGridLayout;

enum ButtonPressed {
    EQUAL_BUTTON,
    NEGATE_BUTTON,
    AC_BUTTON,
    BACK_BUTTON,
    ZERO_BUTTON,
    ONE_BUTTON,
    TWO_BUTTON,
    THREE_BUTTON,
    FOUR_BUTTON,
    FIVE_BUTTON,
    SIX_BUTTON,
    SEVEN_BUTTON,
    EIGHT_BUTTON,
    NINE_BUTTON,
    ADD_BUTTON,
    SUBTRACT_BUTTON,
    MULTIPLY_BUTTON,
    DIVIDE_BUTTON,
    EXP_BUTTON,
    GCD_BUTTON,
    LCM_BUTTON,
    PRIME_BUTTON,
    SQRT_BUTTON
};

enum Operation {
    NOOP,
    ADD_OP,
    SUBTRACT_OP,
    MULTIPLY_OP,
    DIVIDE_OP,
    EXP_OP,
    GCD_OP,
    LCM_OP,
    PRIME_OP,
    SQRT_OP
};

class BasicCalculator : public QWidget
{
    Q_OBJECT

public:
    explicit BasicCalculator(QWidget *parent = nullptr);

public slots:
    void buttonPressed(ButtonPressed pressed);

private:
    int firstNumber;
    int secondNumber;
    Operation op;
    bool hasJustPressedOp;

    QGridLayout *mainLayout;
    QLabel *screen;

    void clear();
    void updateDisplay();
    void addButton(int row, int col, QString label, ButtonPressed pressed, bool isImplemented);

};

#endif // BASICCALCULATOR_H
