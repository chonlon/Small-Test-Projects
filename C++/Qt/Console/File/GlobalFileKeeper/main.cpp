#include <QtCore/QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include <QDateTime>
#include <QDebug>

#include <memory>
void writeToFile(const QString& str);

void destory(QFile* file)
{
    writeToFile("Destorying file");
    file->close();
    delete file;
}
const long long time_spot = QDateTime::currentMSecsSinceEpoch();
std::shared_ptr<QFile> log_file{new QFile{"debug_information.log"}, destory};

void writeToFile(const QString& str)
{
    if (!log_file->exists())
        qDebug() << "No Such File" << __FILE__ << __FUNCTION__;
    static bool first = true;
    if(first) {
        if (!log_file->open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
            qWarning() << "File Open Failed" << __FILE__ << __FUNCTION__;
        }
        first = false;
    }

    QTextStream stream{log_file.get()};
    QTextCodec* codec = QTextCodec::codecForName("UTF-8");
    stream.setCodec(codec);

    QString log;
    log.append('[').append(QDateTime::currentDateTime().toString("yy-M-d h:m:s:zzz")).append("] ");
    log.append(QString::number(time_spot)).append(' ').append(str).rightJustified(100, ' ');
    log.append('\n');
    stream << log;

    stream.flush();
}



int main(int argc, char *argv[])
{
    for(auto i = 0; i < 100; ++i) {
        writeToFile("HELLO IM HERE");
    }


    return 0;
}
