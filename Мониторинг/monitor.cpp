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

}

Monitor::~Monitor()
{

}



void Monitor::MonitorPath(QString text)
{    

DWORD dwWaitStatus;
HANDLE dwChangeHandles[8];
char* status;
status = (char*)malloc(sizeof(char));
//QString Status;
bool subDirs = true;
bool change_file_name = true;
change_file_name= FILE_NOTIFY_CHANGE_FILE_NAME;
bool change_directory_name = true;
change_directory_name = FILE_NOTIFY_CHANGE_DIR_NAME;
bool change_attributes = true;
change_attributes = FILE_NOTIFY_CHANGE_ATTRIBUTES;
bool change_size = true;
change_size = FILE_NOTIFY_CHANGE_SIZE;
bool change_last_write = true;
change_last_write = FILE_NOTIFY_CHANGE_LAST_WRITE;
bool change_last_access = true;
change_last_access = FILE_NOTIFY_CHANGE_LAST_ACCESS;
bool change_creation = true;
change_creation = FILE_NOTIFY_CHANGE_CREATION;
bool change_sequrity = true;
change_sequrity = FILE_NOTIFY_CHANGE_SECURITY;

// дескриптор для отслеживания директории C:\WINDOWS на создание
// и удаление файлов.
    wchar_t *path;
    path = new wchar_t[1000];
    text.toWCharArray(path);
 //LPCWSTR path = convertCharArrayToLPCWSTR(text);// сделать правильную конвертацию
// QString result = QString::fromWCharArray(action, -1);

    dwChangeHandles[0] = FindFirstChangeNotification(
    path,                 // директория для просмотра
    subDirs,                         // не просматривать поддиректории
    change_file_name); // отслеживать изм. имён файлов

if (dwChangeHandles[0] == INVALID_HANDLE_VALUE)
    ExitProcess(GetLastError());


dwChangeHandles[1] = FindFirstChangeNotification(
    path ,                        // директория для просмотра
    subDirs,                          // просматривать поддиректории
    change_directory_name);  // отслеживать изм. имён директорий

if (dwChangeHandles[1] == INVALID_HANDLE_VALUE)
    ExitProcess(GetLastError());

dwChangeHandles[2] = FindFirstChangeNotification(
    path,                 // директория для просмотра
    subDirs,                         // не просматривать поддиректории
    change_attributes); // отслеживать изм. имён файлов

if (dwChangeHandles[2] == INVALID_HANDLE_VALUE)
    ExitProcess(GetLastError());

dwChangeHandles[3] = FindFirstChangeNotification(
    path,                 // директория для просмотра
    subDirs,                         // не просматривать поддиректории
    change_size); // отслеживать изм. имён файлов

if (dwChangeHandles[3] == INVALID_HANDLE_VALUE)
    ExitProcess(GetLastError());

dwChangeHandles[4] = FindFirstChangeNotification(
    path,                 // директория для просмотра
    subDirs,                         // не просматривать поддиректории
    change_last_write ); // отслеживать изм. имён файлов

if (dwChangeHandles[4] == INVALID_HANDLE_VALUE)
    ExitProcess(GetLastError());

dwChangeHandles[5] = FindFirstChangeNotification(
    path,                 // директория для просмотра
    subDirs,                         // не просматривать поддиректории
    change_last_access ); // отслеживать изм. имён файлов

if (dwChangeHandles[5] == INVALID_HANDLE_VALUE)
    ExitProcess(GetLastError());

dwChangeHandles[6] = FindFirstChangeNotification(
    path,                 // директория для просмотра
    subDirs,                         // не просматривать поддиректории
    change_creation ); // отслеживать изм. имён файлов

if (dwChangeHandles[6] == INVALID_HANDLE_VALUE)
    ExitProcess(GetLastError());

dwChangeHandles[7] = FindFirstChangeNotification(
    path,                 // директория для просмотра
    subDirs,                         // не просматривать поддиректории
    change_sequrity); // отслеживать изм. имён файлов

if (dwChangeHandles[7] == INVALID_HANDLE_VALUE)
    ExitProcess(GetLastError());
// Итак, уведомления об изменениях установлены. Теперь ожидаем
// уведомления от дескрипторов и производим необходимое обновление.

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
                status = "File was created or deleted!";
                qDebug() << status;
                break;

            }
            else if(change_file_name == false)
            {
                break;
            }

            if( FindNextChangeNotification(dwChangeHandles[0]) == FALSE )
                ExitProcess(GetLastError());
            break;

        case WAIT_OBJECT_0 + 1:

            if(change_directory_name == true)
            {
                status = "Directory was created or deleted!";
                qDebug() << status;
                break;

            }
            else if(change_directory_name == false)
            {
                break;
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
                break;

            }
            else if(change_attributes == false)
            {
                break;
            }



            if( FindNextChangeNotification(dwChangeHandles[2]) == FALSE )
                ExitProcess(GetLastError());
            break;

            case WAIT_OBJECT_0 + 3:

            if(change_size == true)
            {
                status = "Size was changed!";
                qDebug() << status;
                break;

            }
            else if(change_size == false)
            {
                break;
            }


            if( FindNextChangeNotification(dwChangeHandles[3]) == FALSE )
                ExitProcess(GetLastError());
            break;

            case WAIT_OBJECT_0 + 4:

            if(change_last_write == true)
            {
                status = "Last write time was changed!";
                qDebug() << status;
                break;

            }
            else if(change_last_write == false)
            {
                break;
            }

            if( FindNextChangeNotification(dwChangeHandles[4]) == FALSE )
                ExitProcess(GetLastError());
            break;

            case WAIT_OBJECT_0 + 5:


            if(change_last_access == true)
            {
                status = "Last access was changed!";
                qDebug() << status;
                break;

            }
            else if(change_last_access == false)
            {
                break;
            }

            if( FindNextChangeNotification(dwChangeHandles[5]) == FALSE )
                ExitProcess(GetLastError());
            break;

            case WAIT_OBJECT_0 + 6:

            if(change_last_access == true)
            {
                status = "Creation time was changed!";
                qDebug() << status;
                break;

            }
            else if(change_last_access == false)
            {
                break;
            }


            if( FindNextChangeNotification(dwChangeHandles[6]) == FALSE )
                ExitProcess(GetLastError());
            break;

            case WAIT_OBJECT_0 + 7:

            if(change_last_access == true)
            {
                status = "Sequrity descriptor was changed!";
                qDebug() << status;
                break;

            }
            else if(change_last_access == false)
            {
                break;
            }

            if( FindNextChangeNotification(dwChangeHandles[7]) == FALSE )
                ExitProcess(GetLastError());
            break;

        default:
            ExitProcess(GetLastError());


     }
    //QString Status = QString::fromWCharArray(status, -1);
    QString Status = status;
    emit notification(Status);

   }
}


wchar_t* Monitor::convertCharArrayToLPCWSTR(const char* charArray)
{
    wchar_t* wString = new wchar_t[4096];
    MultiByteToWideChar(CP_ACP, 0, charArray, -1, wString, 4096);
    return wString;
}


