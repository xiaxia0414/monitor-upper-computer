#include "monitorwindow.h"
#include "QTimer"
#include <QRandomGenerator>
#include <QDebug>
#include <QtMath>
#include <math.h>
MonitorWindow::MonitorWindow(QWidget *parent)
    : QWidget{parent}
{
    QFile file(QDir::currentPath()+"/confi.json");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open JSON file.";
    }

    // 读取文件内容
    QString jsonString = file.readAll();
    file.close();



    // 解析JSON字符串
     jsonDocument = QJsonDocument::fromJson(jsonString.toUtf8());

    // 获取JSON对象
     jsonObject = jsonDocument.object();

    // 从JSON对象中获取值
     jschart1 = jsonObject["chart1"].toObject();
     jschart2 = jsonObject["chart2"].toObject();

    chart = new ChartWidget(this);
    chart2 = new ChartWidget(this);
    chart->max=jschart1["max"].toDouble();
    chart->min=jschart1["min"].toDouble();
    chart->remindValue=jschart1["remindValue"].toDouble();
    chart->warningValue=jschart1["waringValue"].toDouble();

    chart2->max=jschart2["max"].toDouble();
    chart2->min=jschart2["min"].toDouble();
    chart2->remindValue=jschart2["remindValue"].toDouble();
    chart2->warningValue=jschart2["waringValue"].toDouble();






    this->resize(800,400);
    vlayout1 = new QVBoxLayout(this);

    chart->setChartTittle("粮仓温度");
    chart->setYRange(chart->min,chart->max);
    chart->nowStr="当前温度";
    chart->format="℃";
    chart->normalStr="温度正常";
    chart->warningStr="温度正常";
    chart->errorStr="温度异常";
    chart->setLineColor(QColor(0,204,0));
    chart->setSoundPath(QDir::currentPath()+"/sound/temp_warnning.mp3");



    chart2->setChartTittle("粮仓湿度");
    chart2->setYRange(chart2->min,chart2->max);
    chart2->nowStr="当前湿度";
    chart2->format="%";
    chart2->normalStr="湿度正常";
    chart2->warningStr="湿度正常";
    chart2->errorStr="湿度异常";
    chart2->setLineColor(QColor(0,0,204));
     chart2->setSoundPath(QDir::currentPath()+"/sound/humi_warnning.mp3");

    vlayout1->addWidget(chart);
    vlayout1->addWidget(chart2);
    vlayout1->setSpacing(0);



}
MonitorWindow::~MonitorWindow()
{
    jschart1["max"]=chart->max;
    jschart1["min"]=chart->min;
    jschart1["remindValue"]=chart->remindValue;
    jschart1["waringValue"]=chart->warningValue;

    jschart2["max"]=chart2->max;
    jschart2["min"]=chart2->min;
    jschart2["remindValue"]=chart2->remindValue;
    jschart2["waringValue"]=chart2->warningValue;

    jsonObject["chart1"]=jschart1;
    jsonObject["chart2"]=jschart2;

    jsonDocument.setObject(jsonObject);
    qDebug()<<jsonDocument;

    QFile *file2 = new QFile(QDir::currentPath()+"/confi.json");
    if (!file2->open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug() << "Failed to open JSON file for writing.";
    }

    // 写入JSON数据到文件
    QTextStream out(file2);
    out << jsonDocument.toJson(QJsonDocument::Indented);

    // 关闭文件
    file2->close();

}

ChartWidget::ChartWidget(QWidget *parent):QWidget{parent}
{
     chart = new QChart();


    // 构建折线系列对象
    series = new QLineSeries();
    remindSeries=new QLineSeries();
    warningSeries=new QLineSeries();
    QPen pen(QColor(255, 100, 100));
    pen.setWidth(2);
    warningSeries->setPen(pen);

    QPen pen2(QColor(255, 204, 153));
    pen2.setWidth(2);
    remindSeries->setPen(pen2);



    // 将系列添加到图表
     chart->addSeries(series);
    chart->addSeries(remindSeries);
    chart->addSeries(warningSeries);




    xAxis = new QDateTimeAxis;

    xAxis->setFormat("hh:mm:ss");

    chart->addAxis(xAxis, Qt::AlignBottom);
    series->attachAxis(xAxis);

    // 创建自定义纵坐标
    yAxis = new QValueAxis;
    //yAxis->setLabelFormat("%");
    yAxis->setRange(0, 10); // 设置纵坐标范围
    yAxis->setTickCount(6);

    chart->addAxis(yAxis, Qt::AlignLeft);
    series->attachAxis(yAxis);
    remindSeries->attachAxis(xAxis);
    remindSeries->attachAxis(yAxis);
    warningSeries->attachAxis(xAxis);
    warningSeries->attachAxis(yAxis);







    // 将图表绑定到视图
    QChartView *view= new QChartView(this);
    view->setChart(chart);
    chart->legend()->setVisible(false);
    chart->axisX()->setGridLineVisible(false);
    chart->axisY()->setGridLineVisible(false);
    chart->setContentsMargins(0,0,0,0);




    hlayout1 = new QHBoxLayout(this);
    hlayout1->addWidget(view);
    view->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::Expanding);
    hlayout1->setContentsMargins(0,0,0,0);
    QVBoxLayout *vlayout1=new QVBoxLayout();
    vlayout1->setContentsMargins(0,20,0,20);
    warningLable = new QLabel(this);
    warningLable->setAlignment(Qt::AlignCenter);
    warningLable->setPixmap(QPixmap(":/images/normal.png"));
