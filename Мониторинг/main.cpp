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
#include <QDebug>z
#include <QDir>
#include <QString>
#include <QFileInfo>
#include <QFileInfoList>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //QApplication::setQuitOnLastWindowClosed(false);
    MyWindow *window = new MyWindow;
    window->show();

    return a.exec();
}

