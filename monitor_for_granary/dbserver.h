#ifndef DBSERVER_H
#define DBSERVER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>

class DBServer : public QObject
{
    Q_OBJECT
public:
    explicit DBServer(QObject *parent = nullptr);

signals:
private:

public:
    QSqlDatabase DB;
    void addTempData(QDateTime time,double temp);
    void addHumiData(QDateTime time,double humi);

};

#endif // DBSERVER_H
