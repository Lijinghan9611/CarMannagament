#include "newbathcar.h"
#include <QGridLayout>
#include <QMessageBox>
#include <QListView>
#include <QSqlQuery>
/*添加洗车卡*/
NewBathCar::NewBathCar(Connect *c, QWidget *parent)
    : QMainWindow(parent)
{
    conn = c;

    setWindowTitle("添加洗车卡记录");
    this->resize(350, 200);
    BathCard_is_Open = false;

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
    QStringList Items2;
    Items2<<"蜡水"<<"泡沫";

    labCar = new QLabel("车牌："); //显示“车牌”
    cbxBathcardSheng = new QComboBox();  //省份选择
    cbxBathcardZimu = new QComboBox();;    //车辆省份字母
    editBathcardCarNum = new QLineEdit();  //输入车牌信息
    labType = new QLabel("洗车卡类型：");
    cbxBathcardType = new QComboBox();;  //洗车卡类型
    labBathcardTimes = new QLabel("洗车次数：");
    BathcardTimes = new QLineEdit("10");  //洗车次数
    labTimes = new QLabel("次");
    labBathcardRemark = new QLabel("备注：");
    TeBathcardRemark = new QTextEdit();   //备注
    btnBathcardOK = new QPushButton("确定");   //确定
    btnBathcardReturn = new QPushButton("关闭"); ; //关闭
    btnBathcardReset = new QPushButton("重置"); ;  //重置


    cbxBathcardSheng->addItems(Items);
    cbxBathcardType->addItems(Items2);
    cbxBathcardZimu->addItems(Items1);

    QRegExp rx1("[0-9A-Z]{5}");
    editBathcardCarNum->setValidator(new QRegExpValidator(rx1, editBathcardCarNum));

    cbxBathcardSheng->setStyleSheet("QComboBox { min-height: 15px; min-width: 25px;}"
                                    "QComboBox QAbstractItemView::item{height:20px;}");
    cbxBathcardSheng->setView(new QListView());
    cbxBathcardType->setStyleSheet("QComboBox { min-height: 15px; min-width: 25px;}"
                                   "QComboBox QAbstractItemView::item{height:20px;}");
    cbxBathcardType->setView(new QListView());
    cbxBathcardZimu->setStyleSheet("QComboBox { min-height: 15px; min-width: 25px;}"
                                   "QComboBox QAbstractItemView::item{height:20px;}");
    cbxBathcardZimu->setView(new QListView());

    //连接信号槽
    connect(btnBathcardReturn, SIGNAL(clicked()), this, SLOT(DialogClose()));
    connect(btnBathcardReset, SIGNAL(clicked()), this, SLOT(Reset()));
    connect(btnBathcardOK, SIGNAL(clicked()), this, SLOT(addNewBathCard()));

    QGridLayout *layout = new QGridLayout();
    layout->addWidget(labCar,0,0);
    layout->addWidget(cbxBathcardSheng,0,1);
    layout->addWidget(cbxBathcardZimu,0,2);
    layout->addWidget(editBathcardCarNum,0,3);
    layout->addWidget(labType,1,0);
    layout->addWidget(cbxBathcardType,1,1,1,2);
    layout->addWidget(labBathcardTimes,2,0);
    layout->addWidget(BathcardTimes,2,1);
    layout->addWidget(labTimes,2,2);
    layout->addWidget(labBathcardRemark,3,0);
    layout->addWidget(TeBathcardRemark,3,1,1,3);
    layout->addWidget(btnBathcardOK,4,0);
    layout->addWidget(btnBathcardReturn,4,1);
    layout->addWidget(btnBathcardReset,4,2);

    QWidget *widget1 = new QWidget();
    widget1->setLayout(layout);
    //添加到主布局
    this->setCentralWidget(widget1);
}

NewBathCar::NewBathCar(Connect *c, int type1, QWidget *parent)
    : QMainWindow(parent)
{
    conn = c;
    type = type1;

    setWindowTitle("添加车牌");
    this->resize(300, 40);
    addCarid_is_Open = false;

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
    QStringList Items2;
    Items2<<"蜡水"<<"泡沫";

    labCar = new QLabel("车牌："); //显示“车牌”
    cbxBathcardSheng = new QComboBox();  //省份选择
    cbxBathcardZimu = new QComboBox();;    //车辆省份字母
    editBathcardCarNum = new QLineEdit();  //输入车牌信息
    btnBathcardOK = new QPushButton("确定");   //确定
    btnBathcardReturn = new QPushButton("关闭"); ; //关闭
    btnBathcardReset = new QPushButton("重置"); ;  //重置

    labCar->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    cbxBathcardSheng->addItems(Items);
    cbxBathcardZimu->addItems(Items1);

    QRegExp rx1("[0-9A-Z]{5}");
    editBathcardCarNum->setValidator(new QRegExpValidator(rx1, editBathcardCarNum));

    cbxBathcardSheng->setStyleSheet("QComboBox { min-height: 15px; min-width: 25px;}"
                                    "QComboBox QAbstractItemView::item{height:20px;}");
    cbxBathcardSheng->setView(new QListView());
    cbxBathcardZimu->setStyleSheet("QComboBox { min-height: 15px; min-width: 25px;}"
                                   "QComboBox QAbstractItemView::item{height:20px;}");
    cbxBathcardZimu->setView(new QListView());

    //连接信号槽
    connect(btnBathcardReturn, SIGNAL(clicked()), this, SLOT(DialogClose()));
    connect(btnBathcardReset, SIGNAL(clicked()), this, SLOT(Reset()));
    connect(btnBathcardOK, SIGNAL(clicked()), this, SLOT(addCarID()));

    QGridLayout *layout = new QGridLayout();
    layout->addWidget(labCar,0,0);
    layout->addWidget(cbxBathcardSheng,0,1);
    layout->addWidget(cbxBathcardZimu,0,2);
    layout->addWidget(editBathcardCarNum,0,3);
    layout->addWidget(btnBathcardOK,1,1);
    layout->addWidget(btnBathcardReturn,1,2);
    layout->addWidget(btnBathcardReset,1,3);


    QWidget *widget1 = new QWidget();
    widget1->setLayout(layout);
    //添加到主布局
    this->setCentralWidget(widget1);
}

