#include "bathcar.h"
#include <QGridLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QHeaderView>
#include "newbathcar.h"
#include <QDebug>
#include <QMessageBox>
#include <QListView>
#include <QSqlQuery>
NewBathCar *bathcard, *addCarid;
bathcar::bathcar(Connect *c, QWidget *parent) : QWidget(parent)
{
    is_addRecord = false;
    QStringList Items;
    conn = c;
    rowCount = 0;
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

    labBathCardNum = new QLabel("车牌：");  //“车牌”
    cbxBathCardSheng = new QComboBox;  //省份选择
    cbxBathCardZimu = new QComboBox;    //车辆省份字母
    editBathCardCarNum = new QLineEdit;  //输入车牌信息
    btnBathCardSearch = new QPushButton("查询");  //查询
    btnBathCardSearchAll = new QPushButton("查询所有洗车记录");  //查询所有
    btnBathCardAdd = new QPushButton("添加洗车卡");  //添加
    btnaddBathRecord = new QPushButton("打卡");
    btnBathCardDelete = new QPushButton("删除洗车记录");  //删除
    btnBugCard = new QPushButton("充卡");
    btnAddNewCar = new QPushButton("添加新的绑定车牌");

    labCard = new QLabel("洗车卡号码：");  //“车牌”
    CardNum = new QLabel();
    labCarnums = new QLabel("绑定的车牌");
    cbxCarnums = new QComboBox();

    labType = new QLabel("洗车卡类型：");
    type = new QLabel();   //类型
    labTimes = new QLabel("洗车次数：");
    Times = new QLabel();  //次数
    labRemark = new QLabel("备注：");
    Remark = new QLabel();    //备注

    cbxBathCardSheng->addItems(Items);
    cbxBathCardZimu->addItems(Items1);

    cbxBathCardSheng->setStyleSheet("QComboBox { min-height: 15px; min-width: 25px;}"
                                    "QComboBox QAbstractItemView::item{height:20px;}");
    cbxBathCardSheng->setView(new QListView());
    cbxBathCardZimu->setStyleSheet("QComboBox { min-height: 15px; min-width: 25px;}"
                                   "QComboBox QAbstractItemView::item{height:20px;}");
    cbxBathCardZimu->setView(new QListView());
    cbxCarnums->setStyleSheet("QComboBox { min-height: 20px; min-width: 25px;}"
                              "QComboBox QAbstractItemView::item{height:20px;}");
    cbxCarnums->setView(new QListView());


    /*连接槽函数*/
    connect(btnBathCardAdd, SIGNAL(clicked()), this, SLOT(addNewBathCard()));
    connect(btnBathCardSearch, SIGNAL(clicked()), this, SLOT(Search()));
    connect(btnBathCardSearchAll, SIGNAL(clicked()), this, SLOT(SearchAll()));
    connect(btnaddBathRecord, SIGNAL(clicked()), this, SLOT(addBathRecord()));
    connect(btnBugCard, SIGNAL(clicked()), this, SLOT(addbathTimes()));
    connect(btnAddNewCar, SIGNAL(clicked()), this, SLOT(OpenAddCarid()));
    connect(btnBathCardDelete, SIGNAL(clicked()), this, SLOT(deleteBathRecord()));


    //第一部分
    QGroupBox *box1 = new QGroupBox("功能");
    QHBoxLayout *Layout1 = new QHBoxLayout();

    Layout1->addWidget(labBathCardNum);
    Layout1->addWidget(cbxBathCardSheng);
    Layout1->addWidget(cbxBathCardZimu);
    Layout1->addWidget(editBathCardCarNum);
    Layout1->addWidget(btnBathCardSearch);
    Layout1->addWidget(btnBathCardSearchAll);
    Layout1->addWidget(btnBathCardAdd);
    Layout1->addWidget(btnBathCardDelete);
    Layout1->addStretch(10);
    box1->setLayout(Layout1);
    //第二部分
    QGroupBox *box2 = new QGroupBox("洗车卡信息");
    QHBoxLayout *Layout2 = new QHBoxLayout();

    Layout2->addWidget(labCard);
    Layout2->addWidget(CardNum);
    Layout2->addWidget(labType);
    Layout2->addWidget(type);
    Layout2->addWidget(labTimes);
    Layout2->addWidget(Times);
    Layout2->addWidget(labRemark);
    Layout2->addWidget(Remark);
    Layout2->addWidget(labCarnums);
    Layout2->addWidget(cbxCarnums);
    Layout2->addWidget(btnaddBathRecord);
    Layout2->addWidget(btnBugCard);
    Layout2->addWidget(btnAddNewCar);

    box2->setLayout(Layout2);

    btnaddBathRecord->setEnabled(false);
    btnBugCard->setEnabled(false);
    btnAddNewCar->setEnabled(false);


    QRegExp rx1("[0-9A-Z]{5}");
    editBathCardCarNum->setValidator(new QRegExpValidator(rx1, editBathCardCarNum));

    //第三部分
    BathCarTableWidget = new QTableWidget(13,5);
    BathCarTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);  //设置表格等宽
    //设置表头
    QStringList header;
    header<<"记录ID"<<"车牌号码"<<"洗车类型"<<"洗车时间"<<"备注";   //表列名
    BathCarTableWidget->setHorizontalHeaderLabels(header);
    connect(BathCarTableWidget, SIGNAL(cellChanged(int, int)), this, SLOT(slotItemChanged(int , int)));

    QGridLayout *Layout3 = new QGridLayout();
    Layout3->addWidget(BathCarTableWidget);
    QGroupBox *box3 = new QGroupBox("洗车记录");
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

    bathcard = new NewBathCar(conn, this);
    addCarid = new NewBathCar(conn, 1, this);
}

