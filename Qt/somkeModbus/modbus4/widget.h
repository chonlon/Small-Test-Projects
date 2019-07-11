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

signals:
    void signal_request_start();
    void signal_request_stop();
private slots:
    void on_modbus_init_clicked();
    void on_modbus_destroy_clicked();

    void on_start_read_clicked();
    void on_stop_read_clicked();

    void onReadResult(SmokeData result);
private:
    void update_button();

    Ui::Widget *ui;
    CModbus *m_pModbus{ nullptr };

    QTime m_countTimer;
    qint64  m_count;

    bool m_inited{ false };
    bool m_requested{ false };

    QString m_strRslt;

    QPushButton* m_pTestBtn{ nullptr };
};

#endif // WIDGET_H
