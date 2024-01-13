#include "serialportserver.h"
#include "QMessageBox"
SerialportServer::SerialportServer(QObject *parent)
    : QObject{parent}
{
    qDebug() << "Available serial ports:";
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        qDebug() << "Port:" << info.portName()
                 << "Description:" << info.description()
                 << "Manufacturer:" << info.manufacturer()
                 << "System Location:" << info.systemLocation()
                 << "Vendor ID:" << info.vendorIdentifier()
                 << "Product ID:" << info.productIdentifier();
        coms<<info.portName()+":"+info.description();
    }
    qDebug()<<coms;
    QSerialPort *serialPort =new QSerialPort();
    serialPort->setPortName(usingCom);
    serialPort->setBaudRate(QSerialPort::Baud9600);
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setParity(QSerialPort::NoParity);
    serialPort->setStopBits(QSerialPort::OneStop);
    serialPort->setFlowControl(QSerialPort::NoFlowControl);
    serialPort->setReadBufferSize(40);

//    textEdit = new QPlainTextEdit();
//    textEdit->show();
//    textEdit->setReadOnly(true);




    // 连接串口的readyRead信号到槽函数
    if (serialPort->open(QIODevice::ReadOnly)) {
        qDebug() << "Serial port opened successfully.";

    } else {
        qDebug() << "Failed to open serial port:" << serialPort->errorString();
        QMessageBox::warning(nullptr,"错误","蓝牙连接失败");
    }

    connect(serialPort,&QSerialPort::readyRead,this,[=](){
//        qDebug()<<serialPort->readAll();
//        textEdit->insertPlainText(serialPort->readAll());
//        int lineCount=textEdit->document()->blockCount();
//        if(lineCount>2){
//           qDebug()<<lineCount;
//        QTextCursor *cursor=new QTextCursor(textEdit->document());
//        cursor->movePosition(QTextCursor::Start);

//        // 移动到第一个块的末尾
//        cursor->movePosition(QTextCursor::Down,QTextCursor::KeepAnchor);
        sendMsgTochart(serialPort->readAll());
//        cursor->removeSelectedText();
        // 删除选中的文本


    });



//    textEdit->setVisible(false);





}

void SerialportServer::sendMsgTochart(QString data)
{

    QStringList lines = data.split(" ");
    if(lines.size()>=2)
    {
    QString tempStr = lines.at(0);
    QString humiStr = lines.at(1);
    humiStr=humiStr.left(6);
    qDebug()<<tempStr<<humiStr;
    this->chart1->appendPoint(tempStr.left(4).toFloat());
    this->chart2->appendPoint(humiStr.left(4).toFloat());
    }


}

void SerialportServer::setChartsP(ChartWidget *chart1, ChartWidget *chart2)
{
    this->chart1=chart1;
    this->chart2=chart2;
}
