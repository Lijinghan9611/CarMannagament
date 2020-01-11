#ifndef USERMANAGEMENT_H
#define USERMANAGEMENT_H

#include <QWidget>
#include "connect.h"
#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QTableWidget>
#include <QComboBox>
#include <QLineEdit>
class UserManagement : public QWidget
{
    Q_OBJECT
public:
    explicit UserManagement(QWidget *parent = 0):QWidget(parent){}
    explicit UserManagement(Connect *c, QString Username1,QWidget *parent = 0);
private:
    QLabel *labName;
    QLabel *labPwd;
    QLineEdit *editName;
    QLineEdit *editPwd;
    QComboBox *cbxUserType;
    QPushButton *addBtn;
    QPushButton *deleteBtn;
    QTableWidget *tableUser;

    QString userName;
    int rowCount = 0;
    Connect *conn;   //数据库连接
signals:

public slots:
    void Edit(int, int);
    void UserAdd();
    void UserDelete();
    void showAllUser();
};

#endif // USERMANAGEMENT_H