void NewBathCar::addCarID()
{
    if(editBathcardCarNum->text() == ""){
        QMessageBox::information(this, tr("提示"),tr("请输入车牌号码。"),QMessageBox::Ok, QMessageBox::Ok);
        return;
    }
    conn->getDB().open();
    QSqlQuery *exe = new QSqlQuery;

    QString carNumber = cbxBathcardSheng->currentText().trimmed() + cbxBathcardZimu->currentText().trimmed() + editBathcardCarNum->text();
    QString query = "insert into bathcard_carnum values('"+carNumber+"','"+bathcardid+"')";
    exe->prepare(query);
    if(exe->exec())
        QMessageBox::information(this, tr("提示"),tr("添加成功。"),QMessageBox::Ok, QMessageBox::Ok);
    else
        QMessageBox::information(this, tr("提示"),tr("添加失败。"),QMessageBox::Ok, QMessageBox::Ok);
    conn->getDB().close();
}

void NewBathCar::setBathCardId(QString card)
{
    bathcardid = card;
}

void NewBathCar::addNewBathCard()
{
    if(editBathcardCarNum->text() == ""){
        QMessageBox::information(this, tr("提示"),tr("请输入车牌号码。"),QMessageBox::Ok, QMessageBox::Ok);
        return;
    }
    if(TeBathcardRemark->toPlainText().length() > 50)
    {
        QMessageBox::information(this, tr("提示"),tr("备注过长。"),QMessageBox::Ok, QMessageBox::Ok);
        return;
    }

    //弹出警告提示框
    QMessageBox box(QMessageBox::Warning,"提示","确认添加？");
    box.setStandardButtons (QMessageBox::Ok|QMessageBox::Cancel);
    box.setButtonText (QMessageBox::Ok,QString("确定"));
    box.setButtonText (QMessageBox::Cancel,QString("取消"));
    switch(box.exec())
    {
    case QMessageBox::Ok:
        break;
    case QMessageBox::Cancel:
        return;
    default:
        return;
    }

    QString carNumber = cbxBathcardSheng->currentText().trimmed() + cbxBathcardZimu->currentText().trimmed() + editBathcardCarNum->text();
    QString Remark = TeBathcardRemark->toPlainText();
    QString type = cbxBathcardType->currentText().trimmed();
    QString times = BathcardTimes->text();

    conn->getDB().open();
    QSqlQuery *query = new QSqlQuery;

    /* 判断是否存在该客户*/
    QString query0("select * from client where carid = '" + carNumber + "';");
    query->prepare(query0);
    if(query->exec()){
        if(!query->next()){
            QString query01("insert into client(carid) values('" + carNumber + "');");
            query->prepare(query01);
            query->exec();
        }
    }

    QString queryFind = "select id, carid from client where carid = '"+carNumber+"'";
    query->prepare(queryFind);
    QString carid;
    QString userId;
    if(query->exec()){
        if(query->next())
        {
            userId = query->value(0).toString();
            carid = query->value(1).toString();

        }
    }

    QString newCarid = carid.mid(2,carid.length());
    QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
    QString str = time.toString("yyyyMMddhhmmss") + newCarid; //新ID
    QString query1("insert into bathcard(id, userid,bathclass,bathnum,remark) values('" + str + "','" + userId + "','" + type + "','" + times + "','" + Remark + "');");
   // qDebug() <<query1;
    query->prepare(query1);
    query->exec();
    query1 = "insert into bathcard_carnum values('"+carid+"','"+str+"');";
   // qDebug() <<query1;
    query->prepare(query1);
    if(query->exec()){
        QMessageBox::information(this, tr("提示"),tr("添加成功！"),QMessageBox::Ok, QMessageBox::Ok);
    }
    else{
        QMessageBox::information(this, tr("提示"),tr("添加失败！"),QMessageBox::Ok, QMessageBox::Ok);
    }
    conn->getDB().close();

}


void NewBathCar::Reset()
{
    cbxBathcardSheng->setCurrentIndex(0);
    cbxBathcardZimu->setCurrentIndex(0);
    editBathcardCarNum->setText("");
    if(type != 1)
    {
        cbxBathcardType->setCurrentIndex(0);
        BathcardTimes->setText("10");
        TeBathcardRemark->setText("");
    }
}

void NewBathCar::DialogClose()
{
    if(type == 1)
        addCarid_is_Open = false;
    else
        BathCard_is_Open = false;
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

void NewBathCar::closeEvent(QCloseEvent *event)
{
    //TODO: 在退出窗口之前，实现希望做的操作
    DialogClose();
}

