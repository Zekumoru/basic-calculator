#ifndef BASICCALCULATOR_H
#define BASICCALCULATOR_H

#include <QWidget>
#include <cstdarg>

class QLabel;
class QString;
class QGridLayout;

enum ButtonPressed {
    PRIME_BUTTON,
    AC_BUTTON,
    BACK_BUTTON,
    GCD_BUTTON,
    LCM_BUTTON,
    SQRT_BUTTON,
    EXP_BUTTON,
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
    EQUAL_BUTTON
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

    QGridLayout *mainLayout;
    QLabel *screen;

    void updateDisplay();
    void addRow(int row, int nItems, QString item, ButtonPressed button,...);

};

#endif // BASICCALCULATOR_H
