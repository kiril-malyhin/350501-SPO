#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSystemTrayIcon>
#include <QMenu>
#include <QMessageBox>
#include <QMainWindow>
#include <QtGui>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    trayIcon = new QSystemTrayIcon(this);
    QIcon icon(":/icon/i_tilde_blue.png");
    trayIcon->setIcon(icon);
    trayIcon->show();

}

MainWindow::~MainWindow()
{
    delete ui;
}




