#include "usermanagement.h"
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QListView>
#include <QDebug>
#include <QSqlQuery>
#include <QTableWidgetItem>
UserManagement::UserManagement(Connect *c, QString uname, QWidget *parent) : QWidget(parent)
{
    conn = c;
    userName = uname;

    labName = new QLabel("姓名：");
    labPwd= new QLabel("密码：");
    editName = new QLineEdit;
    editPwd= new QLineEdit;
    cbxUserType = new QComboBox;
    addBtn = new QPushButton("添加");
    deleteBtn= new QPushButton("删除");

    QStringList Items;
    Items<<"管理员"<<"普通用户";
    cbxUserType->addItems(Items);
    cbxUserType->setStyleSheet("QComboBox { min-height: 15px; min-width: 25px;}"
                                     "QComboBox QAbstractItemView::item{height:20px;}");
    cbxUserType->setView(new QListView());

    QGroupBox *box2 = new QGroupBox();
    QHBoxLayout *Layout2 = new QHBoxLayout();

    Layout2->addWidget(labName);
    Layout2->addWidget(editName);
    Layout2->addWidget(labPwd);
    Layout2->addWidget(editPwd);
    Layout2->addWidget(cbxUserType);
    Layout2->addWidget(addBtn);
    Layout2->addWidget(deleteBtn);
    Layout2->addStretch(10);
    box2->setLayout(Layout2);

    /*连接槽函数*/
    connect(addBtn, SIGNAL(clicked()), this, SLOT(UserAdd()));
    connect(deleteBtn, SIGNAL(clicked()), this, SLOT(UserDelete()));

    //第二部分
    tableUser = new QTableWidget(15,3);
    tableUser->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);  //设置表格等宽

    connect(tableUser, SIGNAL(cellChanged(int,int)), this, SLOT(Edit(int,int)));

    //设置表头
    QStringList header;
    header<<"用户名"<<"用户密码"<<"用户类型";  //表列名
    tableUser->setHorizontalHeaderLabels(header);

    QGridLayout *Layout3 = new QGridLayout();
    Layout3->addWidget(tableUser);
    QGroupBox *box3 = new QGroupBox();
    box3->setLayout(Layout3);

    //添加到主布局
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(box2);
    mainLayout->addWidget(box3);
    mainLayout->setStretchFactor(box2, 1);
    mainLayout->setStretchFactor(box3, 13);
    this->setLayout(mainLayout);

    showAllUser();

}

