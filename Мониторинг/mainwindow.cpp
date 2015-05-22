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
    /*trIcon = new QSystemTrayIcon();  //инициализируем объект
    trIcon->setIcon(QIcon(":/Images/31.ico"));  //устанавливаем иконку
    trIcon->show();  //отображаем объект

    connect(trIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(showHide(QSystemTrayIcon::ActivationReason)));*/
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*BOOL TrayMessage(HWND hDlg, DWORD dwMessage, UINT uID, HICON hIcon, PSTR pszTip)
{
        BOOL res;

    NOTIFYICONDATA tnd;

    tnd.cbSize      = sizeof(NOTIFYICONDATA);
    tnd.hWnd        = hDlg;
    tnd.uID         = uID;

    tnd.uFlags      = NIF_MESSAGE|NIF_ICON|NIF_TIP;
    tnd.uCallbackMessage    = MYWM_NOTIFYICON;
    tnd.hIcon       = hIcon;
    if (pszTip)
    {
        lstrcpyn(tnd.szTip, pszTip, sizeof(tnd.szTip));
    }
    else
    {
        tnd.szTip[0] = '\0';
    }

    res = Shell_NotifyIcon(dwMessage, &tnd);

    if (hIcon)
        DestroyIcon(hIcon);

    return res;
}*/
/*void MainWindow::showHide(QSystemTrayIcon::ActivationReason reason) {
    if (reason==QSystemTrayIcon::Trigger)  //если нажато левой кнопкой продолжаем
    if (!this->isVisible()) {  //если окно было не видимо - отображаем его
        this->show();
    } else {
        this->hide();  //иначе скрываем
    }
}*/


