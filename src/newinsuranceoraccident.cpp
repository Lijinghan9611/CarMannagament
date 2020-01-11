#include "newinsuranceoraccident.h"
#include <QGridLayout>
#include <QMessageBox>
#include <QSqlQuery>
#include <QListView>
NewInsuranceOrAccident::NewInsuranceOrAccident(Connect *c, QWidget *parent)
    : QMainWindow(parent)
{
    conn = c;

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
    Insurance_is_Open = false; //默认关闭

    setWindowTitle("添加新的车险记录");
    this->resize(350, 200);
    labCar = new QLabel("车牌"); //显示“车牌”
    cbxInsuranceSheng = new QComboBox();  //省份选择
    cbxInsuranceZimu = new QComboBox();    //车辆省份字母
    editInsuranceCarNum = new QLineEdit();  //输入车牌信息
    labInsurancetime= new QLabel("车险到期时间:");
    InsuranceTime = new QDateTimeEdit(QDateTime::currentDateTime());  //车险到期时间
    labFree= new QLabel("车险金额:");
    editInsuranceFree = new QLineEdit();  //车险金额
    QLabel *labMoney = new QLabel("元");
    labInsuranceRemark= new QLabel("备注:");
    TeInsuranceRemark = new QTextEdit();   //备注
    btnInsuranceOK = new QPushButton("确定");   //确定
    btnInsuranceReturn = new QPushButton("关闭"); //关闭
    btnInsuranceReset = new QPushButton("重置");  //重置

    cbxInsuranceSheng->addItems(Items);
    cbxInsuranceZimu->addItems(Items1);
    QRegExp rx1("[0-9A-Z]{5}");
    editInsuranceCarNum->setValidator(new QRegExpValidator(rx1, editInsuranceCarNum));
    QRegExp rx2("[0-9]{6}");
    editInsuranceFree->setValidator(new QRegExpValidator(rx2, editInsuranceFree));

    cbxInsuranceSheng->setStyleSheet("QComboBox { min-height: 15px; min-width: 25px;}"
                                     "QComboBox QAbstractItemView::item{height:20px;}");
    cbxInsuranceSheng->setView(new QListView());
    cbxInsuranceZimu->setStyleSheet("QComboBox { min-height: 15px; min-width: 25px;}"
                                    "QComboBox QAbstractItemView::item{height:20px;}");
    cbxInsuranceZimu->setView(new QListView());
    //连接信号槽
    connect(btnInsuranceReturn, SIGNAL(clicked()), this, SLOT(DialogClose()));
    connect(btnInsuranceOK, SIGNAL(clicked()), this, SLOT(add()));
    connect(btnInsuranceReset, SIGNAL(clicked()), this, SLOT(ResetNewInsurance()));

    QGridLayout *layout = new QGridLayout();
    layout->addWidget(labCar,0,0);
    layout->addWidget(cbxInsuranceSheng,0,1);
    layout->addWidget(cbxInsuranceZimu,0,2);
    layout->addWidget(editInsuranceCarNum,0,3);
    layout->addWidget(labInsurancetime,1,0);
    layout->addWidget(InsuranceTime,1,1,1,2);
    layout->addWidget(labFree,2,0);
    layout->addWidget(editInsuranceFree,2,1);
    layout->addWidget(labMoney,2,2);
    layout->addWidget(labInsuranceRemark,3,0);
    layout->addWidget(TeInsuranceRemark,3,1,1,3);
    layout->addWidget(btnInsuranceOK,4,0);
    layout->addWidget(btnInsuranceReturn,4,1);
    layout->addWidget(btnInsuranceReset,4,2);


    QWidget *widget1 = new QWidget();
    widget1->setLayout(layout);
    //添加到主布局
    this->setCentralWidget(widget1);
}

