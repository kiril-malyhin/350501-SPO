#include "name.h"

#include <QDebug>

#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>
#include <malloc.h>
#include <locale.h>
#include <tchar.h>

Name::Name()
{
    subDirs = true;
    add_file = true;
    delete_file = true;
    rename_file = true;
    other_changes = true;

}

void Name::look_subdirs(bool value)
{
    subDirs = value;
    qDebug() << "Subdirs:";
    qDebug() << subDirs;
}

void Name::add_fileSlot(bool value)
{
    add_file = value;
    qDebug() << "add_file:";
    qDebug() << add_file;
}

void Name::delete_fileSlot(bool value)
{
    delete_file = value;
    qDebug() << "delete_file:";
    qDebug() << delete_file;
}

void Name::rename_fileSlot(bool value)
{
    rename_file = value;
    qDebug() << "rename_file:";
    qDebug() << rename_file;
}

void Name::other_changesSlot(bool value)
{
    other_changes = value;
    qDebug() << "other_changes:";
    qDebug() << other_changes;
}

Name::~Name()
{

}

void Name::start()
{
    qDebug() << "Signal name!";
    setlocale(LC_ALL, "Russian");
    wchar_t action[256];
    wchar_t filename[MAX_PATH];
    char buf[256 * (sizeof(FILE_NOTIFY_INFORMATION)+MAX_PATH * sizeof(WCHAR))] = { 0 };
    DWORD bytesReturned = 0;
    BOOL result = FALSE;
    FILE_NOTIFY_INFORMATION *fni = NULL;

    //QString text("C:/Qt");
    wchar_t *path = L"C:/Qt";
    //wchar_t *path;
    //path = new wchar_t[1000];//C:/Qt
    //text.toWCharArray(path);

    HANDLE hDir = CreateFile(path,
                             FILE_LIST_DIRECTORY | STANDARD_RIGHTS_READ,
                             FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
                             NULL,
                             OPEN_EXISTING,
                             FILE_FLAG_BACKUP_SEMANTICS,
                             NULL);

    if (!hDir || hDir == INVALID_HANDLE_VALUE)
    {
        wprintf(L"CreateFile failed\n");
    }

    while (TRUE)
    {
        result = ReadDirectoryChangesW(hDir,
                                       buf,
                                       sizeof(buf) / sizeof(*buf),
                                       subDirs,
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
                    wcscpy_s(action, sizeof(action) / sizeof(*action), L"File/folder added:");
                    if(add_file == true)
                    {
                        if (fni->FileNameLength)
                        {
                            wcsncpy_s(filename, MAX_PATH, fni->FileName, fni->FileNameLength / 2);
                            filename[fni->FileNameLength / 2] = 0;


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
                        QString Action = QString::fromWCharArray(action, -1);
                        QString Filename = QString::fromWCharArray(filename, -1);
                        emit notificationAction(Action,Filename);

                    }
                    break;

                case FILE_ACTION_REMOVED:
                    wcscpy_s(action, sizeof(action) / sizeof(*action), L"File/folder removed:");
                    if(delete_file == true)
                    {
                        if (fni->FileNameLength)
                        {
                            wcsncpy_s(filename, MAX_PATH, fni->FileName, fni->FileNameLength / 2);
                            filename[fni->FileNameLength / 2] = 0;


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
                        QString Action = QString::fromWCharArray(action, -1);
                        QString Filename = QString::fromWCharArray(filename, -1);
                        emit notificationAction(Action,Filename);
                    }
                    break;

                case FILE_ACTION_MODIFIED:
                    wcscpy_s(action, sizeof(action) / sizeof(*action), L"File/folder modified:");
                    if(other_changes == true)
                    {


                        if (fni->FileNameLength)
                        {
                            wcsncpy_s(filename, MAX_PATH, fni->FileName, fni->FileNameLength / 2);
                            filename[fni->FileNameLength / 2] = 0;

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
                        QString Action = QString::fromWCharArray(action, -1);
                        QString Filename = QString::fromWCharArray(filename, -1);
                        emit notificationAction(Action,Filename);
                    }
                    break;

                case FILE_ACTION_RENAMED_OLD_NAME:
                    wcscpy_s(action, sizeof(action) / sizeof(*action), L"File/folder renamed, was:");
                    if(rename_file == true)
                    {
                        if (fni->FileNameLength)
                        {
                            wcsncpy_s(filename, MAX_PATH, fni->FileName, fni->FileNameLength / 2);
                            filename[fni->FileNameLength / 2] = 0;

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
                        QString Action = QString::fromWCharArray(action, -1);
                        QString Filename = QString::fromWCharArray(filename, -1);
                        emit notificationAction(Action,Filename);
                    }
                    break;

                case FILE_ACTION_RENAMED_NEW_NAME:
                    wcscpy_s(action, sizeof(action) / sizeof(*action), L"File/folder renamed, now is:");
                    if(rename_file == true)
                    {
                        if (fni->FileNameLength)
                        {
                            wcsncpy_s(filename, MAX_PATH, fni->FileName, fni->FileNameLength / 2);
                            filename[fni->FileNameLength / 2] = 0;


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
                        QString Action = QString::fromWCharArray(action, -1);
                        QString Filename = QString::fromWCharArray(filename, -1);
                        emit notificationAction(Action,Filename);

                    }
                    break;

                }

            }
        }

    }
    CloseHandle(hDir);
}
