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

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyWindow *window = new MyWindow;
    window->show();


   // QMessageBox::informativeText();
    /*QMessageBox::information();
    switch( QMessageBox::question(
                    this,
                    tr("Application Name"),
                    tr("An information message."),

                    QMessageBox::Yes |
                    QMessageBox::No |
                    QMessageBox::Cancel,

                    QMessageBox::Cancel ) )
        {
          case QMessageBox::Yes:
            qDebug( "yes" );
            break;
          case QMessageBox::No:
            qDebug( "no" );
            break;
          case QMessageBox::Cancel:
            qDebug( "cancel" );
            break;
          default:
            qDebug( "close" );
            break;
        }*/

    return a.exec();
}

