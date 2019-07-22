#ifndef CONDITIONSELECTWIDGET_H
#define CONDITIONSELECTWIDGET_H

#include <QWidget>

struct ConditionSelectWidgetPrivate;

class ConditionSelectWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ConditionSelectWidget(QWidget *parent = nullptr);
    ~ConditionSelectWidget();

private:
    ConditionSelectWidgetPrivate* data_;
};

#endif // CONDITIONSELECTWIDGET_H
