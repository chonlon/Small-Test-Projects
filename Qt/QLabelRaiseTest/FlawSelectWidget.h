#pragma once

#include <QWidget>

class FlawSelectWidgetPrivate;

class FlawSelectWidget :
    public QWidget
{
    Q_OBJECT
public:
    FlawSelectWidget(QWidget *parent = nullptr);
    ~FlawSelectWidget();
private:
   FlawSelectWidgetPrivate* m_data;
};

//#endif // !_FlawSelectWidget_H__
