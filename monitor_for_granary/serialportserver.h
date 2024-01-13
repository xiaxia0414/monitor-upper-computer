#ifndef SERIALPORTSERVER_H
#define SERIALPORTSERVER_H

#include <QObject>
#include <QtSerialPort/QtSerialPort>
#include <QPlainTextEdit>
#include "monitorwindow.h"
class SerialportServer : public QObject
{
    Q_OBJECT
public:
    explicit SerialportServer(QObject *parent = nullptr);
      QString total="";
    QPlainTextEdit *textEdit;
public slots:
    void sendMsgTochart(QString data);
    void setChartsP(ChartWidget *chart1,ChartWidget *chart2);
signals:

private:
    ChartWidget *chart1=nullptr;
    ChartWidget *chart2=nullptr;
public:
    QStringList coms;
    QString usingCom="COM3";


};

#endif // SERIALPORTSERVER_H
