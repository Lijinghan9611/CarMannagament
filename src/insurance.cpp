#include "insurance.h"
#include <QGroupBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QHeaderView>
#include <qsqlquery.h>
#include <QMessageBox>
#include <QListView>
#include "newinsuranceoraccident.h"
NewInsuranceOrAccident *InsuranceDialog, *addAccidentDialog, *editInsuranceDialog;
Insurance::Insurance(Connect *c, QWidget *parent) : QWidget(parent)
{
    conn = c;
    rowCount = 0;

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

    labInsurance = new QLabel("车牌：");  //“车牌”
    cbxInsuranceSheng = new QComboBox();  //省份选择
    cbxInsuranceZimu = new QComboBox();    //车辆省份字母
    editInsuranceCarNum = new QLineEdit();  //输入车牌信息
    btnInsuranceSearch = new QPushButton("查询");  //查询
    btnInsuranceSearchAll= new QPushButton("显示所有");  //查询所有
    btnInsuranceAdd= new QPushButton("添加");  //添加
    btnInsuranceDelete= new QPushButton("删除");  //删除

    labCarnum = new QLabel("车牌:");
    showCarnum = new QLabel("");
    labtime = new QLabel("车险到期时间:");
    showTime = new QLabel("");
    labFare = new QLabel("费用:");
    showFare = new QLabel("");
    labAccidentNum = new QLabel("出险次数:");
    showAccidentNum = new QLabel("");
    labRemark = new QLabel("备注:");
    showRemark = new QLabel("");
    addAccident = new QPushButton("添加出险记录");
    btnEditInsurance = new QPushButton("修改");
    btnDeleteAccident = new QPushButton("删除记录");

    cbxInsuranceSheng->addItems(Items);
    cbxInsuranceZimu->addItems(Items1);

    cbxInsuranceSheng->setStyleSheet("QComboBox { min-height: 15px; min-width: 25px;}"
                                     "QComboBox QAbstractItemView::item{height:20px;}");
    cbxInsuranceSheng->setView(new QListView());
    cbxInsuranceZimu->setStyleSheet("QComboBox { min-height: 15px; min-width: 25px;}"
                                    "QComboBox QAbstractItemView::item{height:20px;}");
    cbxInsuranceZimu->setView(new QListView());
    //第一部分
    QGroupBox *box1 = new QGroupBox("查询车险信息");
    QHBoxLayout *Layout1 = new QHBoxLayout();

    Layout1->addWidget(labInsurance);
    Layout1->addWidget(cbxInsuranceSheng);
    Layout1->addWidget(cbxInsuranceZimu);
    Layout1->addWidget(editInsuranceCarNum);
    Layout1->addWidget(btnInsuranceSearch);
    Layout1->addWidget(btnInsuranceSearchAll);
    Layout1->addWidget(btnInsuranceAdd);
    Layout1->addWidget(btnInsuranceDelete);
    Layout1->addStretch(10);
    box1->setLayout(Layout1);
    //第二部分
    QGroupBox *box2 = new QGroupBox("显示车险信息");
    QHBoxLayout *Layout2 = new QHBoxLayout();

    Layout2->addWidget(labCarnum);
    Layout2->addWidget(showCarnum);
    Layout2->addWidget(labtime);
    Layout2->addWidget(showTime);
    Layout2->addWidget(labFare);
    Layout2->addWidget(showFare);
    Layout2->addWidget(labAccidentNum);
    Layout2->addWidget(showAccidentNum);
    Layout2->addWidget(labRemark);
    Layout2->addWidget(showRemark);
    Layout2->addWidget(addAccident);
    Layout2->addWidget(btnEditInsurance);
    Layout2->addWidget(btnDeleteAccident);
    box2->setLayout(Layout2);

    /*连接槽函数*/
    connect(btnInsuranceAdd, SIGNAL(clicked()), this, SLOT(InsuranceAdd()));
    connect(addAccident, SIGNAL(clicked()), this, SLOT(addNewAccident()));
    connect(btnEditInsurance, SIGNAL(clicked()), this, SLOT(editInsurance()));
    connect(btnInsuranceSearch, SIGNAL(clicked()), this, SLOT(Search()));
    connect(btnInsuranceSearchAll, SIGNAL(clicked()), this, SLOT(SearchAll()));
    connect(btnInsuranceDelete, SIGNAL(clicked()), this, SLOT(Delete()));
    connect(btnDeleteAccident, SIGNAL(clicked()), this, SLOT(DeleteAccident()));

    QRegExp rx1("[0-9A-Z]{5}");
    editInsuranceCarNum->setValidator(new QRegExpValidator(rx1, editInsuranceCarNum));

    // 先查询才能显示
    addAccident->setEnabled(false);
    btnEditInsurance->setEnabled(false);
    btnDeleteAccident->setEnabled(false);
    btnInsuranceDelete->setEnabled(false);

    //第三部分
    InsuranceTableWidget = new QTableWidget(13,6);
    InsuranceTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);  //设置表格等宽

    connect(InsuranceTableWidget, SIGNAL(cellChanged(int,int)), this, SLOT(Edit(int,int)));
    connect(InsuranceTableWidget, SIGNAL(cellChanged(int,int)), this, SLOT(EditAccident(int,int)));

    //设置表头
    QStringList header;
    header<<"ID"<<"车牌号码"<<"事故地点"<<"维修费用"<<"事故时间"<<"备注";   //表列名
    InsuranceTableWidget->setHorizontalHeaderLabels(header);

    QGridLayout *Layout3 = new QGridLayout();
    Layout3->addWidget(InsuranceTableWidget);
    QGroupBox *box3 = new QGroupBox("显示");
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

    InsuranceDialog = new NewInsuranceOrAccident(conn, this);
    editInsuranceDialog = new NewInsuranceOrAccident(1,conn, this);
    addAccidentDialog = new NewInsuranceOrAccident("1", conn, this);
}

