#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include "connect.h"
class Client : public QWidget
{
    Q_OBJECT
public:
    explicit Client(QWidget *parent = 0):QWidget(parent){}
    explicit Client(Connect *c, QWidget *parent = 0);
private:
    QLabel *labName;
    QLineEdit *editName;
    QPushButton *btnSearch;
    QPushButton *btnSearchAll;
    QPushButton *btnAdd;  //添加
    QPushButton *btnEdit;
    QTableWidget *clientTable;

    QLabel *labShowCarId;
    QLabel *ShowCarId;
    QLabel *labShowName;
    QLabel *ShowName;
    QLabel *labShowPhone;
    QLabel *ShowPhone;
    QLabel *labShowAddress;
    QLabel *ShowAddress;
    QLabel *labShowRemark;
    QLabel *ShowRemark;

    int rowCount; //统计行数
    Connect *conn;   //数据库连接
signals:

public slots:
    void addNewClient();
    void editClient();
    void SearchClient();
    void SearchAll();
};

#endif // CLIENT_H
