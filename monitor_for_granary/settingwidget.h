#ifndef SETTINGWIDGET_H
#define SETTINGWIDGET_H

#include <QWidget>
#include "monitorwindow.h"
#include "serialportserver.h"
#include "tabledataview.h"
namespace Ui {
class settingWidget;
}

class settingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit settingWidget(ChartWidget *chart1,ChartWidget *chart2,QWidget *parent = nullptr);
    ~settingWidget();
    void setSerialPort(SerialportServer *serialport);

private slots:
    void on_doubleSpinBox_valueChanged(double arg1);

    void on_doubleSpinBox_2_valueChanged(double arg1);

    void on_doubleSpinBox_3_valueChanged(double arg1);

    void on_doubleSpinBox_4_valueChanged(double arg1);

    void on_horizontalSlider_valueChanged(int value);

    void on_horizontalSlider_2_valueChanged(int value);

    void on_horizontalSlider_3_valueChanged(int value);

    void on_horizontalSlider_4_valueChanged(int value);

    void on_doubleSpinBox_5_valueChanged(double arg1);

    void on_doubleSpinBox_6_textChanged(const QString &arg1);

    void on_doubleSpinBox_7_textChanged(const QString &arg1);

    void on_doubleSpinBox_8_valueChanged(double arg1);

    void on_doubleSpinBox_6_valueChanged(double arg1);

    void on_doubleSpinBox_7_valueChanged(double arg1);



private:
    Ui::settingWidget *ui;
    ChartWidget *chart1;
    ChartWidget *chart2;
    SerialportServer *serialport;


};

#endif // SETTINGWIDGET_H