void Insurance::Search()
{
    showCarnum->setText(0);
    showTime->setText(0);
    showFare->setText(0);
    showAccidentNum->setText(0);
    showRemark->setText(0);
    btnInsuranceDelete->setEnabled(false);
    InsuranceTableWidget->setColumnCount(6);
    QStringList header;
    header<<"ID"<<"车牌号码"<<"事故地点"<<"维修费用"<<"事故时间"<<"备注";   //表列名
    InsuranceTableWidget->setHorizontalHeaderLabels(header);
    rowCount = InsuranceTableWidget->rowCount();
    if(13 < rowCount)
        for(int i = rowCount; 13 <= i;i--)
            InsuranceTableWidget->removeRow(i);
    rowCount = 0;
    InsuranceTableWidget->clearContents();
    QString carNumber;
    if(editInsuranceCarNum->text() != "")
    {
        carNumber = cbxInsuranceSheng->currentText().trimmed() + cbxInsuranceZimu->currentText().trimmed() + editInsuranceCarNum->text();
    }
    else
    {
        //弹出警告提示框
        QMessageBox::warning(this, tr("警告"),tr("请输入车牌号码"),QMessageBox::Ok, QMessageBox::Ok);
        return;
    }

    conn->getDB().open();
    QString query1("select carid,insurancetime,fare,accidentnum,remark from insurance where carid ='" + carNumber + "';");
    QSqlQuery *query = new QSqlQuery;
    query->prepare(query1);
    bool a = false;
    if(query->exec()){
        while(query->next()){
            showCarnum->setText(query->value(0).toString());
            showTime->setText(query->value(1).toString());
            showFare->setText(query->value(2).toString());
            showAccidentNum->setText(query->value(3).toString());
            showRemark->setText(query->value(4).toString());
            a = true;
            addAccident->setEnabled(true);
            btnEditInsurance->setEnabled(true);
            btnDeleteAccident->setEnabled(true);
        }
    }
    if(!a){
        QMessageBox::information(this, tr("提示"),tr("没有搜索到数据"),QMessageBox::Ok, QMessageBox::Ok);
    }
    conn->getDB().close();

    conn->getDB().open();
    QString query2("select id,carid,accidentplace,compensatemoney,accidenttime,remark from accident where carid ='" + carNumber + "';");
    query->prepare(query2);
    int i = 0;
    if(query->exec()){
        while(query->next()){
            if(rowCount > 12)
            {
                int insertRowId = rowCount;
                InsuranceTableWidget->insertRow(insertRowId);
            }
            for(int j = 0; j < 6; j++){
                QTableWidgetItem *item = new QTableWidgetItem(query->value(j).toString());
                                item->setTextAlignment(Qt::AlignCenter);  //居中
                                InsuranceTableWidget->setItem( i, j, item);
            }
            i++;
            rowCount++;
            a = true;
        }
    }
    if(!a){
        QMessageBox::information(this, tr("提示"),tr("没有搜索到数据"),QMessageBox::Ok, QMessageBox::Ok);
    }
    conn->getDB().close();
}