/*添加新的事故信息*/
NewInsuranceOrAccident::NewInsuranceOrAccident(QString type1, Connect *c,  QWidget *parent)
    : QMainWindow(parent)
{
    conn = c;
    setWindowTitle("添加新的事故出险记录");
    this->resize(350, 250);
    Accident_is_Open = false;  //默认关闭
    insType = type1;

    labCarid= new QLabel("车牌:"); //显示“车牌”
    showCarid= new QLabel("");
    labacInsurancetime = new QLabel("车险到期时间:");
    labShowInsurancetime = new QLabel("");
    labaccidentplace= new QLabel("事故地点:");
    editAccidentPlace= new QTextEdit();  //事故地点
    labCompensateMoney= new QLabel("赔付金额:");
    editCompensateMoney= new QLineEdit();  //赔付金额
    QLabel *labMoney = new QLabel("元");
    labAccidentACtime= new QLabel("事故时间:");
    AccidentACtime= new QDateTimeEdit(QDateTime::currentDateTime());  //事故时间
    labAccidentRemark= new QLabel("备注:");
    TeAccidentRemark = new QTextEdit();   //备注
    btnAccidentOK= new QPushButton("确定");;   //确定
    btnAccidentReturn= new QPushButton("关闭");; //关闭
    btnAccidentReset= new QPushButton("重置");;  //重置

    //连接信号槽
    connect(btnAccidentReturn, SIGNAL(clicked()), this, SLOT(DialogClose()));
    connect(btnAccidentOK, SIGNAL(clicked()), this, SLOT(Accidentadd()));
    connect(btnAccidentReset, SIGNAL(clicked()), this, SLOT(ResetNewAccident()));

    QRegExp rx3("[0-9]{6}");
    editCompensateMoney->setValidator(new QRegExpValidator(rx3, editCompensateMoney));

    QGridLayout *layout = new QGridLayout();
    layout->addWidget(labCarid,0,0);
    layout->addWidget(showCarid,0,1);
    layout->addWidget(labacInsurancetime,1,0);
    layout->addWidget(labShowInsurancetime,1,1);
    layout->addWidget(labaccidentplace,2,0);
    layout->addWidget(editAccidentPlace,2,1,1,3);
    layout->addWidget(labCompensateMoney,3,0);
    layout->addWidget(editCompensateMoney,3,1);
    layout->addWidget(labMoney,3,2);
    layout->addWidget(labAccidentACtime,4,0);
    layout->addWidget(AccidentACtime,4,1,1,2);
    layout->addWidget(labAccidentRemark,5,0);
    layout->addWidget(TeAccidentRemark,5,1,1,3);
    layout->addWidget(btnAccidentOK,6,0);
    layout->addWidget(btnAccidentReturn,6,1);
    layout->addWidget(btnAccidentReset,6,2);

    QWidget *widget = new QWidget();
    widget->setLayout(layout);
    //添加到主布局
    this->setCentralWidget(widget);
}


/*修改车险信息*/
NewInsuranceOrAccident::NewInsuranceOrAccident( int type1, Connect *c, QWidget *parent)
    : QMainWindow(parent)
{
    conn = c;
    setWindowTitle("修改车险信息");
    this->resize(350, 200);
    editDialog_is_Open = false;  //默认关闭
    type = type1;


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

    labCar = new QLabel("车牌"); //显示“车牌”
    cbxInsuranceSheng = new QComboBox();  //省份选择
    cbxInsuranceZimu = new QComboBox();    //车辆省份字母
    editInsuranceCarNum = new QLineEdit();  //输入车牌信息
    labInsurancetime= new QLabel("车险到期时间:");
    InsuranceTime = new QDateTimeEdit(QDateTime::currentDateTime());  //车险到期时间
    labFree= new QLabel("车险金额:");
    editInsuranceFree = new QLineEdit();  //车险金额
    QLabel *labMoney = new QLabel("元");
    labInsuranceRemark= new QLabel("备注:");
    TeInsuranceRemark = new QTextEdit();   //备注
    btnInsuranceOK = new QPushButton("确定");   //确定
    btnInsuranceReturn = new QPushButton("关闭"); //关闭
    btnInsuranceReset = new QPushButton("重置");  //重置

    cbxInsuranceSheng->addItems(Items);
    cbxInsuranceZimu->addItems(Items1);

    cbxInsuranceSheng->setStyleSheet("QComboBox { min-height: 15px; min-width: 25px;}"
                                     "QComboBox QAbstractItemView::item{height:20px;}");
    cbxInsuranceSheng->setView(new QListView());
    cbxInsuranceZimu->setStyleSheet("QComboBox { min-height: 15px; min-width: 25px;}"
                                    "QComboBox QAbstractItemView::item{height:20px;}");
    cbxInsuranceZimu->setView(new QListView());

    QRegExp rx4("[0-9]{6}");
    editInsuranceFree->setValidator(new QRegExpValidator(rx4, editInsuranceFree));
    //连接信号槽
    connect(btnInsuranceReturn, SIGNAL(clicked()), this, SLOT(DialogClose()));
    connect(btnInsuranceOK, SIGNAL(clicked()), this, SLOT(editInsurance()));
    connect(btnInsuranceReset, SIGNAL(clicked()), this, SLOT(ResetEditInsurance()));


    QGridLayout *layout = new QGridLayout();
    layout->addWidget(labCar,0,0);
    layout->addWidget(cbxInsuranceSheng,0,1);
    layout->addWidget(cbxInsuranceZimu,0,2);
    layout->addWidget(editInsuranceCarNum,0,3);
    layout->addWidget(labInsurancetime,1,0);
    layout->addWidget(InsuranceTime,1,1,1,2);
    layout->addWidget(labFree,2,0);
    layout->addWidget(editInsuranceFree,2,1);
    layout->addWidget(labMoney,2,2);
    layout->addWidget(labInsuranceRemark,3,0);
    layout->addWidget(TeInsuranceRemark,3,1,1,3);
    layout->addWidget(btnInsuranceOK,4,0);
    layout->addWidget(btnInsuranceReturn,4,1);
    layout->addWidget(btnInsuranceReset,4,2);


    QWidget *widget1 = new QWidget();
    widget1->setLayout(layout);
    //添加到主布局
    this->setCentralWidget(widget1);
}

