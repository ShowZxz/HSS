#ifndef DATABASE_H
#define DATABASE_H
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlDriver>
#include <qsqlerror.h>
#include <QDateTime>


class Database
{
public:
    Database();
    bool openDatabase();
    void closeDatabase();
    void recordDatabase(const QString &table, const QString &username, const long long &score);
    bool existGameDatabase(const QString &table);

private:
    QSqlDatabase db;
    QDateTime * now;
};

#endif // DATABASE_H
