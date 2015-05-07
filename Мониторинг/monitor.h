#ifndef MONITOR_H
#define MONITOR_H

#include <QObject>

class Monitor : public QObject
{
    Q_OBJECT
public:
    explicit Monitor(QObject *parent = 0);
    ~Monitor();
    void MonitorPath(QString path);
    wchar_t* convertCharArrayToLPCWSTR(const char* charArray);
    bool Stop;
    //QString fileName;

signals:
    void notification(QString);

public slots:
};

#endif // MONITOR_H
