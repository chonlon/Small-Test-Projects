#include "FilterWidget.h"
#include <QHBoxLayout>

FilterWidget::FilterWidget(QWidget *parent) : QWidget(parent)
{
    auto layout = new QHBoxLayout{this};

    spin_one = new QSpinBox{this};
    spin_two = new QSpinBox{this};
    spin_three = new QSpinBox{this};

    button = new QPushButton{"filter",this};

    layout->addWidget(spin_one);
    layout->addWidget(spin_two);
    layout->addWidget(spin_three);
    layout->addWidget(button);

    connect(button, &QPushButton::clicked, [this]() {
        emit filter();
    });
}

QVector<int> FilterWidget::getData()
{
    QVector<int> result;
    result.push_back(spin_one->value());
    result.push_back(spin_two->value());
    result.push_back(spin_three->value());
    return result;
}
