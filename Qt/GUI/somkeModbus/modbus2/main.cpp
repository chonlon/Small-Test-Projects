#include "widget.h"
#include <QApplication>
#include <QMessageBox>
#include <QFileInfo>


#include <windows.h>
#include <Dbghelp.h>

#include <vld.h>
LONG ApplicationCrashHandler(EXCEPTION_POINTERS *pException)
{
    QString strFileName = QString::number(QDateTime::currentMSecsSinceEpoch()) + ".dmp";
    HANDLE hDumpFile = CreateFile((LPCWSTR)strFileName.utf16(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hDumpFile != INVALID_HANDLE_VALUE)
    {
        MINIDUMP_EXCEPTION_INFORMATION dumpInfo;
        dumpInfo.ExceptionPointers = pException;
        dumpInfo.ThreadId = GetCurrentThreadId();
        dumpInfo.ClientPointers = TRUE;
        MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hDumpFile, MiniDumpNormal, &dumpInfo, NULL, NULL);
    }

    EXCEPTION_RECORD* record = pException->ExceptionRecord;
    QString errCode(QString::number(record->ExceptionCode, 16)), errAdr(QString::number((uint)record->ExceptionAddress, 16)), errMod;
    QMessageBox::critical(NULL, "error", strFileName, QMessageBox::Ok);
    return EXCEPTION_EXECUTE_HANDLER;
}

void InitTrace(const QString& strAppFullPath, const QString& strAppName)
{
    SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)ApplicationCrashHandler);
}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFileInfo appFile(QString::fromLocal8Bit(argv[0]));
    InitTrace(appFile.absolutePath(), appFile.baseName());

    Widget w;
    w.show();

    return a.exec();
}
