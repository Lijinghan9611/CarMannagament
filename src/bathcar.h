#ifndef BATHCAR_H
#define BATHCAR_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QTableWidget>
#include <QComboBox>
#include <QLineEdit>
#include "connect.h"
class bathcar : public QWidget
{
    Q_OBJECT
public:
    explicit bathcar(QWidget *parent = 0):QWidget(parent){}
    explicit bathcar(Connect *c, QWidget *parent = 0);

private:
    bool is_search;
    bool is_addRecord;
    QLabel *labBathCardNum;  //“车牌”
    QComboBox *cbxBathCardSheng;  //省份选择
    QComboBox *cbxBathCardZimu;    //车辆省份字母
    QLineEdit *editBathCardCarNum;  //输入车牌信息
    QPushButton *btnBathCardSearch;  //查询
    QPushButton *btnBathCardSearchAll;  //查询所有
    QPushButton *btnBathCardAdd;  //添加
    QPushButton *btnaddBathRecord;  //打卡
    QPushButton *btnBathCardDelete;  //删除
    QPushButton *btnBugCard;  //充卡
    QTableWidget *BathCarTableWidget;
    QPushButton *btnAddNewCar;  //绑定新的车牌


    QLabel *labCard;  //
    QLabel *CardNum;
    QLabel *labCarnums;
    QComboBox *cbxCarnums;

    QLabel *labType;
    QLabel *type;   //类型
    QLabel *labTimes;
    QLabel *Times;   //次数
    QLabel *labRemark;
    QLabel *Remark;    //备注
    int rowCount;
    Connect *conn;   //数据库连接
signals:

public slots:
    void slotItemChanged(int ,int);
    void addNewBathCard();
    void OpenAddCarid();
    void Search();
    void SearchAll();
    void addBathRecord();
    void addbathTimes();
    void deleteBathRecord();
};

#endif // BATHCAR_H
