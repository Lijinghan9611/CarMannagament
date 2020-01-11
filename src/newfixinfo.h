#ifndef NEWFIXINFO_H
#define NEWFIXINFO_H
/*
*添加车辆维修信息
*/
#include <QObject>
#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QDebug>
#include <QMainWindow>
#include <QComboBox>
#include <QLineEdit>
#include <QDateTime>
#include <QTextEdit>
#include <QDateTimeEdit>
#include <QCloseEvent>   //监听关闭事件
#include "connect.h"
class NewFixInfo : public QMainWindow
{
    Q_OBJECT
public:
    NewFixInfo(QWidget *parent = 0): QMainWindow(parent){}
    NewFixInfo(Connect *c, QWidget *parent = 0);

    bool Dialog_is_Open;

    ~NewFixInfo();
protected:
    void closeEvent(QCloseEvent *event);
private:
    QLabel *labCar; //显示“车牌”
    QComboBox *cbxAddSheng;  //省份选择
    QComboBox *cbxAddZimu;    //车辆省份字母
    QLineEdit *editAddCarNum;  //输入车牌信息
    QLabel *labItems;
    QLineEdit *editAddItems;  //维修项目
    QLabel *labtime;
    QDateTimeEdit *addDateEdit;  //时间
    QLabel *labFree;
    QLineEdit *addEditFree;  //费用
    QLabel *labRMB;
    QLabel *labRemark;
    QTextEdit *addTeRemark;   //备注
    QPushButton *btnOK;   //确定
    QPushButton *btnReturn; //关闭
    QPushButton *btnReset;  //重置

    Connect *conn;

private slots:
    void dialogClose();   //关闭
    void add();
    void Reset();
};

#endif // NEWFIXINFO_H
