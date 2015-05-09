#include "monitor.h"

#include <QDebug>

#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>
#include <malloc.h>
#include <locale.h>
#include <tchar.h>


using namespace std;

Monitor::Monitor(QObject *parent) : QObject(parent)
{

        subDirs = true;
        change_file_name = true;

        change_directory_name = true;

        change_attributes = true;

        change_size = true;

        change_last_write = true;

        change_last_access = true;

        change_creation = true;

        change_sequrity = true;

}

Monitor::~Monitor()
{

}

void Monitor::look_subdirs(bool value)
{
    subDirs = value;
}

void Monitor::change_file_nameSlot(bool value)
{

    change_file_name = value;
}

void Monitor::change_dir_nameSlot(bool value)
{
    change_directory_name = value;
}

void Monitor::change_attributesSlot(bool value)
{
    change_attributes = value;
}

void Monitor::change_sizeSlot(bool value)
{
    change_size = value;
}

void Monitor::change_last_writeSlot(bool value)
{
    change_last_write = value;
}

void Monitor::change_last_accessSlot(bool value)
{
    change_last_access = value;
}

void Monitor::change_creationSlot(bool value)
{
    change_creation = value;
}

void Monitor::change_sequritySlot(bool value)
{
    change_sequrity = value;
}

wchar_t *convertCharArrayToLPCWSTR(const char* charArray)
{
    wchar_t* wString = new wchar_t[4096];
    MultiByteToWideChar(CP_ACP, 0, charArray, -1, wString, 4096);
    return wString;
}

wchar_t* Monitor::getFileName(QString text)
{
        setlocale(LC_ALL, "Russian");

        wchar_t filename[MAX_PATH];
        char buf[256 * (sizeof(FILE_NOTIFY_INFORMATION)+MAX_PATH * sizeof(WCHAR))] = { 0 };
        DWORD bytesReturned = 0;
        BOOL result = FALSE;
        FILE_NOTIFY_INFORMATION *fni = NULL;

        wchar_t *path;
        path = new wchar_t[1000];
        text.toWCharArray(path);

        HANDLE hDir = CreateFile(path,
            FILE_LIST_DIRECTORY | STANDARD_RIGHTS_READ,
            FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
            NULL,
            OPEN_EXISTING,
            FILE_FLAG_BACKUP_SEMANTICS,
            NULL);

        while (1)
        {
            result = ReadDirectoryChangesW(hDir,
                buf,
                sizeof(buf) / sizeof(*buf),
                TRUE,
                FILE_NOTIFY_CHANGE_FILE_NAME |
                FILE_NOTIFY_CHANGE_DIR_NAME |
                FILE_NOTIFY_CHANGE_ATTRIBUTES |
                FILE_NOTIFY_CHANGE_SIZE |
                FILE_NOTIFY_CHANGE_LAST_WRITE |
                FILE_NOTIFY_CHANGE_LAST_ACCESS |
                FILE_NOTIFY_CHANGE_CREATION |
                FILE_NOTIFY_CHANGE_SECURITY,
                &bytesReturned,
                NULL,
                NULL);

           // if (result && bytesReturned)

                wchar_t action[256];
                for (fni = (FILE_NOTIFY_INFORMATION*)buf; fni;)
                {
                    wcscpy_s(action, sizeof(action) / sizeof(*action), L"");
                        break;
                }
                if (fni->FileNameLength)
                {
                        wcsncpy_s(filename, MAX_PATH, fni->FileName, fni->FileNameLength / 2);
                        filename[fni->FileNameLength / 2] = 0;
                }

                if (fni->NextEntryOffset)
                {
                        char *p = (char*)fni;
                        fni = (FILE_NOTIFY_INFORMATION*)(p + fni->NextEntryOffset);
                }
                else
                {
                    //qDebug() << "NULL";
                    fni = NULL;
                }
                //else:
                //{
                    wprintf(L"ReadDirectoryChangesW failed\n");
                //}

        //QString Name1 = QString::fromWCharArray(filename, -1);
        return filename;
        //qDebug() << filename;
        }CloseHandle(hDir);
}

