#ifndef FILTERWIDGET_H
#define FILTERWIDGET_H

#include <QWidget>
#include <QSpinBox>
#include <QVector>
#include <QPushButton>

class FilterWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FilterWidget(QWidget *parent = nullptr);

    QVector<int> getData();

    Q_SIGNAL void filter();
private:
    QSpinBox *spin_one;
    QSpinBox *spin_two;
    QSpinBox *spin_three;

    QPushButton *button;
signals:

public slots:
};

#endif // FILTERWIDGET_H
