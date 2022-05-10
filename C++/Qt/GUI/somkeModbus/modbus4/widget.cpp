#include "widget.h"
#include "ui_widget.h"
#include <QDateTime>


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    connect(ui->modbus_init_btn, SIGNAL(clicked()), this, SLOT(on_modbus_init_clicked()));
    connect(ui->destroy_btn, SIGNAL(clicked()), this, SLOT(on_modbus_destroy_clicked()));

    connect(ui->start_read_btn, SIGNAL(clicked()), this, SLOT(on_start_read_clicked()));
    connect(ui->stop_read_btn, SIGNAL(clicked()), this, SLOT(on_stop_read_clicked()));

    update_button();
}

Widget::~Widget()
{
    delete ui;
    
    if (m_pModbus) {
        m_pModbus->modbus_end();
        m_pModbus = nullptr;
    }
}

void Widget::on_modbus_init_clicked()
{
    ModbusParam ss;
    //ss.port_name_ = "COM3";

    ss.modbus_type_ = Modbus_TCP;
    ss.server_ip_ = "127.0.0.1";
    ss.server_port_ = 502;

    if (!m_pModbus) {
        m_pModbus = new CModbus(ss);

        connect(this, &Widget::signal_request_start,
            m_pModbus, &CModbus::data_request_start);
        connect(this, &Widget::signal_request_stop, 
            m_pModbus, &CModbus::data_request_stop);
        connect(m_pModbus, &CModbus::signal_data_recv, 
            this, &Widget::onReadResult);
    }
    m_pModbus->modbus_start();


    m_inited = true;
    update_button();
}

void Widget::on_modbus_destroy_clicked()
{
    if (m_pModbus) {
        m_pModbus->modbus_end();
        m_pModbus = nullptr;
    }

    m_inited = false;
    m_requested = false;
    update_button();
}

void Widget::on_start_read_clicked()
{
    emit signal_request_start();

    m_requested = true;
    m_countTimer.restart();
    m_count = 0;
    update_button();
}

void Widget::on_stop_read_clicked()
{
    emit signal_request_stop();

    m_requested = false;
    update_button();
}

void Widget::onReadResult(SmokeData result)
{
    QString str = QString("%1 - result:%2 %3 %4 %5\n")
        .arg(QDateTime::currentDateTime().toString("hh:mm:ss:zzz"))
        .arg(result.addr0_)
        .arg(result.addr1_)
        .arg(result.addr2_)
        .arg(result.addr3_);

    //m_strRslt += str;
    //ui->show_result->setPlainText(m_strRslt);
    //ui->show_result->moveCursor(QTextCursor::End);

    QTextCursor textCursor = ui->show_result->textCursor();
    textCursor.movePosition(QTextCursor::End);
    textCursor.insertText(str);
    ui->show_result->moveCursor(QTextCursor::End);

    m_count++;

    qint64 neslped = m_countTimer.elapsed() / 1000;

    if (m_count % 10 == 0 && neslped > 0) {
        float nhz = m_count / neslped;
        ui->frame_rate->setText(QString("%1").arg(nhz));
    }
}

void Widget::update_button()
{
    if (m_inited) {
        ui->modbus_init_btn->setEnabled(false);
        ui->destroy_btn->setEnabled(true);
        ui->start_read_btn->setEnabled(!m_requested);
        ui->stop_read_btn->setEnabled(m_requested);
    }
    else {
        ui->modbus_init_btn->setEnabled(true);
        ui->destroy_btn->setEnabled(false);
        ui->start_read_btn->setEnabled(false);
        ui->stop_read_btn->setEnabled(false);
    }
}