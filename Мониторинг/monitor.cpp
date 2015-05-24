#include "monitor.h"

#include <QDebug>

#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>
#include <malloc.h>
#include <locale.h>
#include <tchar.h>

using namespace std;

Monitor::Monitor(QObject *parent) : QObject(parent)
{
        subDirs = true;

        change_file_name = true;

        change_attributes = true;

        change_size = true;

        change_last_write = true;

        change_last_access = true;

        change_creation = true;

        change_sequrity = true;

}

Monitor::~Monitor()
{

}

void Monitor::look_subdirs(bool value)
{
    subDirs = value;
}

void Monitor::change_file_nameSlot(bool value)
{

    change_file_name = value;
}

void Monitor::change_attributesSlot(bool value)
{
    change_attributes = value;
}

void Monitor::change_sizeSlot(bool value)
{
    change_size = value;
}

void Monitor::change_last_writeSlot(bool value)
{
    change_last_write = value;
}

void Monitor::change_last_accessSlot(bool value)
{
    change_last_access = value;
}

void Monitor::change_creationSlot(bool value)
{
    change_creation = value;
}

void Monitor::change_sequritySlot(bool value)
{
    change_sequrity = value;
}