/*初始化修改界面*/
void NewInsuranceOrAccident::initInsuranceDialog(QString carid,QString oldtime,QString oldFare,QString oldRemark)
{
    int CarSheng = cbxInsuranceSheng->findText(carid.mid(0,1));
    int CarZimu = cbxInsuranceZimu->findText(carid.mid(1,1));
    int length = carid.length();
    QString oldNum = carid.mid(2,length);
    cbxInsuranceSheng->setCurrentIndex(CarSheng);
    cbxInsuranceZimu->setCurrentIndex(CarZimu);
    editInsuranceCarNum->setText(oldNum);

    QTime time;

    time = QTime::fromString(oldtime, "yyyy-MM-ddThh:mm:ss");
    InsuranceTime->setTime(time);
    editInsuranceFree->setText(oldFare);
    TeInsuranceRemark->setText(oldRemark);
}

void NewInsuranceOrAccident::initaddNewAccidentDialog(QString carid,QString oldtime)
{
    showCarid->setText(carid);
    labShowInsurancetime->setText(oldtime);

}

void NewInsuranceOrAccident::DialogClose()
{
    //设置窗口关闭的标志
       if(type != 1 && insType != "1"){
           Insurance_is_Open = false;
       }
       else if(insType != "1" && type == 1)
           editDialog_is_Open = false;
       else
           Accident_is_Open = false;


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

void NewInsuranceOrAccident::add()
{

    QString carNumber,insurancetime,InsuranceFree,carRemark;
    if(editInsuranceCarNum->text() != "")
    {
        carNumber = cbxInsuranceSheng->currentText().trimmed() + cbxInsuranceZimu->currentText().trimmed() + editInsuranceCarNum->text();
        qDebug() <<carNumber;
    }
    else
    {
        //弹出提示框
        QMessageBox::information(this, tr("提示"),tr("请输入车牌号码"),QMessageBox::Ok, QMessageBox::Ok);
        return;
    }

    if(InsuranceTime->text()!= "")
    {
        insurancetime = InsuranceTime->text();
        qDebug()<<insurancetime;
    }
    else
    {
        //弹出提示框
        QMessageBox::information(this, tr("提示"),tr("请输入车险过期时间"),QMessageBox::Ok, QMessageBox::Ok);
        return;
    }
    if(editInsuranceFree->text() != "")
    {
        InsuranceFree = editInsuranceFree->text();
    }
    else
    {
        //弹出提示框
        QMessageBox::information(this, tr("提示"),tr("请输入车险价格"),QMessageBox::Ok, QMessageBox::Ok);
        return;
    }

    carRemark = TeInsuranceRemark->toPlainText();

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
    QString query2("insert into insurance(carid,insurancetime,fare,remark) values('" + carNumber + "','" + insurancetime + "','" + InsuranceFree + "','" + carRemark + "');");
    qDebug()<<query2;
    query->prepare(query2);
    if(query->exec()){
        QMessageBox::information(this, tr("提示"),tr("添加成功！"),QMessageBox::Ok, QMessageBox::Ok);
    }
    else{
        QMessageBox::information(this, tr("提示"),tr("添加失败！"),QMessageBox::Ok, QMessageBox::Ok);
    }
    conn->getDB().close();
}

void NewInsuranceOrAccident::Accidentadd()
{
    QString carNumber,accidentplace,CompensateMoney,ACtime,carRemark;
    carNumber = showCarid->text();
    if(editAccidentPlace->toPlainText() != "")
    {
        accidentplace = editAccidentPlace->toPlainText();
    }
    else
    {
        //弹出提示框
        QMessageBox::information(this, tr("提示"),tr("请输入事故地点"),QMessageBox::Ok, QMessageBox::Ok);
        return;
    }
    if(editCompensateMoney->text() != "")
    {
        CompensateMoney = editCompensateMoney->text();
    }
    else
    {
        //弹出提示框
        QMessageBox::information(this, tr("提示"),tr("请输入赔偿金额"),QMessageBox::Ok, QMessageBox::Ok);
        return;
    }
    if(AccidentACtime->text() != "")
    {
        ACtime = AccidentACtime->text();
    }
    else
    {
        //弹出提示框
        QMessageBox::information(this, tr("提示"),tr("请输入事故时间"),QMessageBox::Ok, QMessageBox::Ok);
        return;
    }

    carRemark = TeAccidentRemark->toPlainText();

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
    QString query2("insert into accident(carid,accidentPlace,compensateMoney,accidenttime,remark) values('" + carNumber + "','" + accidentplace + "','" + CompensateMoney + "','" + ACtime + "','" + carRemark + "');");
    query->prepare(query2);
    if(query->exec()){
        QMessageBox::information(this, tr("提示"),tr("添加成功！"),QMessageBox::Ok, QMessageBox::Ok);
    }
    else{
        QMessageBox::information(this, tr("提示"),tr("添加失败！"),QMessageBox::Ok, QMessageBox::Ok);
    }
    QString query3("update insurance set accidentnum = accidentnum + 1 where carid ='" + carNumber + "';");
    query->prepare(query3);
    query->exec();
    conn->getDB().close();
}

void NewInsuranceOrAccident::editInsurance()
{
    QString carNumber,insurancetime,InsuranceFree,carRemark;
    if(editInsuranceCarNum->text() != "")
    {
        carNumber = cbxInsuranceSheng->currentText().trimmed() + cbxInsuranceZimu->currentText().trimmed() + editInsuranceCarNum->text();
        qDebug() <<carNumber;
    }
    else
    {
        //弹出提示框
        QMessageBox::information(this, tr("提示"),tr("请输入车牌号码"),QMessageBox::Ok, QMessageBox::Ok);
        return;
    }

    if(InsuranceTime->text()!= "")
    {
        insurancetime = InsuranceTime->text();
        qDebug()<<insurancetime;
    }
    else
    {
        //弹出提示框
        QMessageBox::information(this, tr("提示"),tr("请输入车险过期时间"),QMessageBox::Ok, QMessageBox::Ok);
        return;
    }
    if(editInsuranceFree->text() != "")
    {
        InsuranceFree = editInsuranceFree->text();
    }
    else
    {
        //弹出提示框
        QMessageBox::information(this, tr("提示"),tr("请输入车险价格"),QMessageBox::Ok, QMessageBox::Ok);
        return;
    }

    carRemark = TeInsuranceRemark->toPlainText();

    conn->getDB().open();

    QSqlQuery *query = new QSqlQuery;
    QString query1("update insurance set carid = '" + carNumber +"', insurancetime = '" + insurancetime +"', fare = '" + InsuranceFree +"', remark = '" + carRemark +"' where carid = '" + carNumber + "';");
    query->prepare(query1);
    if(query->exec()){
        QMessageBox::information(this, tr("提示"),tr("修改成功！"),QMessageBox::Ok, QMessageBox::Ok);
    }
    else{
        QMessageBox::information(this, tr("提示"),tr("修改失败！"),QMessageBox::Ok, QMessageBox::Ok);
    }
    conn->getDB().close();
}

//重置添加事故信息窗口
void NewInsuranceOrAccident::ResetNewAccident()
{
    editAccidentPlace->setText("");
    editCompensateMoney->setText("");
    TeAccidentRemark->setText("");
}

//重置添加车险信息窗口
void NewInsuranceOrAccident::ResetNewInsurance()
{
    cbxInsuranceSheng->setCurrentIndex(0);
    cbxInsuranceZimu->setCurrentIndex(0);
    editInsuranceCarNum->setText("");
    editInsuranceFree->setText("");
    TeInsuranceRemark->setText("");
}

//重置修改车险信息窗口
void NewInsuranceOrAccident::ResetEditInsurance()
{
    cbxInsuranceSheng->setCurrentIndex(0);
    cbxInsuranceZimu->setCurrentIndex(0);
    editInsuranceCarNum->setText("");
    editInsuranceFree->setText("");
    TeInsuranceRemark->setText("");
}


void NewInsuranceOrAccident::closeEvent(QCloseEvent *event)
{
    DialogClose();
}


NewInsuranceOrAccident::~NewInsuranceOrAccident(){}