void bathcar::deleteBathRecord()
{
    QString query = "";
    conn->getDB().open();
    QList<QTableWidgetItem*>items=BathCarTableWidget->selectedItems();  //获取选定的内容
    int count=items.count();  //获取选定的数目，每个单元格单独计数

    if(count == 0)  //没有选定内容
    {
        //弹出提示框
        QMessageBox::information(this, tr("提示"),tr("没有选定内容。"),QMessageBox::Ok, QMessageBox::Ok);
        return;
    }

    //弹出警告提示框
    QMessageBox box(QMessageBox::Warning,"确认删除？","删除后数据不能恢复。");
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

    for(int i=0;i<count;i+=5)  //只获取每行第一列
    {
        QTableWidgetItem*item=items.at(i);
        QString name = item->text();//获取内容
        int row =BathCarTableWidget->row(items.at(i));//获取选中的行
        BathCarTableWidget->removeRow(row);
        query = "delete from bathrecord where id = '"+name+"'";

        //执行语句
        QSqlQuery *exe = new QSqlQuery;
        exe->exec(query);
    }
    conn->getDB().close();
}

void bathcar::addbathTimes()
{
    //添加次数
    int t = Times->text().toInt() + 10;

    conn->getDB().open();
    QString s = QString::number(t);
    QString query = "update bathcard set bathnum = '" + s + "' where id = '"+CardNum->text()+"'";
    //执行语句
    QSqlQuery *exe = new QSqlQuery;

    if(!exe->exec(query))
        QMessageBox::information(this, tr("提示"),tr("充卡失败"),QMessageBox::Ok, QMessageBox::Ok);
    //qDebug()<<query;
    conn->getDB().close();

    is_addRecord = true;
    Search();  //更新一下显示信息
}

