#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private slots:
    void showHide(QSystemTrayIcon::ActivationReason);

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QSystemTrayIcon *trIcon;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
