#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "modbus.h"
#include <QTimer>
#include <QSharedPointer>

class QPushButton;
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

public slots:
    void onReadResult(const SmokeData&);
signals:
    void signal_modbus_start();
    void signal_modbus_stop();
    void signal_modbus_destory();
private slots:
    void on_modbus_init_clicked();
    void on_modbus_destroy_clicked();

    void on_start_read_clicked();
    void on_stop_read_clicked();

    
private:
    void update_button();

    Ui::Widget *ui;

    QTime m_countTimer;
    qint64  m_count;

    bool m_inited{ false };
    bool m_requested{ false };

    QString m_strRslt;

    QPushButton* m_pTestBtn{ nullptr };
};

#endif // WIDGET_H
