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

Name::Name(QString text, bool subDirs, bool change_file_name, bool change_attributes,
           bool change_size, bool change_last_write, bool change_last_access, bool change_creation, bool change_sequrity)
{
    this->text = new QString;
    this->text->append(text);

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
    //path = new wchar_t[1000];
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

    change_file_name = true;

    change_attributes = true;
    change_size = true;
    change_last_write = true;
    change_last_access = true;
    change_creation = true;
    change_sequrity = true;

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
                    break;

                case FILE_ACTION_REMOVED:
                    wcscpy_s(action, sizeof(action) / sizeof(*action), L"File/folder removed:");
                    break;

                case FILE_ACTION_MODIFIED:

                    if(change_attributes == true)
                    {swprintf_s(action, sizeof(action) / sizeof(*action), L"Attributes were changed! File name is:", fni->Action);
                    break;}
                    if(change_size == true)
                    {swprintf_s(action, sizeof(action) / sizeof(*action), L"Size was changed! File name is:", fni->Action);
                    break;}
                    if(change_creation == true)
                    {swprintf_s(action, sizeof(action) / sizeof(*action), L"Creation time was changed! File name is:", fni->Action);
                    break;}
                    if(change_last_write == true)
                    {swprintf_s(action, sizeof(action) / sizeof(*action), L"Last write time was changed! File name is:", fni->Action);
                    break;}
                    if(change_last_access == true)
                    {swprintf_s(action, sizeof(action) / sizeof(*action), L"Last access was changed! File name is:", fni->Action);
                    break;}
                    if(change_sequrity == true)
                    {swprintf_s(action, sizeof(action) / sizeof(*action), L"Sequrity descriptor was changed! File name is:", fni->Action);
                    break;}
                    //wcscpy_s(action, sizeof(action) / sizeof(*action), L"File modified:");
                                       //break;

                case FILE_ACTION_RENAMED_OLD_NAME:
                    wcscpy_s(action, sizeof(action) / sizeof(*action), L"File/folder renamed, was:");
                    break;

                case FILE_ACTION_RENAMED_NEW_NAME:
                    wcscpy_s(action, sizeof(action) / sizeof(*action), L"File/folder renamed, now is:");
                    break;
                default:
                    swprintf_s(action, sizeof(action) / sizeof(*action), L"Unknonwn action:", fni->Action);
                }


                //swprintf_s(action, sizeof(action) / sizeof(*action), L"File/folder name is:", fni->Action);
                if (fni->FileNameLength)
                {
                    wcsncpy_s(filename, MAX_PATH, fni->FileName, fni->FileNameLength / 2);
                    filename[fni->FileNameLength / 2] = 0;
                    qDebug() << "action-filename";
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

                    /*qDebug() << change_file_name;

                    qDebug() << change_attributes;
                    qDebug() << change_size;
                    qDebug() << change_last_write;
                    qDebug() << change_last_access;
                    qDebug() << change_creation;
                    qDebug() << change_sequrity;*/

                    if(change_file_name == true)
                    {emit notificationAction(Action,Filename);break;}
                    if(change_attributes == true)
                    {emit notificationAction(Action,Filename);break;}
                    if(change_size == true)
                    {emit notificationAction(Action,Filename);break;}
                    if(change_last_write == true)
                    {emit notificationAction(Action,Filename);break;}
                    if(change_last_access == true)
                    {emit notificationAction(Action,Filename);break;}
                    if(change_creation == true)
                    {emit notificationAction(Action,Filename);break;}
                    if(change_sequrity == true)
                    {emit notificationAction(Action,Filename);break;}

                }
            }

        }
        CloseHandle(hDir);
    }
