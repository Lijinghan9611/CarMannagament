#include "mainwindow.h"
#include "fix.h"
#include "bathcar.h"
#include "usermanagement.h"
#include "insurance.h"
#include "client.h"
#include "concerning.h"
#include "connect.cpp"
#include <QHBoxLayout>
#include <QStatusBar>
#include <QDateTime>
#include <QMessageBox>
MainWindow::MainWindow(Connect *c, QString Limit, QString username, QWidget *parent)
    : QMainWindow(parent)
{
    tabWidget = new QTabWidget();
    conn = c;

    //向QTabWidget中添加第一个页面
    QIcon icon1(":/image/Car_Repair_16px.ico");
    QIcon icon2(":/image/customer.ico");
    QIcon icon3(":/image/insurance.ico");
    QIcon icon4(":/image/manage.ico");
    QIcon icon5(":/image/xiche.ico");
    QIcon icon6(":/image/CarManage.ico");
    QIcon icon7(":/image/about.ico");
    setWindowIcon(icon6);
    //添加切换面板
    tabWidget->addTab(new Fix(conn, this),icon1, "维修美容");
    tabWidget->addTab(new Insurance(conn, this), icon3,"车险信息");
    tabWidget->addTab(new bathcar(conn, this), icon5,"洗车");
    tabWidget->addTab(new Client(conn, this),icon2, "客户信息");

    QString s1;
    if(Limit == "admin"){
        tabWidget->addTab(new UserManagement(conn, username, this),icon4, "用户管理");
        s1 = "登录类型:管理员";
    }
    else{
        s1 = "登录类型:普通用户";
    }
    tabWidget->addTab(new concerning(this),icon7, "帮助与关于");

    //状态栏
    QStatusBar * sBar = statusBar();//创建状态栏
    QString s = "登录用户:" + username;

    QLabel *labuser = new QLabel(s);
    QLabel *labtype = new QLabel(s1);
    QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
    QString str = time.toString("yyyy-MM-dd hh:mm:ss"); //设置显示格式
    QLabel *labtime = new QLabel("登录时间:"+ str);
    sBar->addPermanentWidget(labuser);//addPermanentWidget：从右往左添加
    sBar->addPermanentWidget(labtype);//addPermanentWidget：从右往左添加
    sBar->addPermanentWidget(labtime);//addPermanentWidget：从右往左添加

    this->setCentralWidget(tabWidget);
    this->resize(1280, 640);
    this->setWindowTitle("车辆信息管理系统");
}


void MainWindow::closeEvent(QCloseEvent *event)
{
    //TODO: 在退出窗口之前，实现希望做的操作
    //弹出警告提示框
    QMessageBox box(QMessageBox::Warning,"确认关闭？","请注意保存数据。");
    box.setStandardButtons (QMessageBox::Ok|QMessageBox::Cancel);
    box.setButtonText (QMessageBox::Ok,QString("确定关闭"));
    box.setButtonText (QMessageBox::Cancel,QString("取消"));
    switch(box.exec()){
        case QMessageBox::Ok:
            event->accept();
            break;
        case QMessageBox::Cancel:
            event->ignore();
            return;
        }
}

MainWindow::~MainWindow()
{

}
