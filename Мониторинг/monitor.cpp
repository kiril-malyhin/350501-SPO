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

wchar_t* Monitor::getFileName(QString text)
{
        setlocale(LC_ALL, "Russian");
        wchar_t action[256];
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

            if (result && bytesReturned)
            {

                for (fni = (FILE_NOTIFY_INFORMATION*)buf; fni;)
                {
                    switch (fni->Action)
                    {
                    case FILE_ACTION_ADDED:
                        wcscpy_s(action, sizeof(action) / sizeof(*action), L"File created:");
                        break;

                    case FILE_ACTION_REMOVED:
                        wcscpy_s(action, sizeof(action) / sizeof(*action), L"File deleted:");
                        break;

                    //case FILE_ACTION_MODIFIED:
                        //wcscpy_s(action, sizeof(action) / sizeof(*action), L"File modified:");
                        //break;

                    case FILE_ACTION_RENAMED_OLD_NAME:
                        wcscpy_s(action, sizeof(action) / sizeof(*action), L"File renamed, was:");
                        break;

                    case FILE_ACTION_RENAMED_NEW_NAME:
                        wcscpy_s(action, sizeof(action) / sizeof(*action), L"File renamed, now is:");
                        break;

                    default:
                        swprintf_s(action, sizeof(action) / sizeof(*action), L"File name is %ld:", fni->Action);
                    }


                    if (fni->FileNameLength)
                    {
                        wcsncpy_s(filename, MAX_PATH, fni->FileName, fni->FileNameLength / 2);
                        filename[fni->FileNameLength / 2] = 0;
                        wprintf(L"%s '%s'\n", action, filename);
                    }
                    else
                    {
                        wprintf(L"%s <EMPTY>\n", action);
                    }

                    if (fni->NextEntryOffset)
                    {
                        char *p = (char*)fni;
                        fni = (FILE_NOTIFY_INFORMATION*)(p + fni->NextEntryOffset);
                    }
                    else
                    {
                        fni = NULL;
                    }

                }
            }
            else
            {
                wprintf(L"ReadDirectoryChangesW failed\n");
            }

            QString Action = QString::fromWCharArray(action, -1);
            QString Filename = QString::fromWCharArray(filename, -1);
            qDebug() << Action;
            qDebug() << Filename;
            //emit notificationAction(Action, Filename);
        //qDebug() << filename;
        }
CloseHandle(hDir);
}






