#include "connect.h"

Connect::Connect()
{
    QString HostName = "172.18.164.43";
    QString DBName = "carmanagement";
    QString DBuser = "zmb";
    QString DBpwd = "abc";

    DB = QSqlDatabase::addDatabase("QMYSQL");
    DB.setHostName(HostName);
    DB.setDatabaseName(DBName);
    DB.setPort(3306);
    DB.setUserName(DBuser);
    DB.setPassword(DBpwd);
}

/*获取数据库连接变量*/
QSqlDatabase Connect::getDB(){
    return DB;
}
Connect::~Connect()
{
    QString name;
        {
            name = "qt_sql_default_connection";
        } //超出作用域，隐含对象QSqlDatabase::database()被删除。
    QSqlDatabase::removeDatabase(name);

}
