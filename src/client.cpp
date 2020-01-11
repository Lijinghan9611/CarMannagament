#include "client.h"
#include <QHBoxLayout>
#include <QGroupBox>
#include <QHeaderView>
#include "newclient.h"
#include <QMessageBox>
#include <QSqlQuery>
NewClient *client, *editClientval;
QGroupBox *box3;
Client::Client(Connect *c, QWidget *parent) : QWidget(parent)
{
    conn = c;

    labName = new QLabel("姓名或车牌：");
    editName = new QLineEdit();
    btnSearch = new QPushButton("查询");
    btnSearchAll = new QPushButton("显示所有用户");
    btnAdd= new QPushButton("添加");;  //添加
    btnEdit= new QPushButton("修改");;  //修改

    labShowCarId = new QLabel("车牌号码：");
    ShowCarId= new QLabel("");
    labShowName= new QLabel("姓名：");
    ShowName= new QLabel("");
    labShowPhone= new QLabel("电话号码：");
    ShowPhone= new QLabel("");
    labShowAddress= new QLabel("地址：");
    ShowAddress= new QLabel("");
    labShowRemark= new QLabel("备注：");
    ShowRemark= new QLabel("");

    QHBoxLayout *Layout1 = new QHBoxLayout();

    Layout1->addWidget(labName);
    Layout1->addWidget(editName);
    Layout1->addWidget(btnSearch);   
    Layout1->addWidget(btnAdd);
    Layout1->addStretch(10);
    Layout1->addWidget(btnSearchAll);
    QGroupBox *box1 = new QGroupBox("客户");
    box1->setLayout(Layout1);

    btnEdit->setEnabled(false);

    /*连接槽函数*/
    connect(btnAdd, SIGNAL(clicked()), this, SLOT(addNewClient()));
    connect(btnEdit, SIGNAL(clicked()), this, SLOT(editClient()));
    connect(btnSearch, SIGNAL(clicked()), this, SLOT(SearchClient()));
    connect(btnSearchAll, SIGNAL(clicked()), this, SLOT(SearchAll()));


    //第二部分
    QGroupBox *box2 = new QGroupBox("客户信息");
    QHBoxLayout *Layout2 = new QHBoxLayout();

    Layout2->addWidget(labShowCarId);
    Layout2->addWidget(ShowCarId);
    Layout2->addWidget(labShowName);
    Layout2->addWidget(ShowName);
    Layout2->addWidget(labShowPhone);
    Layout2->addWidget(ShowPhone);
    Layout2->addWidget(labShowAddress);
    Layout2->addWidget(ShowAddress);
    Layout2->addWidget(labShowRemark);
    Layout2->addWidget(ShowRemark);
     Layout2->addWidget(btnEdit);
    box2->setLayout(Layout2);

    //第三部分
    clientTable = new QTableWidget(13,4);
    clientTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);  //设置表格等宽
    //设置表头
    QStringList header;
    header<<"车牌号码"<<"业务"<<"时间"<<"备注";   //表列名
    clientTable->setHorizontalHeaderLabels(header);

    QGridLayout *Layout3 = new QGridLayout();
    Layout3->addWidget(clientTable);
    box3 = new QGroupBox("客户所有记录");
    box3->setLayout(Layout3);

    //添加到主布局
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(box1);
    mainLayout->addWidget(box2);
    mainLayout->addWidget(box3);
    mainLayout->setStretchFactor(box1, 1);
    mainLayout->setStretchFactor(box2, 1);
    mainLayout->setStretchFactor(box3, 13);
    this->setLayout(mainLayout);

    client = new NewClient(conn, this);
    editClientval = new NewClient(conn, 1, this);
}

void Client::SearchAll()
{
    ShowCarId->setText("");
    ShowName->setText("");
    ShowPhone->setText("");
    ShowAddress->setText("");
    ShowRemark->setText("");

    box3->setTitle("所有客户");
    if(clientTable->columnCount() != 5)
        clientTable->insertColumn(4);
    //设置表头
    QStringList header;
    header<<"车牌号码"<<"姓名"<<"电话号码"<<"地址"<<"备注";   //表列名
    clientTable->setHorizontalHeaderLabels(header);
    btnEdit->setEnabled(false);
    clientTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    bool flag = false;  //判断是否查询到数据
    rowCount = clientTable->rowCount();
    if(16 < rowCount)
        for(int i = rowCount; 13 <= i;i--)
            clientTable->removeRow(i);
    rowCount = 0;
    conn->getDB().open();
    clientTable->clearContents();
    QString query1("select carid, name, phonenumber, address, remark from client;");
    QSqlQuery *query = new QSqlQuery;
    query->prepare(query1);
    int i = 0;
    if(query->exec()){
        while(query->next()){
            if(rowCount > 12)
            {
                int insertRowId = rowCount;
                clientTable->insertRow(insertRowId);
            }
            for(int j = 0; j < 5; j++){
                QTableWidgetItem *item = new QTableWidgetItem(query->value(j).toString());
                item->setTextAlignment(Qt::AlignCenter);  //居中
                clientTable->setItem( i, j, item);
            }
            i++;
            rowCount++;
            flag = true;
        }
    }
    if(!flag){
        QMessageBox::information(this, tr("提示"),tr("没有搜索到数据"),QMessageBox::Ok, QMessageBox::Ok);
    }
    conn->getDB().close();
}

