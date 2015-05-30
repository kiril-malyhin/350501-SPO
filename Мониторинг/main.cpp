#include <QApplication>
#include <QPushButton>
#include <QSpinBox>
#include <QSlider>
#include <QHBoxLayout>
#include <QObject>
#include <QFile>
#include <QTextEdit>
#include <myWindow.h>
#include <QMessageBox>
#include <QDebug>
#include <QDir>
#include <QString>
#include <QFileInfo>
#include <QFileInfoList>
#include <QSystemTrayIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //QApplication::setQuitOnLastWindowClosed(false);
    MyWindow *window = new MyWindow;

    window->show();

    QObject::connect(window->stop, SIGNAL(clicked()), window, SLOT(close()));
    return a.exec();

}

