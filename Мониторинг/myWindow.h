#ifndef MYWINDOW_H
#define MYWINDOW_H

#include<QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QListWidget>
#include <QDebug>
#include <QDir>
#include <QString>
#include <QFileInfo>
#include <QFileInfoList>
#include <QFileSystemWatcher>
#include <QFileDialog>
#include <QListWidgetItem>
#include <QtTest/QtTest>
#include <QFile>
#include "monitor.h"


#include <stdlib.h>
#include <tchar.h>
#include <malloc.h>
#include <locale.h>
#include <tchar.h>


#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <iostream>

using namespace std;

class MyWindow:public QDialog
{
    Q_OBJECT

public:
    MyWindow(QWidget *parent=0);
    QString text;
    bool Stop;
    QMimeData *data_to_file;
    QLabel *path;
    QLabel *crit;
    QListWidget *data;
    QLineEdit *input_path;
    QCheckBox *catalog;
    QPushButton *enter_path;
    QPushButton *start;
    QPushButton *stop;
    QPushButton *clear_window;
    QCheckBox *change_file_name;
    QCheckBox *change_folder_name;
    QCheckBox *change_attribute;
    QCheckBox *change_size;
    QCheckBox *change_time;
    QCheckBox *change_sequrity_descriptor;
    QCheckBox *change_dir_name;
    QCheckBox *create_file_folder;

    QFile *myFile;
    QTextStream myText;
    QString str,str1;
    Monitor *monitor;
    QMutex mutex;

private:
    QFileSystemWatcher *watcher;

private slots:

public slots:



    void startSlot()
    {
        QDir dir(text);
        if(dir.exists())
        {
            data->addItem("Программа запущена!");
            data->addItem("Данные из заданной директории:");

            QFileInfoList list = dir.entryInfoList();
            for(int i=0; i < list.size(); ++i)
            {
                if(list.at(i).fileName().toStdString() == "." || list.at(i).fileName().toStdString() == "..")
                        continue;

                data->addItem(list.at(i).fileName());
            }

            data->addItem("Ожидание изменений в заданной директории...");

            start->setEnabled(false);
            stop->setEnabled(true);
            enter_path->setEnabled(false);
            catalog->setEnabled(false);
            create_file_folder->setEnabled(false);
            change_file_name->setEnabled(false);
            change_folder_name->setEnabled(false);
            change_attribute->setEnabled(false);
            change_size->setEnabled(false);
            change_time->setEnabled(false);
            change_dir_name->setEnabled(false);
            change_sequrity_descriptor->setEnabled(false);

            monitor->MonitorPath(text);


        }
        else{ data->addItem("Ошибка открытия директории!");}
    }

    void stopSlot()
    {

        data->addItem("Остановлено!");

        start->setEnabled(true);
        enter_path->setEnabled(true);
        stop->setEnabled(false);
        catalog->setEnabled(true);
        create_file_folder->setEnabled(true);
        change_file_name->setEnabled(true);
        change_folder_name->setEnabled(true);
        change_attribute->setEnabled(true);
        change_size->setEnabled(true);
        change_time->setEnabled(true);
        change_dir_name->setEnabled(true);
        change_sequrity_descriptor->setEnabled(true);
    }

    void pathSlot()
    {
        text = input_path->text();

        start->setEnabled(true);
        enter_path->setEnabled(true);
        stop->setEnabled(false);
        catalog->setEnabled(true);
        change_file_name->setEnabled(true);
        change_folder_name->setEnabled(true);
        change_attribute->setEnabled(true);
        change_size->setEnabled(true);
        change_time->setEnabled(true);
        change_sequrity_descriptor->setEnabled(true);
        data->addItem("Путь к папке или диску:");

        if(text == NULL)
        {

            data->addItem("Путь не введен!");
            data->addItem("");
            start->setEnabled(false);
        }
        else
        {
            data->addItem(text);
        }
    }


    void clearSlot()
    {
        data->clear();
    }

    void notificationReceived(QString Status)
    {

        QListWidgetItem *res = new QListWidgetItem;
        res->setText(Status);
        res->setForeground(Qt::darkRed);
        data->addItem(res);

        QDate dateToday = QDate::currentDate();
        QString str;
        str = dateToday.toString("dd/MM/yyyy");

        QString str1;
        QTime timeToday = QTime::currentTime();
        str1 = timeToday.toString("hh:mm:ss\n");

        QFile myFile("C:/Users/Kirill/Documents/MonitoringV-05/log.txt");

        if (!myFile.open(QFile::WriteOnly | QFile::Text | QFile::Append)) //открываем файл
        {
            return;
        }

        QTextStream myText(&myFile);

        myText << Status;
        myText << "\n";
        myText << "Data:";
        myText << str;
        myText << "\t";
        myText << "Time:";
        myText << str1;
        myText << "\n";
        myText << "###########################################################\n";
    }

};



#endif