void Insurance::SearchAll()
{
    showCarnum->setText(0);
    showTime->setText(0);
    showFare->setText(0);
    showAccidentNum->setText(0);
    showRemark->setText(0);
    addAccident->setEnabled(false);
    btnEditInsurance->setEnabled(false);
    btnDeleteAccident->setEnabled(false);
    InsuranceTableWidget->setColumnCount(6);
    QStringList header1;
    header1<<"ID"<<"车牌号码"<<"车险过期时间"<<"车险价格"<<"事故数量"<<"备注";   //表列名
    InsuranceTableWidget->setHorizontalHeaderLabels(header1);
    rowCount = InsuranceTableWidget->rowCount();
    if(13 < rowCount)
        for(int i = rowCount; 13 <= i;i--)
            InsuranceTableWidget->removeRow(i);
    rowCount = 0;
    conn->getDB().open();
    InsuranceTableWidget->clearContents();
    QString query1("select id,carid,insurancetime,fare,accidentnum,remark from insurance;");
    QSqlQuery *query = new QSqlQuery;
    query->prepare(query1);
    bool a = false;
    int i = 0;
    if(query->exec()){
        while(query->next()){
            if(rowCount > 12)
            {
                int insertRowId = rowCount;
                InsuranceTableWidget->insertRow(insertRowId);
            }
            for(int j = 0; j < 6; j++){
                QTableWidgetItem *item = new QTableWidgetItem(query->value(j).toString());
                                item->setTextAlignment(Qt::AlignCenter);  //居中
                                InsuranceTableWidget->setItem( i, j, item);
            }
            i++;
            rowCount++;
            a = true;
            btnInsuranceDelete->setEnabled(true);
        }
    }
    if(!a){
        QMessageBox::information(this, tr("提示"),tr("没有搜索到数据"),QMessageBox::Ok, QMessageBox::Ok);
    }
    conn->getDB().close();
}

void Insurance::Edit(int a,int b)
{
    if(a+1 > rowCount)  //非法修改空格返回
        return;
    QString string,id,query1;
    string = InsuranceTableWidget->item(a,b)->text();
    id = InsuranceTableWidget->item(a,0)->text();
    if(b == 0){
        query1 = "update insurance set id = '" +string + "' where id ='" + id + "';";
    }
    else if(b == 1){
        query1 = "update insurance set carid = '" +string + "' where id ='" + id + "';";
    }
    else if(b == 2){
        query1 = "update insurancee set insurancetime = '" +string + "' where id ='" + id + "';";
    }
    else if(b == 3){
        query1 = "update insurance set fare = '" +string + "' where id ='" + id + "';";
    }
    else if(b == 4){
        query1 = "update insurance set accidentnum = '" +string + "' where id ='" + id + "';";
    }
    else if(b == 5){
        query1 = "update insurance set remark = '" +string + "' where id ='" + id + "';";
    }

    conn->getDB().open();
    QSqlQuery *query = new QSqlQuery;
    query->prepare(query1);
    if(query->exec(query1)){
        QMessageBox::information(this, tr("提示"),tr("修改成功！"),QMessageBox::Ok, QMessageBox::Ok);
    }else{
        QMessageBox::information(this, tr("提示"),tr("修改失败！"),QMessageBox::Ok, QMessageBox::Ok);
    }
    conn->getDB().close();
}

void Insurance::EditAccident(int a,int b)
{
    if(a+1 > rowCount)  //非法修改空格返回
        return;
    QString string,id,query1;
    string = InsuranceTableWidget->item(a,b)->text();
    id = InsuranceTableWidget->item(a,0)->text();
    if(b == 0){
        query1 = "update accident set id = '" +string + "' where id ='" + id + "';";
    }
    else if(b == 1){
        query1 = "update accident set carid = '" +string + "' where id ='" + id + "';";
    }
    else if(b == 2){
        query1 = "update accident set accidentplace = '" +string + "' where id ='" + id + "';";
    }
    else if(b == 3){
        query1 = "update accident set compensatemoney = '" +string + "' where id ='" + id + "';";
    }
    else if(b == 4){
        query1 = "update accident set accidenttime = '" +string + "' where id ='" + id + "';";
    }
    else if(b == 5){
        query1 = "update accident set remark = '" +string + "' where id ='" + id + "';";
    }

    conn->getDB().open();
    QSqlQuery *query = new QSqlQuery;
    query->prepare(query1);
    if(query->exec(query1)){
        QMessageBox::information(this, tr("提示"),tr("修改成功！"),QMessageBox::Ok, QMessageBox::Ok);
    }else{
        QMessageBox::information(this, tr("提示"),tr("修改失败！"),QMessageBox::Ok, QMessageBox::Ok);
    }
    conn->getDB().close();
}

