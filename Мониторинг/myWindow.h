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

class MyWindow:public QDialog
 {
    Q_OBJECT

public:
    MyWindow(QWidget *parent=0);

    QLabel *path;
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
public slots:
    void program();

    void startSlot()
    {

           data->addItem("Программа запущена!");
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
        QString text = input_path->text();
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
       // bool ok;
       // int vall = text.toInt(&ok, 16);
    }

    void clearSlot()
    {
       data->clear();
    }

    // for(int i = 0; i < 30; i++)
    // {
    //      data->addItem(QString::number(i) + "item");
    // }
};

#endif
