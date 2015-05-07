// ConsoleApplication3.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>
#include <malloc.h>
#include <locale.h>
using namespace std;


wchar_t *convertCharArrayToLPCWSTR(const char* charArray)
{
    wchar_t* wString = new wchar_t[4096];
    MultiByteToWideChar(CP_ACP, 0, charArray, -1, wString, 4096);
    return wString;
} //в любое место

void Monitor(char *path)
{
    DWORD dwWaitStatus;
    HANDLE dwChangeHandles[6];
    LPCWSTR dir = convertCharArrayToLPCWSTR(path);
    bool subdirs = true;

    char buf[256 * (sizeof(FILE_NOTIFY_INFORMATION)+MAX_PATH * sizeof(WCHAR))] = { 0 };
    DWORD bytesReturned = 0;
    BOOL result = FALSE;
    FILE_NOTIFY_INFORMATION *fni = NULL;

    HANDLE hDir = CreateFile(dir,
        FILE_LIST_DIRECTORY | STANDARD_RIGHTS_READ,
        FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
        NULL,
        OPEN_EXISTING,
        FILE_FLAG_BACKUP_SEMANTICS,
        NULL);

	if (!hDir || hDir == INVALID_HANDLE_VALUE)
{
    printf("CreateFile failed\n");
    getchar();
	return 0;
	
}
	puts("Waiting for changes...");
	bool i; // для 	start-stop
	int k = 0;	 //flags   k = k | FILE_NOTIFY_CHANGE_FILE_NAME(example)
    while (1)
    {
        result = ReadDirectoryChangesW(hDir,
            buf,
            sizeof(buf) / sizeof(*buf),
            TRUE, /* monitor the entire subtree */	//подкаталоги
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
            wchar_t filename[MAX_PATH];
            wchar_t action[256];
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
                    swprintf_s(action, sizeof(action) / sizeof(*action), L"Unknown action: %ld. File name is:", fni->Action);
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

    }
    CloseHandle(hDir);
}

