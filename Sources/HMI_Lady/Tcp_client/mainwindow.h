#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../client.h"
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void editing_IP() ;
    void allow_connect() ;
    void allow_send() ;
    void send_message() ;
    void mark_connection() ;

private:
    Ui::MainWindow *ui;
    client C ;
};

#endif // MAINWINDOW_H
