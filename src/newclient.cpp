#include "newclient.h"
#include <QGridLayout>
#include <QMessageBox>
#include <QListView>
#include <QSqlQuery>
NewClient::NewClient(Connect *c, QWidget *parent) : QMainWindow(parent)
{

    conn = c;

    setWindowTitle("添加顾客记录");
    this->resize(350, 200);
    Dialog_is_Open = false;

    QStringList Items;
    Items<<"粤"<<"琼"<<"湘"<<"桂"<<"渝"<<"冀"
        <<"云"<<"辽"<<"黑"<<"皖"<<"鲁"<<"津"
       <<"新"<<"苏"<<"浙"<<"鄂"<<"甘"<<"沪"
      <<"晋"<<"蒙"<<"陕"<<"吉"<<"贵"<<"京"
     <<"青"<<"藏"<<"川"<<"宁"<<"豫";
    QStringList Items1;
    Items1<<"A"<<"B"<<"C"<<"D"<<"E"<<"F"
         <<"G"<<"H"<<"I"<<"J"<<"K"<<"L"
        <<"M"<<"N"<<"O"<<"P"<<"Q"<<"R"
       <<"S"<<"T"<<"U"<<"V"<<"W"<<"X"
      <<"Y"<<"Z";

    labCar = new QLabel("车牌："); //显示“车牌”
    cbxBathcardSheng = new QComboBox() ; //省份选择
    cbxBathcardZimu= new QComboBox();    //车辆省份字母
    editBathcardCarNum = new QLineEdit;  //输入车牌信息
    labName= new QLabel("姓名");
    editName = new QLineEdit();  //姓名
    labPhone= new QLabel("电话");
    editPhone = new QLineEdit();  //电话
    labAddress= new QLabel("地址");
    teAddress = new QTextEdit;  //地址
    labRemark= new QLabel("备注");
    TeRemark = new QTextEdit;   //备注
    btnOK = new QPushButton("确定");   //确定
    btnReturn= new QPushButton("关闭");  //关闭
    btnReset= new QPushButton("重置");  //重置

    cbxBathcardSheng->addItems(Items);
    cbxBathcardZimu->addItems(Items1);

    cbxBathcardSheng->setStyleSheet("QComboBox { min-height: 15px; min-width: 25px;}"
                                    "QComboBox QAbstractItemView::item{height:20px;}");
    cbxBathcardSheng->setView(new QListView());
    cbxBathcardZimu->setStyleSheet("QComboBox { min-height: 15px; min-width: 25px;}"
                                   "QComboBox QAbstractItemView::item{height:20px;}");
    cbxBathcardZimu->setView(new QListView());

    QRegExp rx1("[0-9A-Z]{5}");
    QRegExp rx2("[0-9]{15}");
    editBathcardCarNum->setValidator(new QRegExpValidator(rx1, editBathcardCarNum));
    editPhone->setValidator(new QRegExpValidator(rx2, editPhone));
    //连接信号槽
    connect(btnReturn, SIGNAL(clicked()), this, SLOT(DialogClose()));
    connect(btnOK, SIGNAL(clicked()), this, SLOT(addClient()));
    connect(btnReset, SIGNAL(clicked()), this, SLOT(Reset()));


    QGridLayout *layout = new QGridLayout();
    layout->addWidget(labCar,0,0);
    layout->addWidget(cbxBathcardSheng,0,1);
    layout->addWidget(cbxBathcardZimu,0,2);
    layout->addWidget(editBathcardCarNum,0,3);
    layout->addWidget(labName,1,0);
    layout->addWidget(editName,1,1);
    layout->addWidget(labPhone,2,0);
    layout->addWidget(editPhone,2,1,1,2);
    layout->addWidget(labAddress,3,0);
    layout->addWidget(teAddress,3,1,1,3);
    layout->addWidget(labRemark,4,0);
    layout->addWidget(TeRemark,4,1,1,3);
    layout->addWidget(btnOK,5,0);
    layout->addWidget(btnReturn,5,1);
    layout->addWidget(btnReset,5,2);


    QWidget *widget1 = new QWidget();
    widget1->setLayout(layout);
    //添加到主布局
    this->setCentralWidget(widget1);
}


