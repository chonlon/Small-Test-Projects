#pragma once

#include <QtWidgets/QWidget>
#include "ui_Widget.h"

class GuiWidget :
    public QWidget
{
    Q_OBJECT
private:
    Ui::Form form_;
public:
    GuiWidget();
    ~GuiWidget();
};

