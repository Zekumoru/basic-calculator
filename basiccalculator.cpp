#include "basiccalculator.h"

#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QString>
#include <cstdarg>
#include <iostream>

extern "C" {
    #include "math/math.h"
}

BasicCalculator::BasicCalculator(QWidget *parent)
    : QWidget{parent}
{
    screen = new QLabel(QString::number(0));

    QPushButton *primeButton = new QPushButton(tr("Prime"));
    QPushButton *acButton = new QPushButton(tr("AC"));
    QPushButton *backButton = new QPushButton(tr("<-"));

    QPushButton *zeroButton = new QPushButton(tr("0"));
    QPushButton *equalButton = new QPushButton(tr("="));
    QPushButton *plusButton = new QPushButton(tr("+"));

    mainLayout = new QGridLayout;
    mainLayout->addWidget(screen, 0, 0, 1, 4, Qt::AlignRight);

    mainLayout->addWidget(primeButton, 1, 0, 1, 2);
    mainLayout->addWidget(acButton, 1, 2);
    mainLayout->addWidget(backButton, 1, 3);

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

    connect(primeButton, &QPushButton::clicked, [this]() { this->buttonPressed(PRIME_BUTTON); });
    connect(acButton, &QPushButton::clicked, [this]() { this->buttonPressed(AC_BUTTON); });
    connect(backButton, &QPushButton::clicked, [this]() { this->buttonPressed(BACK_BUTTON); });

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
    if (pressed == DIVIDE_BUTTON) {
        std::cout << "10 / 2 = " << divide(10, 2) << std::endl;
    }
}