/*修改顾客信息*/
NewClient::NewClient(Connect *c, int type1,  QWidget *parent): QMainWindow(parent)
{
    conn = c;
    type = type1;
    editClient_is_open = false;

    setWindowTitle("修改顾客信息");
    this->resize(350, 200);

    QStringList Items;
    Items<<"粤"<<"琼"<<"湘"<<"桂"<<"渝"<<"冀"
        <<"云"<<"辽"<<"黑"<<"皖"<<"鲁"<<"津"
       <<"新"<<"苏"<<"浙"<<"鄂"<<"甘"<<"沪"
      <<"晋"<<"蒙"<<"陕"<<"吉"<<"贵"<<"京"
     <<"青"<<"藏"<<"川"<<"宁"<<"豫";
    QStringList Items1;
    Items1<<"A"<<"B"<<"C"<<"D"<<"E"<<"F"
         <<"G"<<"H"<<"I"<<"J"<<"K"<<"L"
        <<"M"<<"N"<<"O"<<"P"<<"Q"<<"R"
       <<"S"<<"T"<<"U"<<"V"<<"W"<<"X"
      <<"Y"<<"Z";

    labCar = new QLabel("车牌："); //显示“车牌”
    cbxBathcardSheng = new QComboBox() ; //省份选择
    cbxBathcardZimu= new QComboBox();    //车辆省份字母
    editBathcardCarNum = new QLineEdit;  //输入车牌信息
    labName= new QLabel("姓名");
    editName = new QLineEdit();  //姓名
    labPhone= new QLabel("电话");
    editPhone = new QLineEdit();  //电话
    labAddress= new QLabel("地址");
    teAddress = new QTextEdit;  //地址
    labRemark= new QLabel("备注");
    TeRemark = new QTextEdit;   //备注
    btnOK = new QPushButton("确定");   //确定
    btnReturn= new QPushButton("关闭");  //关闭
    btnReset= new QPushButton("重置");  //重置

    cbxBathcardSheng->addItems(Items);
    cbxBathcardZimu->addItems(Items1);

    QRegExp rx1("[0-9A-Z]{5}");
    QRegExp rx2("[0-9]{15}");
    editBathcardCarNum->setValidator(new QRegExpValidator(rx1, editBathcardCarNum));
    editPhone->setValidator(new QRegExpValidator(rx2, editPhone));

    cbxBathcardSheng->setStyleSheet("QComboBox { min-height: 15px; min-width: 25px;}"
                                    "QComboBox QAbstractItemView::item{height:20px;}");
    cbxBathcardSheng->setView(new QListView());
    cbxBathcardZimu->setStyleSheet("QComboBox { min-height: 15px; min-width: 25px;}"
                                   "QComboBox QAbstractItemView::item{height:20px;}");
    cbxBathcardZimu->setView(new QListView());


    //连接信号槽
    connect(btnReturn, SIGNAL(clicked()), this, SLOT(DialogClose()));
    connect(btnOK, SIGNAL(clicked()), this, SLOT(editClient()));
    connect(btnReset, SIGNAL(clicked()), this, SLOT(Reset()));


    QGridLayout *layout = new QGridLayout();
    layout->addWidget(labCar,0,0);
    layout->addWidget(cbxBathcardSheng,0,1);
    layout->addWidget(cbxBathcardZimu,0,2);
    layout->addWidget(editBathcardCarNum,0,3);
    layout->addWidget(labName,1,0);
    layout->addWidget(editName,1,1);
    layout->addWidget(labPhone,2,0);
    layout->addWidget(editPhone,2,1,1,2);
    layout->addWidget(labAddress,3,0);
    layout->addWidget(teAddress,3,1,1,3);
    layout->addWidget(labRemark,4,0);
    layout->addWidget(TeRemark,4,1,1,3);
    layout->addWidget(btnOK,5,0);
    layout->addWidget(btnReturn,5,1);
    layout->addWidget(btnReset,5,2);


    QWidget *widget1 = new QWidget();
    widget1->setLayout(layout);
    //添加到主布局
    this->setCentralWidget(widget1);
}

