#pragma once
/*
 *Dump Uncatched expection into dumpfile.
 *Only works in windows.
 */


#include <chrono>
#include <ctime>
#include <Dbghelp.h>
#include <iomanip>
#include <iostream>
#include <tchar.h>
#include <vector>
#include <windows.h>

using namespace std;
using namespace std::chrono;

#pragma comment(lib, "Dbghelp.lib")
namespace DumpFile {

void CreateDumpFile(
    LPCWSTR             lpstrDumpFilePathName,
    EXCEPTION_POINTERS* pException) {
    // 创建Dump文件
    //
    HANDLE hDumpFile =
        CreateFile(lpstrDumpFilePathName,
                   GENERIC_WRITE,
                   0,
                   NULL,
                   CREATE_ALWAYS,
                   FILE_ATTRIBUTE_NORMAL,
                   NULL);


    // Dump信息
    //
    MINIDUMP_EXCEPTION_INFORMATION dumpInfo;
    dumpInfo.ExceptionPointers = pException;
    dumpInfo.ThreadId = GetCurrentThreadId();
    dumpInfo.ClientPointers = TRUE;


    // 写入Dump文件内容
    //
    MiniDumpWriteDump(GetCurrentProcess(),
                      GetCurrentProcessId(),
                      hDumpFile,
                      MiniDumpNormal,
                      &dumpInfo,
                      NULL,
                      NULL);


    CloseHandle(hDumpFile);
}


LPTOP_LEVEL_EXCEPTION_FILTER WINAPI
MyDummySetUnhandledExceptionFilter(
    LPTOP_LEVEL_EXCEPTION_FILTER
    lpTopLevelExceptionFilter) {
    return NULL;
}


BOOL PreventSetUnhandledExceptionFilter() {
    HMODULE hKernel32 =
        LoadLibrary(_T("kernel32.dll"));
    if (hKernel32 == NULL)
        return FALSE;


    void* pOrgEntry = GetProcAddress(
    hKernel32,
    "SetUnhandledExceptionFilter");
    if (pOrgEntry == NULL)
        return FALSE;


    unsigned char newJump[100];
    DWORD         dwOrgEntryAddr = (DWORD)
        pOrgEntry;
    dwOrgEntryAddr +=
        5;  // add 5 for 5 op-codes for jmp far


    void* pNewFunc =
        &MyDummySetUnhandledExceptionFilter;
    DWORD dwNewEntryAddr = (DWORD)pNewFunc;
    DWORD dwRelativeAddr =
        dwNewEntryAddr - dwOrgEntryAddr;


    newJump[0] = 0xE9;  // JMP absolute
    memcpy(&newJump[1],
           &dwRelativeAddr,
           sizeof(pNewFunc));
    SIZE_T bytesWritten;
    BOOL   bRet =
        WriteProcessMemory(GetCurrentProcess(),
                           pOrgEntry,
                           newJump,
                           sizeof(pNewFunc) + 1,
                           &bytesWritten);
    return bRet;
}

LONG WINAPI UnhandledExceptionFilterEx(
    struct _EXCEPTION_POINTERS* pException) {
    TCHAR szMbsFile[MAX_PATH] = {0};
    ::GetModuleFileName(
    NULL,
    szMbsFile,
    MAX_PATH);
    TCHAR* pFind = _tcsrchr(szMbsFile, '\\');
    if (pFind) {
        *(pFind + 1) = 0;

        char      buffer[80];
        time_t    rawtime;
        struct tm info;
        time(&rawtime);
        localtime_s(&info, &rawtime);
        TCHAR szMbsFile[MAX_PATH] = {0};
        strftime(buffer,
                 80,
                 "%Y-%m-%d %H-%M-%S",
                 &info);
        std::string strName = buffer;
        strName += ".dmp";
        _stprintf_s(szMbsFile,
                    MAX_PATH,
                    _T("%S"),
                    strName.c_str());
        CreateDumpFile(szMbsFile, pException);
    }


    // TODO: MiniDumpWriteDump
    FatalAppExit(-1, _T("Fatal Error"));
    return EXCEPTION_CONTINUE_SEARCH;
}


void RunCrashHandler() {
    SetUnhandledExceptionFilter(
    UnhandledExceptionFilterEx);
    PreventSetUnhandledExceptionFilter();
}

}  // namespace DumpFile

using DumpFile::RunCrashHandler;
