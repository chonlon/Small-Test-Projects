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

std::shared_ptr<QFile> log_file{new QFile{"debug_information.log"}, destory};

void writeToFile(const QString& str)
{
    if (!log_file->exists())
        qDebug() << "No Such File" << __FILE__ << __FUNCTION__;
    if (!log_file->open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        qWarning() << "File Open Failed" << __FILE__ << __FUNCTION__;
    }

    QTextStream stream{log_file.get()};
    QTextCodec* codec = QTextCodec::codecForName("UTF-8");
    stream.setCodec(codec);

    QString log;
    log.append('[').append(QDateTime::currentDateTime().toString("yy-MM-dd hh:mm:ss")).append("] ");
    log.append(str);
    log.append('\n');
    stream << log;

    stream.flush();
}

int main(int argc, char *argv[])
{

    writeToFile( QString("HELLO IM HERE").leftJustified(100, ' ').append("123"));


    return 0;
}