void NewClient::editClient()
{
    QString carNumber,name, Phone,address,Remark;
    if(editBathcardCarNum->text() != "")
    {
        carNumber = cbxBathcardSheng->currentText().trimmed() + cbxBathcardZimu->currentText().trimmed() + editBathcardCarNum->text();
        //qDebug() <<carNumber;
    }
    else
    {
        //弹出提示框
        QMessageBox::information(this, tr("提示"),tr("请输入车牌号码。"),QMessageBox::Ok, QMessageBox::Ok);
        return;
    }

    if(editName->text() != "")
    {
        name = editName->text();
    }
    else
    {
        //弹出提示框
        QMessageBox::information(this, tr("提示"),tr("请输入姓名。"),QMessageBox::Ok, QMessageBox::Ok);
        return;
    }

    if(editName->text().length() > 20)
    {
        //弹出提示框
        QMessageBox::information(this, tr("提示"),tr("姓名字数超长"),QMessageBox::Ok, QMessageBox::Ok);
        return;
    }
    if(teAddress->toPlainText().length() > 50)
    {
        //弹出提示框
        QMessageBox::information(this, tr("提示"),tr("地址字数超长"),QMessageBox::Ok, QMessageBox::Ok);
        return;
    }
    if(TeRemark->toPlainText().length() > 50)
    {
        //弹出提示框
        QMessageBox::information(this, tr("提示"),tr("备注字数超长"),QMessageBox::Ok, QMessageBox::Ok);
        return;
    }

    Phone = editPhone->text();
    address = teAddress->toPlainText();
    Remark = TeRemark->toPlainText();
    conn->getDB().open();
    QSqlQuery *query = new QSqlQuery;

    if (oldCarNumber != carNumber){//车牌号码更改时判断一下是否存在该更改后的号码
        /* 判断是否存在该客户*/
        QString queryFind = "select * from client where carid = '"+carNumber+"'";
        query->prepare(queryFind);
        if(query->exec()){
            while(query->next()){
                QMessageBox::information(this, tr("提示"),tr("已存在该客户。"),QMessageBox::Ok, QMessageBox::Ok);
                return;
            }
        }
    }

    QString query1("update client set carid = '" + carNumber + "',name = '" + name + "',phonenumber = '"
                   +Phone + "',address = '" + address + "',remark = '" + Remark + "' "
                   +"where carid = '"+oldCarNumber+"';");
    query->prepare(query1);
    if(query->exec()){
        QMessageBox::information(this, tr("提示"),tr("修改成功！"),QMessageBox::Ok, QMessageBox::Ok);
    }
    else{
        QMessageBox::information(this, tr("提示"),tr("修改失败！"),QMessageBox::Ok, QMessageBox::Ok);
    }
    conn->getDB().close();
}

void NewClient::Reset()
{
    cbxBathcardSheng->setCurrentIndex(0);
    cbxBathcardZimu->setCurrentIndex(0);
    editBathcardCarNum->setText("");
    editName->setText("");
    editPhone->setText("");
    teAddress->setText("");
    TeRemark->setText("");
}