void Insurance::Delete()
{
    QString query = "";
    conn->getDB().open();
    QList<QTableWidgetItem*>items=InsuranceTableWidget->selectedItems();  //获取选定的内容
    int count=items.count();  //获取选定的数目，每个单元格单独计数

    if(count == 0)  //没有选定内容
    {
        //弹出提示框
        QMessageBox::information(this, tr("提示"),tr("没有选定内容。"),QMessageBox::Ok, QMessageBox::Ok);
        return;
    }

    //弹出警告提示框
    QMessageBox box(QMessageBox::Warning,"确认删除？","删除后数据不能恢复，请注意备份。");
    box.setStandardButtons (QMessageBox::Ok|QMessageBox::Cancel);
    box.setButtonText (QMessageBox::Ok,QString("确定"));
    box.setButtonText (QMessageBox::Cancel,QString("取消"));
    switch(box.exec()){
    case QMessageBox::Ok:
        break;
    case QMessageBox::Cancel:
        return;
    default:
        return;
    }

    for(int i=0;i<count;i+=6)  //只获取每行第一列
    {
        QTableWidgetItem*item=items.at(i);
        QString name = item->text();//获取内容
        int row =InsuranceTableWidget->row(items.at(i));//获取选中的行
        InsuranceTableWidget->removeRow(row);
        query = "delete from insurance where id = '"+name+"'";
        //执行语句
        QSqlQuery *exe = new QSqlQuery;
        exe->exec(query);
    }
    conn->getDB().close();
}

void Insurance::DeleteAccident()
{
    QString query = "";
    conn->getDB().open();
    QList<QTableWidgetItem*>items=InsuranceTableWidget->selectedItems();  //获取选定的内容
    int count=items.count();  //获取选定的数目，每个单元格单独计数

    if(count == 0)  //没有选定内容
    {
        //弹出提示框
        QMessageBox::information(this, tr("提示"),tr("没有选定内容。"),QMessageBox::Ok, QMessageBox::Ok);
        return;
    }

    //弹出警告提示框
    QMessageBox box(QMessageBox::Warning,"确认删除？","删除后数据不能恢复，请注意备份。");
    box.setStandardButtons (QMessageBox::Ok|QMessageBox::Cancel);
    box.setButtonText (QMessageBox::Ok,QString("确定"));
    box.setButtonText (QMessageBox::Cancel,QString("取消"));
    switch(box.exec()){
    case QMessageBox::Ok:
        break;
    case QMessageBox::Cancel:
        return;
    default:
        return;
    }

    int num = 0;
    for(int i=0;i<count;i+=6)  //只获取每行第一列
    {
        QTableWidgetItem*item=items.at(i);
        QString name = item->text();//获取内容
        int row =InsuranceTableWidget->row(items.at(i));//获取选中的行
        InsuranceTableWidget->removeRow(row);
        query = "delete from accident where id = '"+name+"'";
        //执行语句
        QSqlQuery *exe = new QSqlQuery;
        exe->exec(query);
        num = num + 1;
    }
    QSqlQuery *query0 = new QSqlQuery;
    QString n = QString::number(num, 10);
    QString query1 = "update insurance set accidentnum = accidentnum - " + n + " where carid = '" + showCarnum->text() +"'";
    qDebug()<<n << query1;
    query0->prepare(query1);
    query0->exec();
    conn->getDB().close();
}


/*添加新的出险记录*/
void Insurance::addNewAccident()
{
    if(!addAccidentDialog->Accident_is_Open)
    {
        QString carid = showCarnum->text();
        QString oldtime = showTime->text();
        addAccidentDialog->initaddNewAccidentDialog(carid,oldtime);
        addAccidentDialog->editDialog_is_Open = true;
        addAccidentDialog->show();
    }
}

/*添加车险信息*/
void Insurance::InsuranceAdd()
{
    if(!InsuranceDialog->Insurance_is_Open){
        InsuranceDialog->Insurance_is_Open = true;
        InsuranceDialog->show();

    }
}
/*修改车险信息*/
void Insurance::editInsurance()
{
    if(!editInsuranceDialog->editDialog_is_Open )
    {
        QString carid = showCarnum->text();
        QString oldtime = showTime->text();
        QString oldFare = showFare->text();
        QString oldRemark = showRemark->text();
        editInsuranceDialog->initInsuranceDialog(carid,oldtime,oldFare,oldRemark);
        editInsuranceDialog->editDialog_is_Open = true;
        editInsuranceDialog->show();

    }
}

