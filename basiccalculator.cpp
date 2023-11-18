#include "basiccalculator.h"

#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QString>
#include <cstdbool>

extern "C" {
    #include "math/math.h"
}

BasicCalculator::BasicCalculator(QWidget *parent)
    : QWidget{parent}
{
    clear();

    screen = new QLabel(QString::number(firstNumber));

    QPushButton *zeroButton = new QPushButton(tr("0"));
    QPushButton *equalButton = new QPushButton(tr("="));
    QPushButton *plusButton = new QPushButton(tr("+"));

    mainLayout = new QGridLayout;
    mainLayout->addWidget(screen, 0, 0, 1, 4, Qt::AlignRight);

    addButton(1, 0, tr("+/-"), NEGATE_BUTTON, true);
    addButton(1, 1, tr("Prime"), PRIME_BUTTON, true);
    addButton(1, 2, tr("AC"), AC_BUTTON, true);
    addButton(1, 3, tr("<-"), BACK_BUTTON, true);

    addButton(2, 0, tr("GCD"), GCD_BUTTON, true);
    addButton(2, 1, tr("LCM"), LCM_BUTTON, false); // need multiply function
    addButton(2, 2, tr("Sqrt"), SQRT_BUTTON, true);
    addButton(2, 3, tr("^"), EXP_BUTTON, false);

    addButton(3, 0, tr("7"), SEVEN_BUTTON, true);
    addButton(3, 1, tr("8"), EIGHT_BUTTON, true);
    addButton(3, 2, tr("9"), NINE_BUTTON, true);
    addButton(3, 3, tr("/"), DIVIDE_BUTTON, true);

    addButton(4, 0, tr("4"), FOUR_BUTTON, true);
    addButton(4, 1, tr("5"), FIVE_BUTTON, true);
    addButton(4, 2, tr("6"), SIX_BUTTON, true);
    addButton(4, 3, tr("*"), MULTIPLY_BUTTON, false);

    addButton(5, 0, tr("1"), ONE_BUTTON, true);
    addButton(5, 1, tr("2"), TWO_BUTTON, true);
    addButton(5, 2, tr("3"), THREE_BUTTON, true);
    addButton(5, 3, tr("-"), SUBTRACT_BUTTON, true);

    mainLayout->addWidget(zeroButton, 6, 0, 1, 2);
    mainLayout->addWidget(equalButton, 6, 2);
    mainLayout->addWidget(plusButton, 6, 3);

    connect(zeroButton, &QPushButton::clicked, this, [this]() { this->buttonPressed(ZERO_BUTTON); });
    connect(equalButton, &QPushButton::clicked, this, [this]() { this->buttonPressed(EQUAL_BUTTON); });
    connect(plusButton, &QPushButton::clicked, this, [this]() { this->buttonPressed(ADD_BUTTON); });

    setLayout(mainLayout);
    setWindowTitle(tr("Basic Calculator"));
}

void BasicCalculator::addButton(int row, int col, QString label, ButtonPressed pressed, bool isImplemented)
{
    QPushButton *button = new QPushButton(label);

    button->setEnabled(isImplemented);
    mainLayout->addWidget(button, row, col);

    connect(button, &QPushButton::clicked, this, [this, pressed]() {
        this->buttonPressed(pressed);
    });
}

void BasicCalculator::clear()
{
    firstNumber = 0;
    secondNumber = 0;
    op = NOOP;
    hasJustPressedOp = false;
}

void BasicCalculator::buttonPressed(ButtonPressed pressed)
{
    hasJustPressedOp = false;

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
    } else if (pressed == AC_BUTTON) {
        clear();
    } else if (pressed == BACK_BUTTON) {
        if (currentNumber == 0) {
            op = NOOP;
        } else {
            currentNumber /= 10;
            affectNumberChanges = true;
        }
    } else if (ADD_BUTTON <= pressed && pressed <= SQRT_BUTTON) {
        op = (Operation)(pressed - ADD_BUTTON + ADD_OP);
        hasJustPressedOp = true;

        if (PRIME_OP <= op && op <= SQRT_OP) {
            buttonPressed(EQUAL_BUTTON);
            return;
        }
    } else if (pressed == EQUAL_BUTTON && op != NOOP) {
        int result = 0;

        switch (op) {
        case ADD_OP:
            result = firstNumber + secondNumber;
            break;
        case SUBTRACT_OP:
            result = firstNumber - secondNumber;
            break;
        case DIVIDE_OP:
            result = divide(firstNumber, secondNumber);
            break;
        case GCD_OP:
            result = gcd(firstNumber, secondNumber);
            break;
        case LCM_OP:
            result = lcm(firstNumber, secondNumber);
            break;
        case PRIME_OP:
            result = prime(firstNumber);
            break;
        case SQRT_OP:
            result = sqroot(firstNumber);
            break;
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

        switch (op) {
        case ADD_OP:
            opString = " +";
            break;
        case SUBTRACT_OP:
            opString = " -";
            break;
        case DIVIDE_OP:
            opString = " /";
            break;
        case GCD_OP:
            opString = "GCD(";
            break;
        case LCM_OP:
            opString = "LCM(";
            break;
        case PRIME_OP:
        case SQRT_OP:
            break;
        }

        QString secondNumberString = QString::number(secondNumber);
        if (GCD_OP <= op && op <= LCM_OP) {
            display = opString + display + ", " + secondNumberString + ")";
        } else {
            display += opString;
            if (!hasJustPressedOp) {
                display += " " + secondNumberString;
            }
        }
    }

    screen->setText(display);
}