void UserManagement::showAllUser()
{
    bool flag = false;  //判断是否查询到数据
    rowCount = tableUser->rowCount();
    if(16 < rowCount)
        for(int i = rowCount; 15 <= i;i--)
            tableUser->removeRow(i);
    rowCount = 0;

    conn->getDB().open();
    tableUser->clearContents();
    QString query1("select * from admin;");
    QSqlQuery *query = new QSqlQuery;
    query->prepare(query1);
    int i = 0;
    if(query->exec()){
        while(query->next()){
            if(rowCount > 14) //插入空行
            {
                int insertRowId = rowCount;
                tableUser->insertRow(insertRowId);
            }
            for(int j = 0; j < 3; j++){
                QTableWidgetItem *item = new QTableWidgetItem(query->value(j).toString());
                item->setTextAlignment(Qt::AlignCenter);  //居中
                tableUser->setItem( i, j, item);
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

void UserManagement::UserAdd()
{
    if(editName->text() == "")
    {
        //弹出警告提示框
        QMessageBox::warning(this, tr("提示"),tr("请输入用户名。"),QMessageBox::Ok, QMessageBox::Ok);
        return;
    }
    if(editName->text().length() > 20)
    {
        //弹出警告提示框
        QMessageBox::warning(this, tr("提示"),tr("用户名过长。"),QMessageBox::Ok, QMessageBox::Ok);
        return;
    }
    if(editPwd->text().length() > 20)
    {
        //弹出警告提示框
        QMessageBox::warning(this, tr("提示"),tr("密码过长。"),QMessageBox::Ok, QMessageBox::Ok);
        return;
    }
    if(editPwd->text() == "")
    {
        //弹出警告提示框
        QMessageBox::warning(this, tr("提示"),tr("请输入密码。"),QMessageBox::Ok, QMessageBox::Ok);
        return;
    }
    QString name = editName->text().trimmed();
    QString pwd = editPwd->text().trimmed();
    QString t = cbxUserType->currentText().trimmed();
    QSqlQuery *query = new QSqlQuery;

    conn->getDB().open();

    //判断是否存在该用户
    QString sql = "select * from admin where userid = '"+name+"';";
    query->prepare(sql);
    query->exec();
    if(query->next())
    {
        QMessageBox::information(this, tr("提示"),tr("已存在该用户。"),QMessageBox::Ok, QMessageBox::Ok);
        conn->getDB().close();
        return;
    }

    if(t == "管理员")
        t = "admin";
    else
        t = "普通";
    QString query1("insert into admin values('"+name+"','"+pwd+"','"+t+"')");
    query->prepare(query1);
    if(query->exec())
    {
       QMessageBox::information(this, tr("提示"),tr("添加成功。"),QMessageBox::Ok, QMessageBox::Ok);
    }
    else
    {
        QMessageBox::information(this, tr("提示"),tr("添加失败"),QMessageBox::Ok, QMessageBox::Ok);
    }
    conn->getDB().close();

    showAllUser();
}

void UserManagement::UserDelete()
{
    QString query = "";


    QList<QTableWidgetItem*>items=tableUser->selectedItems();  //获取选定的内容
    int count=items.count();  //获取选定的数目，每个单元格单独计数

    if(count == 0)  //没有选定内容
    {
        //弹出提示框
        QMessageBox::information(this, tr("提示"),tr("没有选定内容。"),QMessageBox::Ok, QMessageBox::Ok);
        return;
    }

    conn->getDB().open();
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

    for(int i=0;i<count;i+=3)  //只获取每行第一列
    {
        QTableWidgetItem*item=items.at(i);
        QString name = item->text();//获取内容
        if(userName == name)
        {
            //弹出提示框
            QMessageBox::information(this, tr("提示"),tr("所选择账号为登录账号，不能删除"),QMessageBox::Ok, QMessageBox::Ok);
            conn->getDB().close();
            return;
        }
        int row =tableUser->row(items.at(i));//获取选中的行
        tableUser->removeRow(row);
        tableUser->insertRow(row);
        query = "delete from admin where userid = '"+name+"'";
        //执行语句
        QSqlQuery *exe = new QSqlQuery;
        exe->exec(query);
    }
    conn->getDB().close();
    showAllUser();
}

void UserManagement::Edit(int row, int col)
{
    if(row+1 > rowCount)  //非法修改空格返回
        return;

    QString string,id,query1;
    string = tableUser->item(row,col)->text();
    id = tableUser->item(row,0)->text();
    if(col == 0){
        QMessageBox::information(this, tr("提示"),tr("用户名不可修改"),QMessageBox::Ok, QMessageBox::Ok);
        showAllUser(); // 更新表格
        return;
    }
    else if(col == 1){
        query1 = "update admin set mypwd = '" +string + "' where userid ='" + id + "';";
    }
    else if(col == 2){
        query1 = "update admin set mylimit = '" +string + "' where userid ='" + id + "';";
    }

    qDebug()<<query1;
    conn->getDB().open();
    QSqlQuery *query = new QSqlQuery;
    query->prepare(query1);
    if(query->exec(query1)){
        QMessageBox::information(this, tr("提示"),tr("修改成功！"),QMessageBox::Ok, QMessageBox::Ok);
    }else{
        QMessageBox::information(this, tr("提示"),tr("修改失败！"),QMessageBox::Ok, QMessageBox::Ok);
    }
    conn->getDB().close();

    showAllUser();
}
