#ifndef MONITORWINDOW_H
#define MONITORWINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QtCharts/QtCharts>
#include "dbserver.h"
#include "QJsonObject"
#include <QtMultimedia/QMediaPlayer>
class ChartWidget;
class MonitorWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MonitorWindow(QWidget *parent = nullptr);
    ~MonitorWindow();
    ChartWidget *chart;
    ChartWidget *chart2;

    QJsonObject jschart1;
    QJsonObject jschart2;
    QJsonObject jsonObject;
    QJsonDocument jsonDocument;
private:
    QVBoxLayout *vlayout1;


signals:

};

class ChartWidget : public QWidget
{
     Q_OBJECT
public:
    explicit ChartWidget(QWidget *parent = nullptr);
    QString normalStr="xx正常";
    QString warningStr="xx正常";
    QString errorStr="xx异常";
    QString nowStr="当前XX:";
    QString format="℃";
    float remindValue;
    float warningValue;
    float max;
    float min;

    QDateTimeAxis *xAxis;
    QValueAxis *yAxis;



private:
    QHBoxLayout *hlayout1;
    QLabel *warningLable;
    QLabel *warningText;
    QLabel *information;

    QChart* chart;
    QLineSeries *series;
    QLineSeries *remindSeries;
    QLineSeries *warningSeries;


    QDateTime pretime;
    QDateTime pretimeEnd;



    bool isFristTime=true;

    float maxInMin=0;
    QTimer *timer;

    QMediaPlayer *player;
    QString soundPath;
    bool isplaying=false;

public slots:
    void setWarning();
    void setError();
    void setNormal();
    void appendPoint(float value);

    void  setChartTittle(QString tittle);
    void  setYRange(float bottom,float top);
    void  setLineColor(QColor color);
    void addDBserver1(DBServer *dbs);
    void addDBserver2(DBServer *dbs);

    void setSoundPath(QString soundPath);

    void playSound();
signals:
    void warningState();

};

#endif // MONITORWINDOW_H
