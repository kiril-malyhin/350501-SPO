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

#include "monitor.h"

MyWindow::MyWindow(QWidget *parent): QDialog(parent)
{
    MyWindow::setFont (QFont ("Courier", 10));
    setWindowIcon(QIcon(":/Images/3.png"));
    setFixedSize(950,450);

    input_path = new QLineEdit();
    input_path->setStyleSheet("QLineEdit { background-color: lightgrey }");

    data = new QListWidget;

    path = new QLabel("<h2><font color = darkblue>Введите путь к папке или диску для слежения</font></h2>");
    enter_path = new QPushButton("Записать");

    crit = new QLabel("<h2>Критерии отслеживания изменений</h2>");

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
    change_time = new QCheckBox("Изменение времени доступа к файлу/папке");
    change_time->setChecked(true);
    change_sequrity_descriptor = new QCheckBox("Изменение содержимого дескриптора безопасности в наблюдаемой директории");
    change_sequrity_descriptor->setChecked(true);
    change_dir_name = new QCheckBox("Изменение времени записи");
    change_dir_name->setChecked(true);
    create_file_folder = new QCheckBox("Изменение времени создания файла/папки");
    create_file_folder->setChecked(true);

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

    QVBoxLayout *layout_4 = new QVBoxLayout;
    layout_4->addWidget(crit);

    QVBoxLayout *end = new QVBoxLayout;
    end->addWidget(change_file_name);
    end->addWidget(change_folder_name);
    end->addWidget(create_file_folder);
    end->addWidget(change_attribute);
    end->addWidget(change_size);
    end->addWidget(change_time);
    end->addWidget(change_dir_name);
    end->addWidget(change_sequrity_descriptor);
    end->addWidget(clear_window);

    QVBoxLayout *left = new QVBoxLayout;
    left->addLayout(layout_1);
    left->addLayout(layout_2);
    left->addLayout(layout_3);
    left->addLayout(layout_4);

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

    monitor = new Monitor();
    connect(monitor, &Monitor::notification, this, &MyWindow::notificationReceived);

}
