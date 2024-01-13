#include "monitorwidget.h"
#include "monitorwindow.h"
#include <QApplication>
#include <QFont>
#include "serialportserver.h"
#include "QDir"
#include "dbserver.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setFont(QFont("微软雅黑"));
    a.setWindowIcon(QIcon(":/images/icons8-imac-90.png"));
    qDebug()<<QDir::currentPath();
    DBServer dbs;

    QFile styleFile(":/qss/flatwhite.qss");  // 使用资源文件方式加载QSS
    styleFile.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(styleFile.readAll());   // 应用QSS样式
    qApp->setStyleSheet(styleSheet);

    monitorWidget w;
    w.show();
    w.setWindowTitle("智能粮仓监测系统");

    SerialportServer serial;
    serial.setChartsP(w.w->chart,w.w->chart2);
    w.stw->setSerialPort(&serial);


    w.w->chart->addDBserver1(&dbs);
    w.w->chart2->addDBserver2(&dbs);
    w.dataView->setDatabase(dbs.DB);



//    MonitorWindow m;
//    m.show();
    return a.exec();
}
