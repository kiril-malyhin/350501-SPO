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
    QString *path;

public:
    explicit Status(QString path);
    ~Status();


signals:
    void notification(QString);
    void notificationAction(QString, QString);
public slots:
    void start(QString text,bool subDirs,

    bool change_file_name,

    bool change_directory_name,

    bool change_attributes,

    bool change_size,

    bool change_last_write,

    bool change_last_access,

    bool change_creation,

    bool change_sequrity);
};

#endif // STATUS_H
