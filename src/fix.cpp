#include "fix.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QGridLayout>
#include <QHeaderView>
#include <QSqlDatabase>
#include <QDebug>   //用于控制台输出
#include <QMessageBox>
#include <qsqlquery.h>
#include <QTableView>
#include <QSqlTableModel>
#include <QListView>
#include "newfixinfo.h"
NewFixInfo *dialog;
//Connect *Conn;
Fix::Fix(Connect *c, QWidget *parent) : QWidget(parent)
{
    conn = c;
    rowCount = 0;
    /*第一部分*/
    lab = new QLabel("车牌：");
    cbxSheng = new QComboBox();  //省份选择
    QStringList Items;
    Items<<"粤  "<<"琼"<<"湘"<<"桂"<<"渝"<<"冀"
        <<"云"<<"辽"<<"黑"<<"皖"<<"鲁"<<"津"
       <<"新"<<"苏"<<"浙"<<"鄂"<<"甘"<<"沪"
      <<"晋"<<"蒙"<<"陕"<<"吉"<<"贵"<<"京"
     <<"青"<<"藏"<<"川"<<"宁"<<"豫";
    cbxSheng->addItems(Items);
    cbxSheng->setStyleSheet("QComboBox { min-height: 15px; min-width: 25px;}"
                               "QComboBox QAbstractItemView::item{height:20px;}");
    cbxSheng->setView(new QListView());

    cbxZimu = new QComboBox();    //车辆省份字母
    QStringList Items1;
    Items1<<"A  "<<"B"<<"C"<<"D"<<"E"<<"F"
         <<"G"<<"H"<<"I"<<"J"<<"K"<<"L"
        <<"M"<<"N"<<"O"<<"P"<<"Q"<<"R"
       <<"S"<<"T"<<"U"<<"V"<<"W"<<"X"
      <<"Y"<<"Z";
    cbxZimu->addItems(Items1);
    cbxZimu->setStyleSheet("QComboBox { min-height: 15px; min-width: 25px;}"
                               "QComboBox QAbstractItemView::item{height:20px;}");
    cbxZimu->setView(new QListView());
    editCarNum = new QLineEdit();  //输入车牌信息
    btnSearch = new QPushButton("查询");  //查询
    btnSearchAll = new QPushButton("显示所有");  //查询所有
    btnAdd = new QPushButton("添加");  //添加
    //btnEdit = new QPushButton("修改");   //修改
    btnDelete = new QPushButton("删除");  //删除
    QHBoxLayout *Layout1 = new QHBoxLayout();

    Layout1->addWidget(lab);
    Layout1->addWidget(cbxSheng);
    Layout1->addWidget(cbxZimu);
    Layout1->addWidget(editCarNum);
    Layout1->addWidget(btnSearch);
    Layout1->addWidget(btnSearchAll);
    Layout1->addWidget(btnAdd);
    //Layout1->addWidget(btnEdit);
    Layout1->addWidget(btnDelete);
    Layout1->addStretch(10);
    QGroupBox *searchGroup = new QGroupBox();
    searchGroup->setLayout(Layout1);

    /*第二部分*/
    tableWidget = new QTableWidget(16,6);
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);  //设置表格等宽

    /*连接槽函数*/
    connect(btnSearch, SIGNAL(clicked()), this, SLOT(Search()));
    connect(btnSearchAll, SIGNAL(clicked()), this, SLOT(SearchAll()));
    connect(btnAdd, SIGNAL(clicked()), this, SLOT(showAddNewInfoDialog()));
    connect(tableWidget, SIGNAL(cellChanged(int,int)), this, SLOT(Edit(int,int)));
    connect(btnDelete, SIGNAL(clicked()), this, SLOT(Delete()));

    QRegExp rx1("[0-9A-Z]{5}");
    editCarNum->setValidator(new QRegExpValidator(rx1, editCarNum));

    /*设置表头*/
    QStringList header;
    header<<"记录ID"<<"车牌号码"<<"维修项目"<<"时间"<<"费用"<<"备注";   //表列名
    tableWidget->setHorizontalHeaderLabels(header);

    QGridLayout *Layout2 = new QGridLayout();
    Layout2->addWidget(tableWidget);
    QGroupBox *tableGroup = new QGroupBox();
    tableGroup->setLayout(Layout2);

    //添加到主布局
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(searchGroup);
    mainLayout->addWidget(tableGroup);
    mainLayout->setStretchFactor(searchGroup, 1);
    mainLayout->setStretchFactor(tableGroup, 13);
    this->setLayout(mainLayout);

    dialog = new NewFixInfo(conn, this);
}

