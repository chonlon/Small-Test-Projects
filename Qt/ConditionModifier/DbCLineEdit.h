#pragma once
#include <QLineEdit>

class DbCLineEdit :public QLineEdit
{
    Q_OBJECT
public:
    DbCLineEdit(QWidget *parent = Q_NULLPTR);

    void setChecked();
    void setUnchecked();
signals:
    void clicked();
    void focussed(bool hasFocus);

private slots:
    void editFinished();

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseDoubleClickEvent(QMouseEvent *e) override;
    void focusInEvent(QFocusEvent *e) override;
    void focusOutEvent(QFocusEvent *e) override;

private:
    bool double_clicked = false;
    QTimer*  signal_click_timer;
}; 