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

    path = new QLabel("<h2><font color = darkblue>Введите путь к папке или диску для слежения:</font></h2>");
    enter_path = new QPushButton("Записать");

    crit = new QLabel("<h2>Критерии отслеживания изменений:</h2>");

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

    change_file_name = new QCheckBox("Изменение имени файла/папки");
    change_file_name->setChecked(true);
    change_attributes = new QCheckBox("Изменение любого атрибута файла/папки");
    change_attributes->setChecked(true);
    change_size = new QCheckBox("Изменение размера файла/папки");
    change_size->setChecked(true);
    change_last_write = new QCheckBox("Изменение времени доступа к файлу/папке");
    change_last_write->setChecked(true);
    change_last_access = new QCheckBox("Изменение времени записи");
    change_last_access->setChecked(true);
    change_creation = new QCheckBox("Изменение времени создания файла/папки");
    change_creation->setChecked(true);
    change_sequrity = new QCheckBox("Изменение содержимого дескриптора безопасности в наблюдаемой директории");
    change_sequrity->setChecked(true);

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
    end->addWidget(change_attributes);
    end->addWidget(change_size);
    end->addWidget(change_last_write);
    end->addWidget(change_last_access);
    end->addWidget(change_creation);
    end->addWidget(change_sequrity);
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

    connect(catalog, SIGNAL(toggled(bool)), monitor, SLOT(look_subdirs(bool)));
    connect(change_file_name,SIGNAL(toggled(bool)), monitor, SLOT(change_file_nameSlot(bool)));
    connect(change_attributes, SIGNAL(toggled(bool)), monitor, SLOT(change_attributesSlot(bool)));
    connect(change_size, SIGNAL(toggled(bool)), monitor, SLOT(change_sizeSlot(bool)));
    connect(change_last_write, SIGNAL(toggled(bool)), monitor, SLOT(change_last_writeSlot(bool)));
    connect(change_last_access, SIGNAL(toggled(bool)), monitor, SLOT(change_last_accessSlot(bool)));
    connect(change_creation, SIGNAL(toggled(bool)), monitor, SLOT(change_creationSlot(bool)));
    connect(change_sequrity, SIGNAL(toggled(bool)), monitor, SLOT(change_sequritySlot(bool)));

    //connect(monitor, &Monitor::notification, this, &MyWindow::notificationReceived);
    //connect(monitor, &Monitor::notificationAction, this, &MyWindow::notificationReceived);
}


