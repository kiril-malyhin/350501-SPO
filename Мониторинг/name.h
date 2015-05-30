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
    QString *Text;
public:
    explicit Name();
    ~Name();
    bool subDirs;
    bool add_file;
    bool delete_file;
    bool rename_file;
    bool other_changes;
signals:
    void notificationAction(QString, QString);
public slots:
    void start();
    void look_subdirs(bool);
    void add_fileSlot(bool);
    void delete_fileSlot(bool);
    void rename_fileSlot(bool);
    void other_changesSlot(bool);
};



#endif // NAME_H
