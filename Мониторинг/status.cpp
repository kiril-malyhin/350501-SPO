#include "status.h"

#include <QDebug>

#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>
#include <malloc.h>
#include <locale.h>
#include <tchar.h>

Status::Status()
{
    subDirs = true;
    change_attributes = true;
    change_size = true;
    change_last_write = true;
    change_last_access = true;
    change_creation = true;
    change_sequrity = true;
}

Status::~Status()
{

}

void Status::look_subdirs(bool value)
{
    subDirs = value;
    qDebug() << subDirs;
}

void Status::change_attributesSlot(bool value)
{
    change_attributes = value;
}

void Status::change_sizeSlot(bool value)
{
    change_size = value;
}

void Status::change_last_writeSlot(bool value)
{
    change_last_write = value;
}

void Status::change_last_accessSlot(bool value)
{
    change_last_access = value;
}

void Status::change_creationSlot(bool value)
{
    change_creation = value;
}

void Status::change_sequritySlot(bool value)
{
    change_sequrity = value;
}

void Status::start(){

    qDebug() << "Signal status!";
    QString text("C:/Qt");
    wchar_t *path;
    path = new wchar_t[1000];
    text.toWCharArray(path);

}