void bathcar::addBathRecord()
{

    QString temp = cbxCarnums->currentText();
    //弹出警告提示框
    QMessageBox box(QMessageBox::Warning,"提示","打卡的车牌号码为："+temp);
    box.setStandardButtons (QMessageBox::Ok|QMessageBox::Cancel);
    box.setButtonText (QMessageBox::Ok,QString("确定打卡"));
    box.setButtonText (QMessageBox::Cancel,QString("取消"));
    switch(box.exec()){
    case QMessageBox::Ok:
        break;
    case QMessageBox::Cancel:
        return;
    default:
        return;
    }

    int t = Times->text().toInt();
    if(t <= 0)
    {
        QMessageBox::information(this, tr("提示"),tr("打卡失败,洗车次数不够"),QMessageBox::Ok, QMessageBox::Ok);
        return;
    }
    conn->getDB().open();

    //添加洗车记录
    QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
    QString str = time.toString("yyyy-MM-dd hh:mm:ss"); //设置显示格式
    QString query = "insert into bathrecord(carid, bathcardid, bathclass, bathtime,remark) values('"+temp+"','"+CardNum->text()+"', '"+type->text()+"','"+str+"', '')";
    //执行语句
    QSqlQuery *exe = new QSqlQuery;

    exe->exec(query);
    qDebug()<<query;

    //洗车卡次数-1
    t = t-1;
    QString s = QString::number(t);
    query = "update bathcard set bathnum = '" + s + "' where id = '"+CardNum->text()+"'";
    if(exe->exec(query))
        QMessageBox::information(this, tr("提示"),tr("打卡成功"),QMessageBox::Ok, QMessageBox::Ok);
    qDebug()<<query;
    conn->getDB().close();

    is_addRecord = true;
    Search();  //更新一下显示信息

}

