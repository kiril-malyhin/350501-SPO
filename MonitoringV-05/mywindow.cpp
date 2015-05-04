#include "myWindow.h"
#include <QButtonGroup>
#include <QAction>
#include <QTextStream>
#include <QModelIndex>
#include <QDate>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QIcon>
#include <QString>
#include <QStringData>
#include <QDir>
#include <QFileInfo>
#include <QDebug>
#include <QFileDialog>
#include <QFileSystemWatcher>
#include <QListWidgetItem>

MyWindow::MyWindow(QWidget *parent): QDialog(parent)
{
    MyWindow::setFont (QFont ("Courier", 10));
    setWindowIcon(QIcon(":/Images/3.png"));
    setFixedSize(950,350);

    input_path = new QLineEdit();
    input_path->setStyleSheet("QLineEdit { background-color: lightgrey }");

    data = new QListWidget;

    path = new QLabel("<h2><font color = darkblue>Введите путь к папке или диску для слежения</font></h2>");
    enter_path = new QPushButton("Записать");

    catalog = new QCheckBox("Включать подкаталоги");
    catalog->setChecked(true);

    start = new QPushButton("Старт");
    //start->setText(vall);
    start->setFixedSize(90,25);
    start->setEnabled(false);

    stop = new QPushButton("Стоп");
    stop->setFixedSize(90,25);
    stop->setEnabled(false);

    clear_window = new QPushButton("Очистить окно вывода");

    change_file_name = new QCheckBox("Изменение имени файла");
    change_file_name->setChecked(true);
    change_folder_name = new QCheckBox("Изменение имени папки");
    change_folder_name->setChecked(true);
    change_attribute = new QCheckBox("Изменение любого атрибута файла/папки");
    change_attribute->setChecked(true);
    change_size = new QCheckBox("Изменение размера файла/папки");
    change_size->setChecked(true);
    change_time = new QCheckBox("Изменение последнего времени записи файла/папки");
    change_time->setChecked(true);
    change_sequrity_descriptor = new QCheckBox("Изменение содержимого дескриптора безопасности в наблюдаемой директории");
    change_sequrity_descriptor->setChecked(true);

    QHBoxLayout *layout_data = new QHBoxLayout;
    layout_data->addWidget(data);

    QHBoxLayout *layout_11 = new QHBoxLayout;
    layout_11->addWidget(input_path);
    layout_11->addWidget(enter_path);

    QVBoxLayout *layout_1 = new QVBoxLayout;
    layout_1->addWidget(path);
    layout_1->addLayout(layout_11);

    QVBoxLayout *layout_2 = new QVBoxLayout;
    layout_2->addWidget(catalog);

    QVBoxLayout *layout_3 = new QVBoxLayout;
    layout_3->addWidget(start);
    layout_3->addWidget(stop);

    QVBoxLayout *end = new QVBoxLayout;
    end->addWidget(change_file_name);
    end->addWidget(change_folder_name);
    end->addWidget(change_attribute);
    end->addWidget(change_size);
    end->addWidget(change_time);
    end->addWidget(change_sequrity_descriptor);
    end->addWidget(clear_window);

    QVBoxLayout *left = new QVBoxLayout;
    left->addLayout(layout_1);
    left->addLayout(layout_2);
    left->addLayout(layout_3);

    QVBoxLayout *up = new QVBoxLayout;
    up->addLayout(layout_data);

    QVBoxLayout *down = new QVBoxLayout;
    down->addLayout(left);
    down->addLayout(end);

    QHBoxLayout *main = new QHBoxLayout;
    main->addLayout(up);
    main->addLayout(down);

    setLayout(main);
    setWindowTitle("Мониторинг изменений файловой системы");
    connect(enter_path, SIGNAL(clicked()), this, SLOT(pathSlot()));
    connect(clear_window, SIGNAL(clicked()), this, SLOT(clearSlot()));
    connect(start, SIGNAL(clicked()), this, SLOT(startSlot()));
    connect(stop, SIGNAL(clicked()), this, SLOT(stopSlot()));

}


