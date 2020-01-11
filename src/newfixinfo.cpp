#include "newfixinfo.h"
#include <QGridLayout>
#include <QGroupBox>
#include <QMessageBox>
#include <QSqlDatabase>
#include <qsqlquery.h>
#include <qtextedit.h>
#include <QSqlError>
//#include <connect.h>
//Connect *c11;
NewFixInfo::NewFixInfo(Connect *c, QWidget *parent)
    : QMainWindow(parent)
{
    conn = c;
    //c11 = new Connect();
    setWindowTitle("添加新的维修记录");
    //setWindowIcon(QIcon(":/images/cat.ico"));

    this->resize(350, 200);
    Dialog_is_Open = false;

    QStringList Items;
    Items<<"粤    "<<"琼"<<"湘"<<"桂"<<"渝"<<"冀"
        <<"云"<<"辽"<<"黑"<<"皖"<<"鲁"<<"津"
       <<"新"<<"苏"<<"浙"<<"鄂"<<"甘"<<"沪"
      <<"晋"<<"蒙"<<"陕"<<"吉"<<"贵"<<"京"
     <<"青"<<"藏"<<"川"<<"宁"<<"豫";
    QStringList Items1;
    Items1<<"A    "<<"B"<<"C"<<"D"<<"E"<<"F"
         <<"G"<<"H"<<"I"<<"J"<<"K"<<"L"
        <<"M"<<"N"<<"O"<<"P"<<"Q"<<"R"
       <<"S"<<"T"<<"U"<<"V"<<"W"<<"X"
      <<"Y"<<"Z";

    labCar = new QLabel("车牌："); //显示“车牌”
    cbxAddSheng = new QComboBox();  //省份选择
    cbxAddZimu = new QComboBox();    //车辆省份字母
    cbxAddSheng->addItems(Items);
    cbxAddZimu->addItems(Items1);
    editAddCarNum = new QLineEdit();  //输入车牌信息
    labItems = new QLabel("维修项目：");
    editAddItems = new QLineEdit();  //维修项目
    labtime = new QLabel("维修时间：");
    addDateEdit = new QDateTimeEdit(QDateTime::currentDateTime());  //时间
    labFree = new QLabel("维修费用：");
    addEditFree = new QLineEdit();  //费用
    labRMB = new QLabel("元");
    labRemark = new QLabel("备注：");
    addTeRemark = new QTextEdit();   //备注
    btnOK = new QPushButton("确定");   //确定
    btnReturn = new QPushButton("关闭"); //关闭
    btnReset = new QPushButton("重置");  //重置

    //连接信号槽
    connect(btnReturn, SIGNAL(clicked()), this, SLOT(dialogClose()));
    connect(btnOK, SIGNAL(clicked()), this, SLOT(add()));

    QRegExp rx1("[0-9A-Z]{5}");
    editAddCarNum->setValidator(new QRegExpValidator(rx1, editAddCarNum));
    QRegExp rx2("[0-9]{6}");
    addEditFree->setValidator(new QRegExpValidator(rx2, addEditFree));

    QGridLayout *layout = new QGridLayout();

    layout->addWidget(labCar,0,0);
    layout->addWidget(cbxAddSheng,0,1);
    layout->addWidget(cbxAddZimu,0,2);
    layout->addWidget(editAddCarNum,0,3);
    layout->addWidget(labItems,1,0);
    layout->addWidget(editAddItems,1,1,1,2);
    layout->addWidget(labtime,2,0);
    layout->addWidget(addDateEdit,2,1,1,2);
    layout->addWidget(labFree,3,0);
    layout->addWidget(addEditFree,3,1);
    layout->addWidget(labRMB,3,2);
    layout->addWidget(labRemark,4,0);
    layout->addWidget(addTeRemark,4,1,1,3);
    layout->addWidget(btnOK,5,0);
    layout->addWidget(btnReturn,5,1);
    layout->addWidget(btnReset,5,2);

    QGroupBox *Group = new QGroupBox();
    Group->setLayout(layout);
    //添加到主布局
    this->setCentralWidget(Group);
}

void NewFixInfo::dialogClose()
{
    //弹出警告提示框
    QMessageBox box(QMessageBox::Warning,"确认关闭？","请注意保存数据。");
    box.setStandardButtons (QMessageBox::Ok|QMessageBox::Cancel);
    box.setButtonText (QMessageBox::Ok,QString("确定关闭"));
    box.setButtonText (QMessageBox::Cancel,QString("取消"));
    switch(box.exec()){
    case QMessageBox::Ok:
        Dialog_is_Open = false;
        this->hide();
        break;
    case QMessageBox::Cancel:
        return;
    default:
        return;
    }
}

void NewFixInfo::add()
{

    QString carNumber,carItems,carDate,carFee,carRemark;
    if(editAddCarNum->text() != "")
    {
        carNumber = cbxAddSheng->currentText().trimmed() + cbxAddZimu->currentText().trimmed() + editAddCarNum->text();
        qDebug() <<carNumber;
    }
    else
    {
        //弹出提示框
        QMessageBox::information(this, tr("提示"),tr("请输入车牌号码"),QMessageBox::Ok, QMessageBox::Ok);
        return;
    }
    if(editAddItems->text() != "")
    {
        carItems = editAddItems->text();
        qDebug() <<carItems;
    }
    else
    {
        //弹出提示框
        QMessageBox::information(this, tr("提示"),tr("请输入维护项目"),QMessageBox::Ok, QMessageBox::Ok);
        return;
    }
    if(addDateEdit->text() != "")
    {
        carDate = addDateEdit->text();
        qDebug() <<carDate;
    }
    else
    {
        //弹出提示框
        QMessageBox::information(this, tr("提示"),tr("请输入维护时间"),QMessageBox::Ok, QMessageBox::Ok);
        return;
    }
    if(addEditFree->text() != "")
    {
        carFee = addEditFree->text();
        qDebug() <<carFee;
    }
    else
    {
        //弹出提示框
        QMessageBox::information(this, tr("提示"),tr("请输入维护费用"),QMessageBox::Ok, QMessageBox::Ok);
        return;
    }

    carRemark = addTeRemark->toPlainText();
    qDebug() <<carRemark;

    conn->getDB().open();

    QSqlQuery *query = new QSqlQuery;
    QString query1("select * from client where carid = '" + carNumber + "';");
    query->prepare(query1);
    if(query->exec()){
        if(!query->next()){
            QString query11("insert into client(carid) values('" + carNumber + "');");
            query->prepare(query11);
            query->exec();
        }
    }
    QString query2("insert into maintenance(carid,items,firsttime,fee,remark) values('" + carNumber + "','" + carItems + "','" + carDate + "','" + carFee + "','" + carRemark + "');");
    query->prepare(query2);
    if(query->exec()){
        QMessageBox::information(this, tr("提示"),tr("添加成功！"),QMessageBox::Ok, QMessageBox::Ok);
    }
    else{
        QMessageBox::information(this, tr("提示"),tr("添加失败！"),QMessageBox::Ok, QMessageBox::Ok);
    }
    conn->getDB().close();
}

void NewFixInfo::Reset()
{
    cbxAddSheng->setCurrentIndex(0);
    cbxAddZimu->setCurrentIndex(0);
    editAddCarNum->setText("");
        editAddItems->setText("");
        addEditFree->setText("");
        addTeRemark->setText("");
}


void NewFixInfo::closeEvent(QCloseEvent *event)
{
    //TODO: 在退出窗口之前，实现希望做的操作

    dialogClose();
}

NewFixInfo::~NewFixInfo(){}

