#ifndef CONNECT_H
#define CONNECT_H
#include <qsqldatabase.h>

class Connect
{
public:
    Connect();
    ~Connect();
public slots:
    QSqlDatabase getDB();
private:
    QSqlDatabase DB;
};

#endif // CONNECT_H
