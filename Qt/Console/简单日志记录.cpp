#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include <QDateTime>
const char* g_path = "./dalsa_debug_information.log";
const long long time_spot = QDateTime::currentMSecsSinceEpoch();

void writeToFile(const QString& str)
{
    QFile log_file{g_path};
    if (!log_file.exists())
        qDebug() << "No Such File" << __FILE__ << __FUNCTION__;
    if (!log_file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        qWarning() << "File Open Failed" << __FILE__ << __FUNCTION__;
    }

    QTextStream stream{&log_file};
    QTextCodec* codec = QTextCodec::codecForName("UTF-8");
    stream.setCodec(codec);

    QString log;
    log.append('[').append(QDateTime::currentDateTime().toString("yy-M-d h:m:s")).append("] ");
    log.append(str).append(QString::number(time_spot)).rightJustified(50, ' ');
    log.append('\n');
    stream << log;

    stream.flush();

    log_file.close();
}