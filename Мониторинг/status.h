#ifndef STATUS_H
#define STATUS_H

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

class Status : public QObject
{
    Q_OBJECT

private:
    QString *text;

public:
    explicit Status();
    ~Status();

    bool subDirs;
    bool change_file_name;
    //change_file_name= FILE_NOTIFY_CHANGE_FILE_NAME;
    bool change_directory_name;
    //change_directory_name = FILE_NOTIFY_CHANGE_DIR_NAME;
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
    void notification(QString);

public slots:
    void start();

   void look_subdirs(bool);
   void change_file_nameSlot(bool);
   void change_attributesSlot(bool);
   void change_sizeSlot(bool);
   void change_last_writeSlot(bool);
   void change_last_accessSlot(bool);
   void change_creationSlot(bool);
   void change_sequritySlot(bool);

};

#endif // STATUS_H
