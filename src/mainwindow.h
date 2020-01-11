#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QLineEdit>
#include <QPushButton>
#include "connect.h"
#include <QCloseEvent>   //监听关闭事件
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0): QMainWindow(parent){}
    MainWindow(Connect *c, QString Limit, QString username, QWidget *parent = 0);
    ~MainWindow();
private:
    QTabWidget *tabWidget;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    Connect *conn;
protected:
    void closeEvent(QCloseEvent *event);
};

#endif // MAINWINDOW_H
