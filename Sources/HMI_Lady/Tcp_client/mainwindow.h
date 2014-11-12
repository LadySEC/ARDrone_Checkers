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
    void link_connect() ;


public slots:
    void open_connexion();
    void send_takeoff() ;
    void send_landing() ;
    void send_exit() ;
    void mark_connexion() ;
    void unmark_connexion() ;

private:
    void allow_sending() ;
    void forbid_sending() ;
    Ui::MainWindow *ui;
    client C ;
};

#endif // MAINWINDOW_H
