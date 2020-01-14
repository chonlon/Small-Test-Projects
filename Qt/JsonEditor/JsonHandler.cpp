#include "JsonHandler.h"

#include <QFile>
#include <QJsonDocument>
#include <QDebug>
#include <QIODevice>
#include <QTextCodec>


JsonHandler::JsonHandler(const QString& path)
{
    path_ = path;
    init();
}

JsonHandler::~JsonHandler()
{
}

void JsonHandler::init()
{
    QFile setting_file{path_};
    if (!setting_file.exists())
        qDebug() << "No Such File:" << path_ << __FILE__ << __FUNCTION__;
    if (!setting_file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qWarning() << "File Open Failed" << __FILE__ << __FUNCTION__;
    }

    QTextStream in(&setting_file);
    QTextCodec *codec=QTextCodec::codecForName("UTF-8");
    in.setCodec(codec);
    const auto in_string = in.readAll();
    QJsonParseError error;
    auto document = QJsonDocument::fromJson(in_string.toUtf8(), &error);
    if (error.error == QJsonParseError::NoError)
        if (!(document.isNull() || document.isEmpty()))
            obj_ = document.object();
}

void JsonHandler::writeToFile() const
{
    QFile setting_file{path_};
    if (!setting_file.exists())
        qDebug() << "No Such File" << __FILE__ << __FUNCTION__;
    if (!setting_file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
        qWarning() << "File Open Failed" << __FILE__ << __FUNCTION__;
    }

    // 当关闭时才去写入到文件中.
    QTextStream stream{&setting_file};
    QTextCodec *codec=QTextCodec::codecForName("UTF-8");
    stream.setCodec(codec);
    QJsonDocument document;
    document.setObject(obj_);

    stream << document.toJson();
    stream.flush();

    setting_file.close();
}

QJsonObject JsonHandler::getObject() const
{
    return obj_;
}

void JsonHandler::setObject(QJsonObject obj)
{
    obj_ = obj;
}

void JsonHandler::flush() const
{
    writeToFile();
}
