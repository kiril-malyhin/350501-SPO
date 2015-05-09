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
    //bool Stop;
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
    QCheckBox *change_directory_name;
    QCheckBox *change_attributes;
    QCheckBox *change_size;
    QCheckBox *change_last_write;
    QCheckBox *change_last_access;
    QCheckBox *change_creation;
    QCheckBox *change_sequrity;

   // QFile *myFile;
   //QTextStream myText;
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

            //wchar_t filename;
            monitor->MonitorPath(text);

            start->setEnabled(false);
            stop->setEnabled(true);
            enter_path->setEnabled(false);
            catalog->setEnabled(false);

            change_file_name->setEnabled(false);
            change_directory_name->setEnabled(false);
            change_attributes->setEnabled(false);
            change_size->setEnabled(false);
            change_last_write->setEnabled(false);
            change_last_access->setEnabled(false);
            change_creation->setEnabled(false);
            change_sequrity->setEnabled(false);

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

        change_file_name->setEnabled(true);
        change_directory_name->setEnabled(true);
        change_attributes->setEnabled(true);
        change_size->setEnabled(true);
        change_last_write->setEnabled(true);
        change_last_access->setEnabled(true);
        change_creation->setEnabled(true);
        change_sequrity->setEnabled(true);
    }

    void pathSlot()
    {
        text = input_path->text();

        start->setEnabled(true);
        enter_path->setEnabled(true);
        stop->setEnabled(false);
        catalog->setEnabled(true);
        change_file_name->setEnabled(true);
        change_directory_name->setEnabled(true);
        change_attributes->setEnabled(true);
        change_size->setEnabled(true);
        change_last_write->setEnabled(true);
        change_last_access->setEnabled(true);
        change_creation->setEnabled(true);
        change_sequrity->setEnabled(true);
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

    void notificationReceived(QString Status, QString Name)
    {
        //qDebug() << Status;
        //QListWidgetItem *res = new QListWidgetItem;
        //res->setText(Status);
        //res->setForeground(Qt::darkRed);
        data->addItem(Status);
        data->addItem(Name);


        //QString name = qgetenv(“USERNAME”);
        //qDebug() << name;
        //qUsername  = QString::fromLocal8Bit (qgetenv ("USERNAME").constData ()).toUtf8 ();
        QString qUsername = QString::fromLocal8Bit(qgetenv("USERNAME").constData()).toUtf8();
        //qDebug() << qUsername;
        QDate dateToday = QDate::currentDate();
        QString str;
        str = dateToday.toString("dd/MM/yyyy");

        QString str1;
        QTime timeToday = QTime::currentTime();
        str1 = timeToday.toString("hh:mm:ss\n");

        QFile myFile("log.txt");

        if (!myFile.open(QFile::WriteOnly | QFile::Text | QFile::Append)) //открываем файл
        {
            return;
        }

        QTextStream myText(&myFile);

        myText << "User:  ";
        myText << qUsername;
        myText << "\n";
        myText << Status;
        myText << "\n";
        myText << "File:\t";
        myText << Name;
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