void bathcar::Search()
{

    cbxCarnums->clear();  //清除下拉列表所有项

    bool flag = false;  //判断是否查询到数据
    rowCount = BathCarTableWidget->rowCount();
    if(13 < rowCount)
        for(int i = rowCount; 13 <= i;i--)
            BathCarTableWidget->removeRow(i);
    rowCount = 0;
    BathCarTableWidget->clearContents();
    QString carNumber;
    if(editBathCardCarNum->text() != "")
    {
        carNumber = cbxBathCardSheng->currentText().trimmed() + cbxBathCardZimu->currentText().trimmed() + editBathCardCarNum->text();
    }
    else
    {
        //弹出警告提示框
        QMessageBox::warning(this, tr("警告"),tr("请输入车牌号码"),QMessageBox::Ok, QMessageBox::Ok);
        return;
    }

    conn->getDB().open();
    QString query1;

    //如果不是是打卡
    if(!is_addRecord)
    {
        query1 = "SELECT id,bathclass,bathnum,remark from bathcard where id = (SELECT bathcardid from bathcard_carnum where carid = '"+carNumber+"')";

    }
    else
    {
        is_addRecord = false;
        query1 = "SELECT id,bathclass,bathnum,remark from bathcard where id = '"+CardNum->text()+"'";
    }

       // qDebug()<<query1;
    QSqlQuery *query = new QSqlQuery;
    QString bathCarNumber;
    query->prepare(query1);
    if(query->exec()){
        while(query->next()){
            CardNum->setText(query->value(0).toString());
            type->setText(query->value(1).toString());
            Times->setText(query->value(2).toString());
            Remark->setText(query->value(3).toString());
            flag = true;
            btnaddBathRecord->setEnabled(true);
            btnBugCard->setEnabled(true);
            btnAddNewCar->setEnabled(true);
            bathCarNumber = CardNum->text();
        }
    }

    //添加下拉列表项
    query1 = "select carid from bathcard_carnum where bathcardid = '"+bathCarNumber+"'";
    query->prepare(query1);
     //qDebug()<<query1;
    if(query->exec()){
        while(query->next()){
           cbxCarnums->addItem(query->value(0).toString());
        }
    }

    query1 = "select id, carid, bathclass, bathtime, remark from bathrecord where bathcardid ='" + bathCarNumber + "';";
    query->prepare(query1);
     //qDebug()<<query1;
    int i = 0;
    if(query->exec()){
        while(query->next()){
            if(rowCount > 12)
            {
                int insertRowId = rowCount;
                BathCarTableWidget->insertRow(insertRowId);
            }
            for(int j = 0; j < 5; j++){
                is_search = true;
                QTableWidgetItem *item = new QTableWidgetItem(query->value(j).toString());
                item->setTextAlignment(Qt::AlignCenter); //居中
                BathCarTableWidget->setItem( i, j, item);
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

void bathcar::SearchAll()
{
    CardNum->setText("");
    type->setText("");
    Times->setText("");
    Remark->setText("");
    cbxCarnums->clear();  //清除下拉列表所有项

    btnaddBathRecord->setEnabled(false);
    btnBugCard->setEnabled(false);
    btnAddNewCar->setEnabled(false);

    bool flag = false;  //判断是否查询到数据
    rowCount = BathCarTableWidget->rowCount();
    if(13 < rowCount)
        for(int i = rowCount; 13 <= i;i--){
            rowCount--;
            BathCarTableWidget->removeRow(i);
        }
    rowCount = 0;
    BathCarTableWidget->clearContents();
    conn->getDB().open();

    QString query1 = "select id, carid, bathclass, bathtime, remark from bathrecord;";
    QSqlQuery *query = new QSqlQuery;
    query->prepare(query1);
    int i = 0;
    if(query->exec()){
        while(query->next()){
            if(rowCount > 12)
            {
                int insertRowId = rowCount;
                BathCarTableWidget->insertRow(insertRowId);
            }
            for(int j = 0; j < 5; j++){
                is_search = true;
                QTableWidgetItem *item = new QTableWidgetItem(query->value(j).toString());
                item->setTextAlignment(Qt::AlignCenter); //居中
                BathCarTableWidget->setItem( i, j, item);
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

void bathcar::slotItemChanged(int row, int col)
{
    if(is_search)
    {
        is_search = false;
        return;
    }

    QString s = BathCarTableWidget->item(row, col)->text();

    if(row+1 > rowCount)  //非法修改空格返回
        return;

    QString string,id,query1;
    string = BathCarTableWidget->item(row,col)->text();
    id = BathCarTableWidget->item(row,0)->text();
    if(col == 0){
        QMessageBox::information(this, tr("修改无效"),tr("ID不可修改。"),QMessageBox::Ok, QMessageBox::Ok);
        return;
    }
    else if(col == 1){
        query1 = "update bathrecord set carid = '" +string + "' where id ='" + id + "';";
    }
    else if(col == 2){
        query1 = "update bathrecord set bathclass = '" +string + "' where id ='" + id + "';";
    }
    else if(col == 3){
        query1 = "update bathrecord set bathtime = '" +string + "' where id ='" + id + "';";
    }
    else if(col == 4){
        query1 = "update bathrecord set remark = '" +string + "' where id ='" + id + "';";
    }
    qDebug() << query1;
    conn->getDB().open();
    QSqlQuery *query = new QSqlQuery;
    query->prepare(query1);
    if(query->exec(query1))
    {
        QMessageBox::information(this, tr("提示"),tr("修改成功！"),QMessageBox::Ok, QMessageBox::Ok);
    }
    else
    {
       QMessageBox::information(this, tr("提示"),tr("修改失败！"),QMessageBox::Ok, QMessageBox::Ok);
    }
    conn->getDB().close();
}

void bathcar::OpenAddCarid()
{
    if(!addCarid->addCarid_is_Open)
    {
        addCarid->setBathCardId(CardNum->text());
        addCarid->addCarid_is_Open = true;
        addCarid->show();
    }
}

void bathcar::addNewBathCard()
{
    if(!bathcard->BathCard_is_Open)
    {
        bathcard->BathCard_is_Open = true;
        bathcard->show();
    }
}

