#include "DbCLineEdit.h"
#include <QEvent>
#include <QTimer>

DbCLineEdit::DbCLineEdit(QWidget* parent /*= Q_NULLPTR*/)
{
    this->setReadOnly(true);
    this->setUnchecked();
    connect(this, SIGNAL(editingFinished()), this, SLOT(editFinished()));

    signal_click_timer = new QTimer{this};
    connect(signal_click_timer,
            &QTimer::timeout,
            [signal_click_timer, this]() {
                emit clicked();
                signal_click_timer->stop();
            });
}

void DbCLineEdit::setChecked()
{
    const char* checked_style = "\
        QLineEdit\
    {\
        //边界1像素 实线 颜色rgb  或者border:none 没有边界\
        border:1px solid rgb(180, 180, 180);\
        //背景的颜色\
        background: rgba(35, 168, 242, 100);\
        //边角4像素圆滑\
        border - radius: 4px;\
    }";
    this->setStyleSheet(checked_style);
}

void DbCLineEdit::setUnchecked()
{
    const char* unchecked_style = "\
        QLineEdit\
    {\
        //边界1像素 实线 颜色rgb  或者border:none 没有边界\
        border:1px solid rgb(180, 180, 180);\
        //背景的颜色\
        background: rgba(230, 230, 230, 100);\
        //边角4像素圆滑\
        border - radius: 4px;\
    }";
    this->setStyleSheet(unchecked_style);
}

void DbCLineEdit::editFinished()
{
    this->setReadOnly(true);
}

void DbCLineEdit::mousePressEvent(QMouseEvent* event)
{
    double_clicked ? double_clicked = false : signal_click_timer->start(10);
    QLineEdit::mousePressEvent(event);
}

void DbCLineEdit::mouseDoubleClickEvent(QMouseEvent* e)
{
    this->setReadOnly(false);
    signal_click_timer->stop();
    QLineEdit::mouseDoubleClickEvent(e);
}

void DbCLineEdit::focusInEvent(QFocusEvent* e)
{
    QLineEdit::focusInEvent(e);
    focussed(true);
}

void DbCLineEdit::focusOutEvent(QFocusEvent* e)
{
    QLineEdit::focusOutEvent(e);
    focussed(false);
}
