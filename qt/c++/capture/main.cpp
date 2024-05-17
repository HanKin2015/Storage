#include "mainwindow.h"
#include <QApplication>

#include <Windows.h>
#include <QDateTime>
#include <DbgHelp.h>

// 生成dump文件
LONG ApplicationCrashHandler(EXCEPTION_POINTERS *pException)
{
    qDebug("%s:%d", __FUNCTION__, __LINE__);
    QDateTime CurDTime = QDateTime::currentDateTime();
    QString current_date = CurDTime.toString("yyyy_MM_dd_hh_mm_ss");
    //dmp文件的命名
    QString dumpText = "Dump_"+current_date+".dmp";
    EXCEPTION_RECORD *record = pException->ExceptionRecord;
    QString errCode(QString::number(record->ExceptionCode, 16));
    uintptr_t ptrValue = reinterpret_cast<uintptr_t>(record->ExceptionAddress);
    uint value = static_cast<uint>(ptrValue);
    QString errAddr(QString::number(value, 16));
    QString errFlag(QString::number(record->ExceptionFlags, 16));
    QString errPara(QString::number(record->NumberParameters, 16));
    HANDLE DumpHandle = CreateFile((LPCWSTR)dumpText.utf16(),
                                   GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if(DumpHandle != INVALID_HANDLE_VALUE) {
        MINIDUMP_EXCEPTION_INFORMATION dumpInfo;
        dumpInfo.ExceptionPointers = pException;
        dumpInfo.ThreadId = GetCurrentThreadId();
        dumpInfo.ClientPointers = TRUE;
        //将dump信息写入dmp文件
        MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), DumpHandle, MiniDumpNormal, &dumpInfo, NULL, NULL);
        CloseHandle(DumpHandle);
    }
    QString msg = QString("ErrorCode%1  ErrorAddr：%2  ErrorFlag:%3 ErrorPara:%4").arg(errCode).arg(errAddr).arg(errFlag).arg(errPara);
    qDebug() << msg;
    return EXCEPTION_EXECUTE_HANDLER;
}

int main(int argc, char *argv[])
{
    SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)ApplicationCrashHandler);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
