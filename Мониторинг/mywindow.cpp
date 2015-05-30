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
#include "name.h"



MyWindow::MyWindow(QWidget *parent): QDialog(parent)
{
    MyWindow::setFont (QFont ("Courier", 10));
    setWindowIcon(QIcon(":/Images/3.png"));
    setFixedSize(950,370);

    input_path = new QLineEdit();
    input_path->setStyleSheet("QLineEdit { background-color: lightgrey }");
    input_path->setFixedSize(440,22);
    data = new QListWidget;

    path = new QLabel("<h2><font color = darkblue>Введите путь к папке или диску для слежения:</font></h2>");
    enter_path = new QPushButton("Записать");

    crit = new QLabel("<h2>Критерии отслеживания изменений:</h2>");

    catalog = new QCheckBox("Включать подкаталоги");
    catalog->setChecked(true);

    start = new QPushButton("Старт");
    start->setFixedSize(90,25);
    start->setEnabled(false);

    stop = new QPushButton("Выход");
    stop->setFixedSize(90,25);
    stop->setEnabled(false);

    clear_window = new QPushButton("Очистить окно вывода");

    add_file = new QCheckBox("Добавление файла/папки");
    add_file->setChecked(true);
    delete_file = new QCheckBox("Удаление файла/папки");
    delete_file->setChecked(true);
    rename_file = new QCheckBox("Изменение имени файла/папки");
    rename_file->setChecked(true);
    other_changes = new QCheckBox("Иные изменения файла/папки");
    other_changes->setChecked(true);

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
    end->addWidget(add_file);
    end->addWidget(delete_file);
    end->addWidget(rename_file);
    end->addWidget(other_changes);
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

    name = new Name;

    connect(catalog, SIGNAL(toggled(bool)), name, SLOT(look_subdirs(bool)));
    connect(add_file,SIGNAL(toggled(bool)), name, SLOT(add_fileSlot(bool)));
    connect(delete_file, SIGNAL(toggled(bool)), name, SLOT(delete_fileSlot(bool)));
    connect(rename_file, SIGNAL(toggled(bool)), name, SLOT(rename_fileSlot(bool)));
    connect(other_changes, SIGNAL(toggled(bool)), name, SLOT(other_changesSlot(bool)));

    connect(enter_path, SIGNAL(clicked()), this, SLOT(pathSlot()));
    connect(clear_window, SIGNAL(clicked()), this, SLOT(clearSlot()));
    connect(start, SIGNAL(clicked()), this, SLOT(startSlot()));
}


