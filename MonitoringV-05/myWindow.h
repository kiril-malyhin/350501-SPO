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

class MyWindow:public QDialog
{
    Q_OBJECT

public:
    MyWindow(QWidget *parent=0);
    QString text;
    QLabel *path;
    //int catg = 0, fileName = 0, folderName = 0, attr = 0, size = 0, time = 0, seqDesc = 0;
    bool start_stop;
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

        watcher = new QFileSystemWatcher(this);
        watcher->addPath(text);

        disconnect(watcher, SIGNAL(directoryChanged(QString)), this, SLOT(NotifyChanges(QString)));

            //for more inf, to documentation
            dir.setFilter(QDir::Dirs |QDir::Files | QDir::NoDotAndDotDot);
            dir.setSorting(QDir::Size | QDir::Reversed);

            //now lets get files and directories information in the folder
            QFileInfoList list = dir.entryInfoList();
            for(int i=0; i < list.size(); ++i)
            {
                data->addItem(list.at(i).fileName());
            }

            //now we are connecting the watcher object to get it's signals
            connect(watcher, SIGNAL(directoryChanged(QString)), this, SLOT(NotifyChanges(QString)));
            connect(watcher, SIGNAL(fileChanged(QString)), this, SLOT(NotifyChanges(QString)));

            data->addItem("Ожидание изменений в заданной директории...");

            start->setEnabled(false);
            stop->setEnabled(true);
            enter_path->setEnabled(false);
            catalog->setEnabled(false);
            change_file_name->setEnabled(false);
            change_folder_name->setEnabled(false);
            change_attribute->setEnabled(false);
            change_size->setEnabled(false);
            change_time->setEnabled(false);
            change_sequrity_descriptor->setEnabled(false);
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
        change_folder_name->setEnabled(true);
        change_attribute->setEnabled(true);
        change_size->setEnabled(true);
        change_time->setEnabled(true);
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
    // implementation of our function


    void NotifyChanges(const QString &path)
    {
        QStringList oldList, newList;

        //getting the old list from QList View and
        //the new list which is the current files in the folder
        //then compare them together

        for(int i = 0; i< data->count();i++)
        {
            QListWidgetItem *item = data->item(i);
            oldList << item->text();
        }
        qSort(oldList);

        //now getting new status of folder
        QDir dir(path);

        dir.setFilter(QDir::Dirs |QDir::Files | QDir::NoDotAndDotDot);
        dir.setSorting(QDir::Size | QDir::Reversed);


        QFileInfoList list = dir.entryInfoList();
        for(int i=0; i < list.size(); ++i)
        {
            newList <<list.at(i).fileName();

        }
        qSort(newList);

        //Differences between two lists

        QSet<QString> intersection;
        if(oldList.count() > newList.count())
        {
            intersection = oldList.toSet().intersect(newList.toSet());
            foreach(const QString &value, intersection)
            {
                data->addItem(value);
            }
            data->addItem("(!)Файл удален!");
        }else if(oldList.count() < newList.count())
        {
            intersection = newList.toSet().subtract(oldList.toSet());
            foreach(const QString &value, intersection)
            {
                QListWidgetItem *wi = new QListWidgetItem;
                wi->setText(value);
                wi->setForeground(Qt::blue);
                data->addItem(wi);

            }
            data->addItem("(!)Файл добавлен!");
        }else{
            data->addItem("(!)Файл изменен!");

        }

    }

};

#endif