void Monitor::MonitorPath(QString text)
{    
wchar_t *path;
path = new wchar_t[1000];
text.toWCharArray(path);
DWORD dwWaitStatus;
HANDLE dwChangeHandles[8];
char* status;
status = (char*)malloc(sizeof(char));
//QString Status;

//change_sequrity = FILE_NOTIFY_CHANGE_SECURITY;

    dwChangeHandles[0] = FindFirstChangeNotification(
    path,                 // директория для просмотра
    subDirs,                         // не просматривать поддиректории
    FILE_NOTIFY_CHANGE_FILE_NAME); // отслеживать изм. имён файлов

if (dwChangeHandles[0] == INVALID_HANDLE_VALUE)
    ExitProcess(GetLastError());


dwChangeHandles[1] = FindFirstChangeNotification(
    path ,                        // директория для просмотра
    subDirs,                          // просматривать поддиректории
    FILE_NOTIFY_CHANGE_DIR_NAME);  // отслеживать изм. имён директорий

if (dwChangeHandles[1] == INVALID_HANDLE_VALUE)
    ExitProcess(GetLastError());

dwChangeHandles[2] = FindFirstChangeNotification(
    path,                 // директория для просмотра
    subDirs,                         // не просматривать поддиректории
    FILE_NOTIFY_CHANGE_ATTRIBUTES); // отслеживать изм. имён файлов

if (dwChangeHandles[2] == INVALID_HANDLE_VALUE)
    ExitProcess(GetLastError());

dwChangeHandles[3] = FindFirstChangeNotification(
    path,                 // директория для просмотра
    subDirs,                         // не просматривать поддиректории
    FILE_NOTIFY_CHANGE_SIZE); // отслеживать изм. имён файлов

if (dwChangeHandles[3] == INVALID_HANDLE_VALUE)
    ExitProcess(GetLastError());

dwChangeHandles[4] = FindFirstChangeNotification(
    path,                 // директория для просмотра
    subDirs,                         // не просматривать поддиректории
    FILE_NOTIFY_CHANGE_LAST_WRITE ); // отслеживать изм. имён файлов

if (dwChangeHandles[4] == INVALID_HANDLE_VALUE)
    ExitProcess(GetLastError());

dwChangeHandles[5] = FindFirstChangeNotification(
    path,                 // директория для просмотра
    subDirs,                         // не просматривать поддиректории
    FILE_NOTIFY_CHANGE_LAST_ACCESS ); // отслеживать изм. имён файлов

if (dwChangeHandles[5] == INVALID_HANDLE_VALUE)
    ExitProcess(GetLastError());

dwChangeHandles[6] = FindFirstChangeNotification(
    path,                 // директория для просмотра
    subDirs,                         // не просматривать поддиректории
    FILE_NOTIFY_CHANGE_CREATION ); // отслеживать изм. имён файлов

if (dwChangeHandles[6] == INVALID_HANDLE_VALUE)
    ExitProcess(GetLastError());

dwChangeHandles[7] = FindFirstChangeNotification(
    path,                 // директория для просмотра
    subDirs,                         // не просматривать поддиректории
    FILE_NOTIFY_CHANGE_SECURITY); // отслеживать изм. имён файлов

if (dwChangeHandles[7] == INVALID_HANDLE_VALUE)
    ExitProcess(GetLastError());

while (TRUE)
{

    // Ждём уведомления.

    dwWaitStatus = WaitForMultipleObjects(8, dwChangeHandles,
        FALSE, INFINITE);

    switch (dwWaitStatus)
    {
        case WAIT_OBJECT_0:

        if(change_file_name == true)
        {

        status = "File was created, deleted or renamed!";
        qDebug() << status;
        }
            if( FindNextChangeNotification(dwChangeHandles[0]) == FALSE )
                ExitProcess(GetLastError());
            break;

        case WAIT_OBJECT_0 + 1:

        if(change_directory_name == true)
        {

              status = "Directory was created, deleted or renamed!";
              qDebug() << status;

        }
            if (FindNextChangeNotification(
                    dwChangeHandles[1]) == FALSE)
                ExitProcess(GetLastError());
            break;

            case WAIT_OBJECT_0 + 2:

        if(change_attributes == true)
        {

                status = "Attributes were changed!";
                qDebug() << status;
        }
            if( FindNextChangeNotification(dwChangeHandles[2]) == FALSE )
                ExitProcess(GetLastError());
            break;

            case WAIT_OBJECT_0 + 3:

        if(change_size == true)
        {

                status = "Size was changed!";
                qDebug() << status;
        }
            if( FindNextChangeNotification(dwChangeHandles[3]) == FALSE )
                ExitProcess(GetLastError());
            break;

            case WAIT_OBJECT_0 + 4:

        if(change_last_write == true)
        {

                status = "Last write time was changed!";
                qDebug() << status;
        }
            if( FindNextChangeNotification(dwChangeHandles[4]) == FALSE )
                ExitProcess(GetLastError());
            break;

            case WAIT_OBJECT_0 + 5:

        if(change_last_access == true)
        {

                status = "Last access was changed!";
                qDebug() << status;
        }
            if( FindNextChangeNotification(dwChangeHandles[5]) == FALSE )
                ExitProcess(GetLastError());
            break;

            case WAIT_OBJECT_0 + 6:

        if(change_creation == true)
        {

                status = "Creation time was changed!";
                qDebug() << status;
        }
            if( FindNextChangeNotification(dwChangeHandles[6]) == FALSE )
                ExitProcess(GetLastError());
            break;

            case WAIT_OBJECT_0 + 7:

        if(change_sequrity == true)
        {

                status = "Sequrity descriptor was changed!";
                qDebug() << status;
        }
            if( FindNextChangeNotification(dwChangeHandles[7]) == FALSE )
                ExitProcess(GetLastError());
            break;

        default:
            ExitProcess(GetLastError());
     }

    QString Status = status;
    wchar_t* mez = getFileName(text);
    //qDebug() << mez;
    QString Name = QString::fromWCharArray(mez, -1);
    qDebug() << getFileName(text);
    qDebug() << Name;
    emit notification(Status, Name);

   }
}





