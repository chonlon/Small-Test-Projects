#ifndef LP_COMMANDPROCESS_H__
#define LP_COMMANDPROCESS_H__

#include <QString>

#include <QRunnable>
#include <QThreadPool> 

class CCompressTask : public QObject, public QRunnable
{
    Q_OBJECT
public:
    CCompressTask(const QString& src, const QString& dst, bool bzip=true);
    ~CCompressTask();

    void run();
signals:
    void sigTaskFinished(const QString&, const QString&, int, bool);
private:
    QString m_sSrc;
    QString m_sDst;
    bool m_bzip;
};

#endif //LP_COMMANDPROCESS_H__