void Client::SearchClient()
{  
    btnEdit->setEnabled(true);
    clientTable->setEditTriggers(QAbstractItemView::AllEditTriggers);
    box3->setTitle("客户所有记录");
    if(clientTable->columnCount() != 4)
        clientTable->removeColumn(4);
    //设置表头
    QStringList header;
    header<<"车牌号码"<<"业务"<<"时间"<<"备注";   //表列名
    clientTable->setHorizontalHeaderLabels(header);

    bool flag = false;  //判断是否查询到数据

    QString carNumber = editName->text();
    if( carNumber == "")
    {
        //弹出警告提示框
        QMessageBox::warning(this, tr("警告"),tr("请输入车牌号码或姓名。"),QMessageBox::Ok, QMessageBox::Ok);
        return;
    }
    conn->getDB().open();

    QString query("select * from client where carid = '" + carNumber + "' or name = '"+carNumber+"';");
    QSqlQuery *exe = new QSqlQuery;
    exe->prepare(query);
    if(exe->exec()){
        while(exe->next()){
            ShowCarId->setText(exe->value(1).toString());
            ShowName->setText(exe->value(2).toString());
            ShowPhone->setText(exe->value(3).toString());
            ShowAddress->setText(exe->value(4).toString());
            ShowRemark->setText(exe->value(5).toString());
            flag = true;
        }
    }

    rowCount = clientTable->rowCount();
    if(13 < rowCount)
        for(int i = rowCount; 13 <= i;i--){
            clientTable->removeRow(i);
            rowCount--;
        }
    clientTable->clearContents();
    query = "select carid, items, time,remark from maintenance "
            "where carid = (select carid "
            "from client "
            "where name = '"+carNumber+"' or carid = '"+carNumber+"')";
    //qDebug() << query;
    exe->prepare(query);
    int i = 0;
    if(exe->exec()){
        while(exe->next()){
            if(rowCount > 12)
            {
                int insertRowId = rowCount;
                clientTable->insertRow(insertRowId);
            }
            for(int j = 0; j < 4; j++){
                QTableWidgetItem *item = new QTableWidgetItem(exe->value(j).toString());
                item->setTextAlignment(Qt::AlignCenter);  //居中
                clientTable->setItem( i, j, item);
            }
            i++;
            rowCount++;
        }
    }

    query = "select carid, accidenttime, remark from accident "
            "where carid = (select carid "
            "from client "
            "where name = '"+carNumber+"' or carid = '"+carNumber+"')";
    // qDebug() << query;
    exe->prepare(query);
    if(exe->exec()){
        while(exe->next()){
            if(rowCount > 12)
            {
                int insertRowId = rowCount;
                clientTable->insertRow(insertRowId);
            }
            int val = 0;
            for(int j = 0; j < 4; j++){
                if(j == 1)
                {
                    QTableWidgetItem *item = new QTableWidgetItem("出险");
                    item->setTextAlignment(Qt::AlignCenter);  //居中
                    clientTable->setItem( i, j, item);
                }
                else
                {
                    QTableWidgetItem *item = new QTableWidgetItem(exe->value(val).toString());
                    item->setTextAlignment(Qt::AlignCenter);  //居中
                    clientTable->setItem( i, j, item);
                    val++;
                }
            }
            i++;
            rowCount++;
        }
    }

    query = "select carid, bathclass, bathtime,remark from bathrecord "
            "where carid = (select carid "
            "from client "
            "where name = '"+carNumber+"' or carid = '"+carNumber+"')";
    // qDebug() << query;
    exe->prepare(query);
    if(exe->exec()){
        while(exe->next()){
            if(rowCount > 12)
            {
                int insertRowId = rowCount;
                clientTable->insertRow(insertRowId);
            }
            for(int j = 0; j < 4; j++){
                QTableWidgetItem *item = new QTableWidgetItem(exe->value(j).toString());
                item->setTextAlignment(Qt::AlignCenter);  //居中
                clientTable->setItem( i, j, item);
            }
            i++;
            rowCount++;
        }
    }

    if(!flag){
        QMessageBox::information(this, tr("提示"),tr("没有搜索到数据"),QMessageBox::Ok, QMessageBox::Ok);
    }

    conn->getDB().close();

}

void Client::editClient()
{
    if(ShowCarId->text() == "")
    {
        QMessageBox::information(this, tr("提示"),tr("请先查询顾客信息。"),QMessageBox::Ok, QMessageBox::Ok);
        return;
    }
    if(!editClientval->editClient_is_open)
    {
        editClientval->editClient_is_open = true;

        QString carnum = ShowCarId->text();
        QString name  = ShowName->text();
        QString phone = ShowPhone->text();
        QString addr = ShowAddress->text();
        QString remark = ShowRemark->text();

        //editClientval->initEditClientDialog("粤A88888", "小明", "18816746414", "mnioadfg","165411");

        editClientval->initEditClientDialog(carnum, name, phone, addr,remark);

        editClientval->show();
    }
}
void Client::addNewClient()
{
    if(!client->Dialog_is_Open)
    {
        client->Dialog_is_Open = true;
        client->show();
    }
}

