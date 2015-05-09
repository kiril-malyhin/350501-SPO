#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSystemTrayIcon>
#include <QMenu>
#include <QMessageBox>
#include <QMainWindow>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    trIcon = new QSystemTrayIcon();  //инициализируем объект
    trIcon->setIcon(QIcon(":/Images/31.ico"));  //устанавливаем иконку
    trIcon->show();  //отображаем объект

    connect(trIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(showHide(QSystemTrayIcon::ActivationReason)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showHide(QSystemTrayIcon::ActivationReason reason) {
    if (reason==QSystemTrayIcon::Trigger)  //если нажато левой кнопкой продолжаем
    if (!this->isVisible()) {  //если окно было не видимо - отображаем его
        this->show();
    } else {
        this->hide();  //иначе скрываем
    }
}


