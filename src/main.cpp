#include "logindialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LoginDialog login; //登陆界面
    login.show();

    return a.exec();

}
