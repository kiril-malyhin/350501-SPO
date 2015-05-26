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
    explicit Name();
    ~Name();
    bool subDirs;
    bool change_file_name;
    bool change_attributes;
    bool change_size;
    bool change_last_write;
    bool change_last_access;
    bool change_creation;
    bool change_sequrity;

signals:
    void notificationAction(QString, QString);
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



#endif // NAME_H
