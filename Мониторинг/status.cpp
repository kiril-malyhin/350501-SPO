#include "status.h"

#include <QDebug>

#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>
#include <malloc.h>
#include <locale.h>
#include <tchar.h>

Status::Status(QString text, bool subDirs, bool change_file_name, bool change_directory_name, bool change_attributes,
               bool change_size, bool change_last_write, bool change_last_access, bool change_creation, bool change_sequrity)
{
    this->text = new QString;
    this->text->append(text);

}

Status::~Status()
{

}

void Status::start(){

    qDebug() << "Signal status!";
    QString text("C:/Qt");
    wchar_t *path;
    path = new wchar_t[1000];
    text.toWCharArray(path);
    DWORD dwWaitStatus;
    HANDLE dwChangeHandles[8];
    char* status;
    status = (char*)malloc(sizeof(char));

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
    change_file_name = true;
                       change_directory_name  = true;
                       change_attributes = true;
                       change_size = true;
                       change_last_write = true;
                       change_last_access = true;
                       change_creation = true;
                       change_sequrity = true;

    while (TRUE)//C:/Qt
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
                //qDebug() << status;
            }
            if( FindNextChangeNotification(dwChangeHandles[0]) == FALSE )
                ExitProcess(GetLastError());
            break;

        case WAIT_OBJECT_0 + 1:

            if(change_directory_name == true)
            {

                status = "Directory was created, deleted or renamed!";
                //qDebug() << status;

            }
            if (FindNextChangeNotification(
                        dwChangeHandles[1]) == FALSE)
                ExitProcess(GetLastError());
            break;

        case WAIT_OBJECT_0 + 2:

            if(change_attributes == true)
            {

                status = "Attributes were changed!";
                //qDebug() << status;
            }
            if( FindNextChangeNotification(dwChangeHandles[2]) == FALSE )
                ExitProcess(GetLastError());
            break;

        case WAIT_OBJECT_0 + 3:

            if(change_size == true)
            {
                status = "Size was changed!";
                //qDebug() << status;
            }
            if( FindNextChangeNotification(dwChangeHandles[3]) == FALSE )
                ExitProcess(GetLastError());
            break;

        case WAIT_OBJECT_0 + 4:

            if(change_last_write == true)
            {

                status = "Last write time was changed!";
                //qDebug() << status;
            }
            if( FindNextChangeNotification(dwChangeHandles[4]) == FALSE )
                ExitProcess(GetLastError());
            break;

        case WAIT_OBJECT_0 + 5:

            if(change_last_access == true)
            {
                status = "Last access was changed!";
                //qDebug() << status;
            }
            if( FindNextChangeNotification(dwChangeHandles[5]) == FALSE )
                ExitProcess(GetLastError());
            break;

        case WAIT_OBJECT_0 + 6:

            if(change_creation == true)
            {
                status = "Creation time was changed!";
                //qDebug() << status;
            }
            if( FindNextChangeNotification(dwChangeHandles[6]) == FALSE )
                ExitProcess(GetLastError());
            break;

        case WAIT_OBJECT_0 + 7:

            if(change_sequrity == true)
            {

                status = "Sequrity descriptor was changed!";
                //qDebug() << status;
            }
            if( FindNextChangeNotification(dwChangeHandles[7]) == FALSE )
                ExitProcess(GetLastError());
            break;

        default:
            ExitProcess(GetLastError());
        }
        QString Status = status;
        qDebug() << Status;
        emit notification(Status);

    }
}

