#ifndef NEWCLIENT_H
#define NEWCLIENT_H

/*
*添加新的顾客信息
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
class NewClient : public QMainWindow
{
    Q_OBJECT
public:
    explicit NewClient(QWidget *parent = 0): QMainWindow(parent){}

    explicit NewClient(Connect *c, QWidget *parent = 0);

    explicit NewClient(Connect *c, int type1,  QWidget *parent = 0);
    bool Dialog_is_Open;
    bool editClient_is_open;

    void initEditClientDialog(QString oldCarNum, QString oldName,
                              QString oldPhone, QString oldaddr, QString oldRemark);
protected:
    void closeEvent(QCloseEvent *event);
private:
    QString oldCarNumber;
    int type;
    QLabel *labCar; //显示“车牌”
    QComboBox *cbxBathcardSheng;  //省份选择
    QComboBox *cbxBathcardZimu;    //车辆省份字母
    QLineEdit *editBathcardCarNum;  //输入车牌信息
    QLabel *labName;
    QLineEdit *editName;  //姓名
    QLabel *labPhone;
    QLineEdit *editPhone;  //电话
    QLabel *labAddress;
    QTextEdit *teAddress;  //地址
    QLabel *labRemark;
    QTextEdit *TeRemark;   //备注
    QPushButton *btnOK;   //确定
    QPushButton *btnReturn; //关闭
    QPushButton *btnReset;  //重置

    Connect *conn;   //数据库连接

private slots:
    void addClient();
    void DialogClose();   //关闭
    void Reset();
    void editClient();
signals:
};

#endif // NEWCLIENT_H
