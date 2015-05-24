#ifndef NAME_H
#define NAME_H


#include <QObject>
#include <QDebug>

#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>
#include <malloc.h>
#include <locale.h>
#include <tchar.h>

class Name : public QObject
{
    Q_OBJECT
private:
    QString *text;
public:
    explicit Name(QString text, bool subDirs, bool change_file_name, bool change_attributes,
                  bool change_size, bool change_last_write, bool change_last_access, bool change_creation, bool change_sequrity);
    ~Name();
    bool subDirs;
    bool change_file_name;
    //change_file_name= FILE_NOTIFY_CHANGE_FILE_NAME;
    bool change_attributes;
    //change_attributes = FILE_NOTIFY_CHANGE_ATTRIBUTES;
    bool change_size;
    //change_size = FILE_NOTIFY_CHANGE_SIZE;
    bool change_last_write;
    //change_last_write = FILE_NOTIFY_CHANGE_LAST_WRITE;
    bool change_last_access;
    //change_last_access = FILE_NOTIFY_CHANGE_LAST_ACCESS;
    bool change_creation;
    //change_creation = FILE_NOTIFY_CHANGE_CREATION;
    bool change_sequrity;

signals:
    void notificationAction(QString, QString);
public slots:
    void start();
};

#endif // NAME_H