/*查询*/
void Fix::Search()
{
    rowCount = tableWidget->rowCount();
        if(16 < rowCount)
            for(int i = rowCount; 16 <= i;i--)
                tableWidget->removeRow(i);
    rowCount = 0;
    tableWidget->clearContents();
    QString carNumber;
    if(editCarNum->text() != "")
    {
        carNumber = cbxSheng->currentText().trimmed() + cbxZimu->currentText().trimmed() + editCarNum->text();
    }
    else
    {
        //弹出警告提示框
        QMessageBox::warning(this, tr("警告"),tr("请输入车牌号码"),QMessageBox::Ok, QMessageBox::Ok);
        return;
    }

    conn->getDB().open();

    QString query1("select id,carid,items,firsttime,fee,remark from maintenance where carid ='" + carNumber + "';");
    QSqlQuery *query = new QSqlQuery;
    query->prepare(query1);
    bool a = false;
    int i = 0;
    if(query->exec()){
        while(query->next()){
            if(rowCount > 15)
            {
                int insertRowId = rowCount;
                tableWidget->insertRow(insertRowId);
            }
            for(int j = 0; j < 6; j++){
                QTableWidgetItem *item = new QTableWidgetItem(query->value(j).toString());
                                item->setTextAlignment(Qt::AlignCenter);  //居中
                                tableWidget->setItem( i, j, item);
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

void Fix::SearchAll()
{   
    rowCount = tableWidget->rowCount();
        if(16 < rowCount)
            for(int i = rowCount; 16 <= i;i--)
                tableWidget->removeRow(i);
    rowCount = 0;
    conn->getDB().open();
    tableWidget->clearContents();
    QString query1("select id,carid,items,firsttime,fee,remark from maintenance;");
    QSqlQuery *query = new QSqlQuery;
    query->prepare(query1);
    int i = 0;
    if(query->exec()){
        while(query->next()){
            if(rowCount > 15)
            {
                int insertRowId = rowCount;
                tableWidget->insertRow(insertRowId);
            }
            for(int j = 0; j < 6; j++){
                QTableWidgetItem *item = new QTableWidgetItem(query->value(j).toString());
                                item->setTextAlignment(Qt::AlignCenter);  //居中
                                tableWidget->setItem( i, j, item);
            }
            i++;
            rowCount++;
        }
    }
    else{
        QMessageBox::information(this, tr("提示"),tr("没有搜索到数据"),QMessageBox::Ok, QMessageBox::Ok);
    }
    conn->getDB().close();
}
void Fix::Edit(int a,int b)
{
    if(a+1 > rowCount)  //非法修改空格返回
        return;
    QString string,id,query1;
    string = tableWidget->item(a,b)->text();
    id = tableWidget->item(a,0)->text();
    if(b == 0){
        query1 = "update maintenance set id = '" +string + "' where id ='" + id + "';";
    }
    else if(b == 1){
        query1 = "update maintenance set carid = '" +string + "' where id ='" + id + "';";
    }
    else if(b == 2){
        query1 = "update maintenance set items = '" +string + "' where id ='" + id + "';";
    }
    else if(b == 3){
        query1 = "update maintenance set time = '" +string + "' where id ='" + id + "';";
    }
    else if(b == 4){
        query1 = "update maintenance set fee = '" +string + "' where id ='" + id + "';";
    }
    else if(b == 5){
        query1 = "update maintenance set remark = '" +string + "' where id ='" + id + "';";
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

void Fix::Delete()
{
    QString query = "";
    conn->getDB().open();
    QList<QTableWidgetItem*>items=tableWidget->selectedItems();  //获取选定的内容
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
        int row =tableWidget->row(items.at(i));//获取选中的行
        tableWidget->removeRow(row);
        query = "delete from maintenance where id = '"+name+"';";
        //执行语句
        QSqlQuery *exe = new QSqlQuery;
        exe->exec(query);
    }
    conn->getDB().close();
}

void Fix::showAddNewInfoDialog()
{
    if(!dialog->Dialog_is_Open)
    {
        dialog->Dialog_is_Open = true;
        dialog->show();
    }
}

