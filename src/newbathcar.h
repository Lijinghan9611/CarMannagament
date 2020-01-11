#ifndef NEWBATHCAR_H
#define NEWBATHCAR_H

/**
* 添加洗车卡或洗车记录信息
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
class NewBathCar : public QMainWindow
{
    Q_OBJECT
public:
    NewBathCar(QWidget *parent = 0): QMainWindow(parent){}
    NewBathCar(Connect *c, QWidget *parent = 0);
    NewBathCar(Connect *c, int type1, QWidget *parent = 0);

    bool BathCard_is_Open;
    bool addCarid_is_Open;
    void setBathCardId(QString card);
    //bool addRecordDialog;
protected:
    void closeEvent(QCloseEvent *event);
private:
    QString bathcardid;
    int type;
    QLabel *labCar; //显示“车牌”
    QComboBox *cbxBathcardSheng;  //省份选择
    QComboBox *cbxBathcardZimu;    //车辆省份字母
    QLineEdit *editBathcardCarNum;  //输入车牌信息
    QLabel *labType;
    QComboBox *cbxBathcardType;  //洗车卡类型
    QLabel *labBathcardTimes;
    QLineEdit *BathcardTimes;  //洗车次数
    QLabel *labTimes;
    QLabel *labBathcardRemark;
    QTextEdit *TeBathcardRemark;   //备注
    QPushButton *btnBathcardOK;   //确定
    QPushButton *btnBathcardReturn; //关闭
    QPushButton *btnBathcardReset;  //重置

    Connect *conn;   //数据库连接

private slots:
    void DialogClose();   //关闭
    void Reset();
    void addNewBathCard();
    void addCarID();
};

#endif // NEWBATHCAR_H