void NewClient::addClient()
{
    QString carNumber,name, Phone,address,Remark;
    if(editBathcardCarNum->text() != "")
    {
        carNumber = cbxBathcardSheng->currentText().trimmed() + cbxBathcardZimu->currentText().trimmed() + editBathcardCarNum->text();
        //qDebug() <<carNumber;
    }
    else
    {
        //弹出提示框
        QMessageBox::information(this, tr("提示"),tr("请输入车牌号码。"),QMessageBox::Ok, QMessageBox::Ok);
        return;
    }

    if(editName->text() != "")
    {
        name = editName->text();
    }
    else
    {
        //弹出提示框
        QMessageBox::information(this, tr("提示"),tr("请输入姓名。"),QMessageBox::Ok, QMessageBox::Ok);
        return;
    }

    if(editName->text().length() > 20)
    {
        //弹出提示框
        QMessageBox::information(this, tr("提示"),tr("姓名字数超长"),QMessageBox::Ok, QMessageBox::Ok);
        return;
    }
    if(teAddress->toPlainText().length() > 50)
    {
        //弹出提示框
        QMessageBox::information(this, tr("提示"),tr("地址字数超长"),QMessageBox::Ok, QMessageBox::Ok);
        return;
    }
    if(TeRemark->toPlainText().length() > 50)
    {
        //弹出提示框
        QMessageBox::information(this, tr("提示"),tr("备注字数超长"),QMessageBox::Ok, QMessageBox::Ok);
        return;
    }


    Phone = editPhone->text();
    address = teAddress->toPlainText();
    Remark = TeRemark->toPlainText();
    conn->getDB().open();
    QSqlQuery *query = new QSqlQuery;

    /* 判断是否存在该客户*/
    QString queryFind = "select * from client where carid = '"+carNumber+"'";
    query->prepare(queryFind);
    if(query->exec()){
        while(query->next()){
            QMessageBox::information(this, tr("提示"),tr("已存在该客户。"),QMessageBox::Ok, QMessageBox::Ok);
            return;
        }
    }

    QString query1("insert into client(carid,name,phonenumber,address,remark) values('" + carNumber + "','" + name + "','" + Phone + "','" + address + "','" + Remark + "');");
    //qDebug() <<query1;
    query->prepare(query1);
    if(query->exec()){
        QMessageBox::information(this, tr("提示"),tr("添加成功！"),QMessageBox::Ok, QMessageBox::Ok);
    }
    else{
        QMessageBox::information(this, tr("提示"),tr("添加失败！"),QMessageBox::Ok, QMessageBox::Ok);
    }
    conn->getDB().close();
}

/*初始化修改界面*/
void NewClient::initEditClientDialog(QString oldCarNum, QString oldName, QString oldPhone, QString oldaddr, QString oldRemark)
{
    int CarSheng = cbxBathcardSheng->findText(oldCarNum.mid(0,1));
    int CarZimu = cbxBathcardZimu->findText(oldCarNum.mid(1,1));
    int length = oldCarNum.length();
    QString oldNum = oldCarNum.mid(2,length);
    cbxBathcardSheng->setCurrentIndex(CarSheng);
    cbxBathcardZimu->setCurrentIndex(CarZimu);
    editBathcardCarNum->setText(oldNum);
    editName->setText(oldName);
    editPhone->setText(oldPhone);
    teAddress->setText(oldaddr);
    TeRemark->setText(oldRemark);
    oldCarNumber = cbxBathcardSheng->currentText() +cbxBathcardZimu->currentText() + oldNum;

}


void NewClient::DialogClose()
{
    if(type == 1)
        editClient_is_open = false;
    else
        Dialog_is_Open = false;

    //弹出警告提示框
    QMessageBox box(QMessageBox::Warning,"确认关闭？","请注意保存数据。");
    box.setStandardButtons (QMessageBox::Ok|QMessageBox::Cancel);
    box.setButtonText (QMessageBox::Ok,QString("确定关闭"));
    box.setButtonText (QMessageBox::Cancel,QString("取消"));
    switch(box.exec()){
    case QMessageBox::Ok:
        this->hide();
        break;
    case QMessageBox::Cancel:
        return;
    default:
        return;
    }

}

void NewClient::closeEvent(QCloseEvent *event)
{
    //TODO: 在退出窗口之前，实现希望做的操作

    DialogClose();
}


