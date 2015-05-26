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
    change_file_name = true;
    change_attributes = true;
    change_size = true;
    change_last_write = true;
    change_last_access = true;
    change_creation = true;
    change_sequrity = true;

    this->text = new QString;
    this->text->append(text);

}

void Name::look_subdirs(bool value)
{
    subDirs = value;
    qDebug() << "Subdirs:";
    qDebug() << subDirs;
}

void Name::change_file_nameSlot(bool value)
{
    change_file_name = value;
}

void Name::change_attributesSlot(bool value)
{
    change_attributes = value;
}

void Name::change_sizeSlot(bool value)
{
    change_size = value;
    qDebug() << "change_size:";
    qDebug() << change_size;

}

void Name::change_last_writeSlot(bool value)
{
    change_last_write = value;
}

void Name::change_last_accessSlot(bool value)
{
    change_last_access = value;
}

void Name::change_creationSlot(bool value)
{
    change_creation = value;
}

void Name::change_sequritySlot(bool value)
{
    change_sequrity = value;
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

    //qDebug() << path;
    if (!hDir || hDir == INVALID_HANDLE_VALUE)
    {
        wprintf(L"CreateFile failed\n");
    }

    qDebug() << "Value from name:";
    qDebug() << subDirs;
    qDebug() << change_file_name;
    qDebug() << change_attributes;
    qDebug() << change_size;
    qDebug() << change_last_write;
    qDebug() << change_last_access;
    qDebug() << change_creation;
    qDebug() << change_sequrity;



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
                                    wcscpy_s(action, sizeof(action) / sizeof(*action), L"File added:");
                                    break;

                                case FILE_ACTION_REMOVED:
                                    wcscpy_s(action, sizeof(action) / sizeof(*action), L"File removed:");
                                    break;

                                case FILE_ACTION_MODIFIED:
                                    wcscpy_s(action, sizeof(action) / sizeof(*action), L"File modified:");
                                    break;

                                case FILE_ACTION_RENAMED_OLD_NAME:
                                    wcscpy_s(action, sizeof(action) / sizeof(*action), L"File renamed, was:");
                                    break;

                                case FILE_ACTION_RENAMED_NEW_NAME:
                                    wcscpy_s(action, sizeof(action) / sizeof(*action), L"File renamed, now is:");
                                    break;

                                default:
                                    swprintf_s(action, sizeof(action) / sizeof(*action), L"Unkonwn action: %ld. File name is:", fni->Action);
                                }
                //swprintf_s(action, sizeof(action) / sizeof(*action), L"File/folder name is:", fni->Action);
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

                QString Action = QString::fromWCharArray(action, -1);
                QString Filename = QString::fromWCharArray(filename, -1);



                if(change_file_name == true)
                {Sleep(100);
                    emit notificationAction(Action,Filename);break;}
                if(change_attributes == true)
                {Sleep(100);
                    emit notificationAction(Action,Filename);break;}
                if(change_size == true)
                {Sleep(100);
                    emit notificationAction(Action,Filename);break;}
                if(change_last_write == true)
                {Sleep(100);
                    emit notificationAction(Action,Filename);break;}
                if(change_last_access == true)
                {Sleep(100);
                    emit notificationAction(Action,Filename);break;}
                if(change_creation == true)
                {Sleep(100);
                    emit notificationAction(Action,Filename);break;}
                if(change_sequrity == true)
                {Sleep(100);
                    emit notificationAction(Action,Filename);break;}

            }
        }

    }
    CloseHandle(hDir);
}
