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
#include <QThread>
#include "name.h"

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
    QLabel *path;
    QLabel *crit;
    QListWidget *data;
    QLineEdit *input_path;
    QCheckBox *catalog;
    QPushButton *enter_path;
    QPushButton *start;
    QPushButton *stop;
    QPushButton *clear_window;

    QCheckBox *add_file;
    QCheckBox *delete_file;
    QCheckBox *rename_file;
    QCheckBox *other_changes;
    QString str,str1;
    QThread *threadName;
    Name *name;

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

            QThread *threadName = new QThread;
            name->moveToThread(threadName);

            connect(threadName, SIGNAL(started()), name, SLOT(start()));
            connect(name, SIGNAL(notificationAction(QString,QString)), this, SLOT(notificationActionReceived(QString,QString)));

            threadName->start();

            start->setEnabled(false);
            stop->setEnabled(true);
            enter_path->setEnabled(false);
            catalog->setEnabled(false);

            add_file->setEnabled(false);
            delete_file->setEnabled(false);
            rename_file->setEnabled(false);
            other_changes->setEnabled(false);
        }
        else{ data->addItem("Ошибка открытия директории!");}
    }

    void pathSlot()
    {
        text = input_path->text();

        start->setEnabled(true);
        enter_path->setEnabled(true);
        stop->setEnabled(false);
        catalog->setEnabled(true);
        add_file->setEnabled(true);
        delete_file->setEnabled(true);
        rename_file->setEnabled(true);
        other_changes->setEnabled(true);
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

    void notificationActionReceived(QString Action,QString Filename)
    {

        qDebug() << Action;
        qDebug() << Filename;

        QListWidgetItem *wes = new QListWidgetItem;
        wes->setText(Action);
        wes->setForeground(Qt::blue);
        data->addItem(wes);

        QListWidgetItem *vik = new QListWidgetItem;
        vik->setText(Filename);
        vik->setForeground(Qt::darkGreen);
        data->addItem(vik);

        QListWidgetItem *lop = new QListWidgetItem;
        lop->setText("####################################################");
        lop->setForeground(Qt::darkGray);
        data->addItem(lop);

        QString qUsername = QString::fromLocal8Bit(qgetenv("USERNAME").constData()).toUtf8();

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
        myText << Action;
        myText << "\n";
        myText << "File:\t";
        myText << Filename;
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
