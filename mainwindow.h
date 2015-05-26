#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<tins/tins.h>
#include "mainwindow.h"
#include "ui_mainwindow.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    static bool callback(const Tins::PDU &pdu);
    static bool callbackport(const Tins::PDU &pdu);
    static bool callbackdest(const Tins::PDU &pdu);

    void nothing(char *s);


private slots:
    void on_pushButton_clicked();

    void on_pushButton_pressed();

private:
    Ui::MainWindow *ui;


};

#endif // MAINWINDOW_H
