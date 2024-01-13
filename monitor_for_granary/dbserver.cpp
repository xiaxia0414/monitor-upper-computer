#include "dbserver.h"
#include <QDateTime>
DBServer::DBServer(QObject *parent)
    : QObject{parent}
{
     DB = QSqlDatabase::addDatabase("QSQLITE");
    DB.setDatabaseName("./monitorDB.db");//打开数据库
     if (DB.open())
     {
         qDebug() << "Database opened successfully！";
     }
     else
     {
         qDebug() << "无法打开数据库：" << DB.lastError().text();
     }

     QSqlQuery query("select * from 温度");
     while (query.next()) {
         QString str = query.value("时间").toString();
    qDebug()<<str;

     }


}

void DBServer::addTempData(QDateTime time, double temp)
{
   QString queryString = QString("insert into 温度(时间,峰值) values('%1','%2') ")
                               .arg(time.toString()).arg(temp);
      QSqlQuery query;
    if(query.exec(queryString)){
    qDebug()<<"insert data Successful!";
     }
     else {
    qDebug()<<"insert data Failed!";
     }

}

void DBServer::addHumiData(QDateTime time, double humi)
{
     QString queryString = QString("insert into 湿度(时间,峰值) values('%1','%2') ")
                               .arg(time.toString()).arg(humi);
     QSqlQuery query;
     if(query.exec(queryString)){
    qDebug()<<"insert data Successful!";
     }
     else {
    qDebug()<<"insert data Failed!";
     }
}
