#include "basiccalculator.h"

#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QString>
#include <cstdarg>
#include <cstdbool>

extern "C" {
    #include "math/math.h"
}

BasicCalculator::BasicCalculator(QWidget *parent)
    : QWidget{parent}
{
    firstNumber = 0;
    secondNumber = 0;
    op = NOOP;

    screen = new QLabel(QString::number(firstNumber));

    QPushButton *zeroButton = new QPushButton(tr("0"));
    QPushButton *equalButton = new QPushButton(tr("="));
    QPushButton *plusButton = new QPushButton(tr("+"));

    mainLayout = new QGridLayout;
    mainLayout->addWidget(screen, 0, 0, 1, 4, Qt::AlignRight);

    addRow(
        1, 4,
        tr("+/-"), NEGATE_BUTTON,
        tr("Prime"), PRIME_BUTTON,
        tr("AC"), AC_BUTTON,
        tr("<-"), BACK_BUTTON);
    addRow(
        2, 4,
        tr("GCD"), GCD_BUTTON,
        tr("LCM"), LCM_BUTTON,
        tr("Sqrt"), SQRT_BUTTON,
        tr("^"), EXP_BUTTON);
    addRow(
        3, 4,
        tr("7"), SEVEN_BUTTON,
        tr("8"), EIGHT_BUTTON,
        tr("9"), NINE_BUTTON,
        tr("/"), DIVIDE_BUTTON);
    addRow(
        4, 4,
        tr("4"), FOUR_BUTTON,
        tr("5"), FIVE_BUTTON,
        tr("6"), SIX_BUTTON,
        tr("*"), MULTIPLY_BUTTON);
    addRow(
        5, 4,
        tr("1"), ONE_BUTTON,
        tr("2"), TWO_BUTTON,
        tr("3"), THREE_BUTTON,
        tr("-"), SUBTRACT_BUTTON);

    mainLayout->addWidget(zeroButton, 6, 0, 1, 2);
    mainLayout->addWidget(equalButton, 6, 2);
    mainLayout->addWidget(plusButton, 6, 3);

    connect(zeroButton, &QPushButton::clicked, [this]() { this->buttonPressed(ZERO_BUTTON); });
    connect(equalButton, &QPushButton::clicked, [this]() { this->buttonPressed(EQUAL_BUTTON); });
    connect(plusButton, &QPushButton::clicked, [this]() { this->buttonPressed(ADD_BUTTON); });

    setLayout(mainLayout);
    setWindowTitle(tr("Basic Calculator"));
}

void BasicCalculator::addRow(int row, int nItems, QString item, ButtonPressed buttonPressed, ...)
{
    va_list items;
    va_start(items, buttonPressed);

    ButtonPressed currentButtonPressed = buttonPressed;
    QString* current = &item;
    for (int i = 0; i < nItems; i++) {
        if (i != 0) {
            current = va_arg(items, QString*);
            currentButtonPressed = (ButtonPressed) va_arg(items, int);
        }

        QPushButton *button = new QPushButton(*current);
        mainLayout->addWidget(button, row, i);
        connect(button, &QPushButton::clicked, [this, currentButtonPressed]() {
            this->buttonPressed(currentButtonPressed);
        });
    }

    va_end(items);
}

void BasicCalculator::buttonPressed(ButtonPressed pressed)
{
    bool affectNumberChanges = false;
    int currentNumber = (op == NOOP)? firstNumber : secondNumber;

    if (ZERO_BUTTON <= pressed && pressed <= NINE_BUTTON) {
        int digit = pressed - ZERO_BUTTON;

        currentNumber *= 10;
        currentNumber += digit;
        affectNumberChanges = true;
    } else if (pressed == NEGATE_BUTTON) {
        currentNumber = -currentNumber;
        affectNumberChanges = true;
    } else if (pressed == BACK_BUTTON) {
        if (currentNumber == 0) {
            op = NOOP;
        } else {
            currentNumber /= 10;
            affectNumberChanges = true;
        }
    } else if (pressed == DIVIDE_BUTTON) {
        op = DIVIDE_OP;
    } else if (pressed == EQUAL_BUTTON && op != NOOP) {
        int result = 0;

        if (op == DIVIDE_OP) {
            result = divide(firstNumber, secondNumber);
        }

        firstNumber = result;
        secondNumber = 0;
        op = NOOP;
    }

    if (affectNumberChanges) {
        if (op == NOOP) firstNumber = currentNumber;
        else secondNumber = currentNumber;
    }

    updateDisplay();
}

void BasicCalculator::updateDisplay()
{
    QString display = QString::number(firstNumber);

    if (op != NOOP) {
        QString opString;

        if (op == DIVIDE_OP) {
            opString = " / ";
        }

        display += opString + QString::number(secondNumber);
    }

    screen->setText(display);
}
