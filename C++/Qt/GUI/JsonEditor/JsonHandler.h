#pragma once
#include <QJsonObject>

class JsonHandler
{
public:
    explicit JsonHandler(const QString& path);
    ~JsonHandler();
    QJsonObject getObject() const;
    void setObject(QJsonObject obj);

    void flush() const;
private:
    void init();

    void writeToFile() const;


private:
    QJsonObject obj_;
    QString path_;
};
