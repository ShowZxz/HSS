#ifndef DATABASE_H
#define DATABASE_H

#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlDriver>
#include <qdebug.h>
#include <qsqlerror.h>


struct LoginUser{
    QString pseudo;
    QString code;
};
struct ScoreInfoTop{
    QString username;
    long long score;
};
class Database
{
private:
    QSqlDatabase db;
public:
    Database();
    ~Database();

    bool openDatabase();
    void closeDatabase();

    QList<LoginUser> getLoginUser( const QString &pseudo, const QString &code);

    QString getHighscoreFromDatabase(QString username,QString title);
    QString getRankFromDatabase(const QString &user, const QString &title);
    QString getInfoRank(const QString &user, const QString &title);

    QList<ScoreInfoTop> getTopScoresInFrontUser(const QString &title, const QString &user);
    QList<ScoreInfoTop> getTopScoresBehindUser(const QString &title, const QString &user);

    QList<ScoreInfoTop> getWorldHighscore(const QString &title);

};


#endif // DATABASE_H
