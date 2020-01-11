#include "logindialog.h"
#include "ui_logindialog.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QDebug>
LoginDialog::LoginDialog(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("登录");
    QIcon icon6(":/image/CarManage.ico");
    setWindowIcon(icon6);
    setFixedSize(this->width(), this->height());//固定窗口大小

    QPalette palette;
    palette.setBrush(QPalette::Background, QBrush(QPixmap(":/image/back.jpg")));
    setPalette(palette);

    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::white);
    ui->label->setPalette(pa);
    ui->label_2->setPalette(pa);

    connect(ui->ButtonConfirm, SIGNAL(clicked()), this, SLOT(confrimLogin()));
    connect(ui->ButtonCancel, SIGNAL(clicked()), this, SLOT(cancelLogin()));    
    connect(ui->editPwd, SIGNAL(returnPressed()), this, SLOT(confrimLogin()));
    connect(ui->editName, SIGNAL(returnPressed()), this, SLOT(confrimLogin()));


    conn = new Connect();
}


void LoginDialog::cancelLogin()
{
    QApplication* app;
    app->quit();
}

void LoginDialog::confrimLogin()
{
    if(ui->editName->text() == "")
    {
        QMessageBox::information(this, tr("提示"),tr("请输入用户名。"),QMessageBox::Ok, QMessageBox::Ok);
        return;
    }
    if(ui->editPwd->text() == "")
    {
        QMessageBox::information(this, tr("提示"),tr("请输入密码。"),QMessageBox::Ok, QMessageBox::Ok);
        return;
    }
    QString name = ui->editName->text().trimmed();
    QString password = ui->editPwd->text();
    QSqlQuery *query = new QSqlQuery;
    conn->getDB().open();
    QString query2("select mypwd,mylimit from admin where userid ='" + name + "';");
    query->prepare(query2);
    bool a = false;
    QString limit;
    QString pwd;
    if(query->exec()){
        if(query->next()){
            pwd = query->value(0).toString();
            limit = query->value(1).toString();
            a = true;
        }
    }
    if(!a){
        QMessageBox::information(this, tr("提示"),tr("用户不存在。"),QMessageBox::Ok, QMessageBox::Ok);
        conn->getDB().close();
        return;
    }
    conn->getDB().close();

    if(password != pwd)
    {
        QMessageBox::information(this, tr("提示"),tr("账号或密码错误"),QMessageBox::Ok, QMessageBox::Ok);
        return;
    }

    MainWindow *mainwindow = new MainWindow(conn,limit,name);
    this->close();
    mainwindow->show();
}


LoginDialog::~LoginDialog()
{
    delete ui;
}
