#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include "monitor.h"
#include "myWindow.h"
class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = 0);
    // подключаем метод run(), который будет отвечать за запуск потока
    //void run();
    // переменная для остановки потока
    bool Stop;
    QMutex myMutex;
    Monitor *M;
signals:
public slots:
public:


};

#endif // MYTHREAD_H
