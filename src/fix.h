#ifndef FIX_H
#define FIX_H
/*
*车辆维修
*/
#include <QWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QTableWidget>
#include "connect.h"
class Fix : public QWidget
{
    Q_OBJECT
public:
    explicit Fix(QWidget *parent = 0):QWidget(parent){}
    explicit Fix(Connect *c, QWidget *parent = 0);
private:
    QLabel *lab;  //“车牌”
    QComboBox *cbxSheng;  //省份选择
    QComboBox *cbxZimu;    //车辆省份字母
    QLineEdit *editCarNum;  //输入车牌信息
    QPushButton *btnSearch;  //查询
    QPushButton *btnSearchAll;  //查询所有
    QPushButton *btnAdd;  //添加
    QPushButton *btnEdit;  //修改
    QPushButton *btnDelete;  //删除
    QTableWidget *tableWidget;

    int rowCount; //统计行数
    Connect *conn;   //数据库连接

signals:

public slots:
    void Search();
    void SearchAll();
    void showAddNewInfoDialog();
    void Edit(int,int);
    void Delete();
};

#endif // FIX_H
