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
    createActions();
    createTrayIcon();
    trayIcon->show();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(trayIcon->isVisible())
    {
        hide();
        event->ignore();
    }
}

void MainWindow::createActions()
{
    restoreAction = new QAction(tr("&restore"), this);
    connect(restoreAction, SIGNAL(triggered()), this, SLOT(showNormal()));
    quitAction = new QAction(tr("&exit"), this);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
}

void MainWindow::createTrayIcon()
{
    //trayIconMenu = QMenu(this);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);
    trayIcon = new QSystemTrayIcon(this);
    QIcon icon(":/icon/123.png");
    trayIcon->setIcon(icon);
    trayIcon->setContextMenu(trayIconMenu);
}