//    warningLable->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);
    warningText = new QLabel(this);
//    warningLable->setScaledContents(true);

    warningText->setText(normalStr);
    warningText->setAlignment(Qt::AlignCenter);
    warningText->setFont(QFont("黑体",20));
    warningText->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    warningText->setMaximumWidth(160);
    warningText->setStyleSheet("color:rgb(41, 204, 64)");

    information = new QLabel(this);
    information->setText("当前XX:XX");
    information->setFont(QFont("黑体",13));
    information->setFixedWidth(180);
    information->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    information->setScaledContents(true);
    information->setStyleSheet("color:rgb(41, 204, 64)");

    vlayout1->addWidget(information);
    vlayout1->addWidget(warningLable);
    vlayout1->addWidget(warningText);

    hlayout1->addLayout(vlayout1);

    view->setRenderHint(QPainter::Antialiasing);
    chart->setDropShadowEnabled(true);
    chart->setTitle("粮仓XX");

    this->setStyleSheet("");
    connect(this,&ChartWidget::warningState,this,&ChartWidget::playSound);







    qDebug()<<2;
}

void ChartWidget::setWarning()
{
    warningLable->setPixmap(QPixmap(":/images/warning.png"));
    warningText->setStyleSheet("color:rgb(255, 159, 1);");
    information->setStyleSheet("color:rgb(255, 159, 1)");
    warningText->setText(warningStr);
}

void ChartWidget::setError()
{
    warningLable->setPixmap(QPixmap(":/images/errow.png"));
    warningText->setStyleSheet("color:rgb(240, 61, 71);");
    information->setStyleSheet("color:rgb(240, 61, 71)");
    warningText->setText(errorStr);
}

void ChartWidget::setNormal()
{
    warningLable->setPixmap(QPixmap(":/images/normal.png"));
    warningText->setStyleSheet("color:rgb(41, 204, 64);");
    information->setStyleSheet("color:rgb(41, 204, 64)");
    warningText->setText(normalStr);
}

void ChartWidget::appendPoint(float value)
{
    if(this->isFristTime)
    {
        pretime=QDateTime::currentDateTime();
        pretimeEnd=QDateTime::currentDateTime().addSecs(60);
        xAxis->setRange(pretime,pretimeEnd);
        this->isFristTime=false;

    }

    information->setText(nowStr+QString::number(value)+format);
    if(value>warningValue){setError();
           emit warningState();
    }
    else if(value<=warningValue&&value>remindValue)setWarning();
    else setNormal();

    series->append(QDateTime::currentDateTime().toMSecsSinceEpoch(),value);
    warningSeries->clear();
    warningSeries->append(xAxis->min().toMSecsSinceEpoch(),warningValue);
    warningSeries->append(xAxis->max().toMSecsSinceEpoch(),warningValue);
    remindSeries->clear();
    remindSeries->append(xAxis->min().toMSecsSinceEpoch(),remindValue);
    remindSeries->append(xAxis->max().toMSecsSinceEpoch(),remindValue);




    // 限制数据点数量，可以根据需要调整
    if (QDateTime::currentDateTime()>pretimeEnd) {
        if(QDateTime::currentDateTime()>pretimeEnd.addSecs(20)){
            series->removePoints(0, 1);}
        xAxis->setRange(QDateTime::currentDateTime().addSecs(-60),QDateTime::currentDateTime());
    }

    maxInMin=fmax(maxInMin,value);



}

void ChartWidget::setChartTittle(QString tittle)
{
    this->chart->setTitle(tittle);
}

void ChartWidget::setYRange(float bottom, float top)
{
    this->chart->axisY()->setRange(bottom,top);
}

void ChartWidget::setLineColor(QColor color)
{
    QPen pen(color);
    pen.setWidth(3);
    series->setPen(pen);
}

void ChartWidget::addDBserver1(DBServer *dbs)
{
    timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,[=](){
        dbs->addTempData(QDateTime::currentDateTime(),maxInMin);
        maxInMin=0;
    });
    timer->start(1000*60);
}

void ChartWidget::addDBserver2(DBServer *dbs)
{
    timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,[=](){
        dbs->addHumiData(QDateTime::currentDateTime(),maxInMin);
        maxInMin=0;
    });
    timer->start(1000*60);
}

void ChartWidget::setSoundPath(QString soundPath)
{
    this->soundPath=soundPath;
    QUrl audioUrl(soundPath);
    player=new QMediaPlayer(this);
    player->setMedia(audioUrl);
    connect(player,&QMediaPlayer::stateChanged,[&](QMediaPlayer::State state){
        if(state == QMediaPlayer::StoppedState) {
            // 媒体播放已经结束
            qDebug() << "播放结束";
            isplaying=false;
        }
    });
}

void ChartWidget::playSound()
{
    if(this->isplaying==false)
    {
        player->play();
    }
}
