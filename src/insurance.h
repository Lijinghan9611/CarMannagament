#ifndef INSURANCE_H
#define INSURANCE_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QTableWidget>
#include <QComboBox>
#include <QLineEdit>
#include "connect.h"
class Insurance : public QWidget
{
    Q_OBJECT
public:
    explicit Insurance(QWidget *parent = 0):QWidget(parent){}
    explicit Insurance(Connect *c, QWidget *parent = 0);
private:
    QLabel *labInsurance;  //“车牌”
    QComboBox *cbxInsuranceSheng;  //省份选择
    QComboBox *cbxInsuranceZimu;    //车辆省份字母
    QLineEdit *editInsuranceCarNum;  //输入车牌信息
    QPushButton *btnInsuranceSearch;  //查询
    QPushButton *btnInsuranceSearchAll;  //查询所有
    QPushButton *btnInsuranceAdd;  //添加
    QPushButton *btnInsuranceEdit;  //修改
    QPushButton *btnInsuranceDelete;  //删除
    QPushButton *btnDeleteAccident;

    QLabel *labCarnum;
    QLabel *showCarnum;
    QLabel *labtime;
    QLabel *showTime;
    QLabel *labFare;
    QLabel *showFare;
    QLabel *labAccidentNum;
    QLabel *showAccidentNum;
    QLabel *labRemark;
    QLabel *showRemark;
    QPushButton *btnEditInsurance;
    QPushButton *addAccident;
    QTableWidget *InsuranceTableWidget;

    int rowCount;
    Connect *conn;   //数据库连接

signals:

public slots:
    void InsuranceAdd();
    void addNewAccident();
    void editInsurance();
    void Search();
    void SearchAll();
    void Edit(int,int);
    void EditAccident(int,int);
    void Delete();
    void DeleteAccident();
};

#endif // INSURANCE_H
