#include "widget.h"
#include "ui_widget.h"
#include <QDateTime>
#include "define.h"
#include "compress.h"
#include <QDebug>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    connect(ui->modbus_init_btn, SIGNAL(clicked()), this, SLOT(on_modbus_init_clicked()));
    connect(ui->destroy_btn, SIGNAL(clicked()), this, SLOT(on_modbus_destroy_clicked()));
    
    connect(ui->start_read_btn, SIGNAL(clicked()), this, SLOT(on_start_read_clicked()));
    connect(ui->stop_read_btn, SIGNAL(clicked()), this, SLOT(on_stop_read_clicked()));

    connect(ui->compress_btn, SIGNAL(clicked()), this, SLOT(on_compress_clicked()));

    update_button();
}

Widget::~Widget()
{
    delete ui;
    modbusThread.quit();
    modbusThread.wait();
    
}

void Widget::on_modbus_init_clicked()
{
    ModbusParam ss;
//    ss.port_name_ = "COM4";

    ss.modbus_type_ = Modbus_TCP;
    ss.server_ip_ = "127.0.0.1";
    ss.server_port_ = 502;

    modbusThread.quit();
    modbusThread.wait();
    if (modbusThread.isRunning()) {
        modbusThread.exit(0);
    }

    CModbus* pModbus = new CModbus(ss);
    pModbus->moveToThread(&modbusThread);
    connect(&modbusThread, &QThread::finished, pModbus, &QObject::deleteLater);

    connect(this, &Widget::signal_modbus_start, pModbus, &CModbus::device_start);
    connect(this, &Widget::signal_modbus_destory, pModbus, &CModbus::device_destory);

    connect(this, &Widget::signal_request_start, pModbus, &CModbus::data_request_start);
    connect(this, &Widget::signal_request_stop, pModbus, &CModbus::data_request_stop);
    
    connect(pModbus, &CModbus::signal_data_recv, this, &Widget::onReadResult);

    modbusThread.start();

    emit signal_modbus_start();
    m_inited = true;
    update_button();
}

void Widget::on_modbus_destroy_clicked()
{
    emit signal_modbus_destory();
    modbusThread.quit();
    modbusThread.wait();

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

void Widget::onReadResult(const SmokeData& result)
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

void Widget::on_compress_clicked()
{
    QString src = "src";
    QString dst = "dst";

    CCompressTask *compressTask  = new CCompressTask(src, dst, true);

    connect(compressTask, &CCompressTask::sigTaskFinished,
        this, &Widget::on_compress_finished);
    QThreadPool::globalInstance()->start(compressTask);
}

void Widget::on_compress_finished(const QString& src, const QString& dst, int ret, bool bzip)
{
    QString str = QString("%1 - %2 - %3 - %4\n").arg(src).arg(dst).arg(ret).arg(bzip);
    QTextCursor textCursor = ui->show_result->textCursor();
    textCursor.movePosition(QTextCursor::End);
    textCursor.insertText(str);
    ui->show_result->moveCursor(QTextCursor::End);
}
