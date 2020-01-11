#ifndef NEWINSURANCEORACCIDENT_H
#define NEWINSURANCEORACCIDENT_H

/*
*添加车险或者事故信息
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
class NewInsuranceOrAccident  : public QMainWindow
{
    Q_OBJECT
public:
    NewInsuranceOrAccident(QWidget *parent = 0);
    NewInsuranceOrAccident(Connect *c, QWidget *parent = 0);
    NewInsuranceOrAccident( int type,  Connect *c,QWidget *parent = 0);  //调用事故信息构造
    NewInsuranceOrAccident( QString type1,Connect *c, QWidget *parent = 0);

     ~NewInsuranceOrAccident();
    void initInsuranceDialog(QString carid,QString oldtime,QString oldFare,QString oldRemark);
    void initaddNewAccidentDialog(QString carid,QString oldtime);

    bool Insurance_is_Open;
    bool editDialog_is_Open;
    bool Accident_is_Open;
protected:
    void closeEvent(QCloseEvent *event);
private:
    QString insType;
    int type = 0;  //用于区别两个构造函数
    QLabel *labCar; //显示“车牌”
    QComboBox *cbxInsuranceSheng;  //省份选择
    QComboBox *cbxInsuranceZimu;    //车辆省份字母
    QLineEdit *editInsuranceCarNum;  //输入车牌信息
    QLabel *labInsurancetime;
    QDateTimeEdit *InsuranceTime;  //车险到期时间
    QLabel *labFree;
    QLineEdit *editInsuranceFree;  //车险金额
    QLabel *labInsuranceRemark;
    QTextEdit *TeInsuranceRemark;   //备注
    QPushButton *btnInsuranceOK;   //确定
    QPushButton *btnInsuranceReturn; //关闭
    QPushButton *btnInsuranceReset;  //重置

    QLabel *labCarid; //显示“车牌”
    QLabel *showCarid;
    QLabel *labacInsurancetime;
    QLabel *labShowInsurancetime;
    QComboBox *cbxAccidentSheng;  //省份选择
    QComboBox *cbxAccidentZimu;    //车辆省份字母
    QLineEdit *editAccidentCarNum;  //输入车牌信息
    QLabel *labaccidentplace;
    QTextEdit *editAccidentPlace;  //事故地点
    QLabel *labCompensateMoney;
    QLineEdit *editCompensateMoney;  //赔付金额
    QLabel *labAccidentACtime;
    QDateTimeEdit *AccidentACtime;  //车险到期时间
    QLabel *labAccidentRemark;
    QTextEdit *TeAccidentRemark;   //备注
    QPushButton *btnAccidentOK;   //确定
    QPushButton *btnAccidentReturn; //关闭
    QPushButton *btnAccidentReset;  //重置

    Connect *conn;   //数据库连接
private slots:
     void DialogClose();   //关闭
     void add();
     void Accidentadd();
     void editInsurance();
     void ResetNewInsurance();
     void ResetNewAccident();
     void ResetEditInsurance();

};

#endif // NEWINSURANCEORACCIDENT_H
