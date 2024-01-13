#include "settingwidget.h"
#include "ui_settingwidget.h"

settingWidget::settingWidget(ChartWidget *chart1,ChartWidget *chart2,QWidget *parent) :
    QWidget(parent),chart1(chart1),chart2(chart2),
    ui(new Ui::settingWidget)
{

    ui->setupUi(this);

    ui->doubleSpinBox_5->setValue(this->chart1->yAxis->min());
     ui->doubleSpinBox_6->setValue(this->chart1->yAxis->max());
    ui->doubleSpinBox_7->setValue(this->chart2->yAxis->min());
    ui->doubleSpinBox_8->setValue(this->chart2->yAxis->max());

    ui->doubleSpinBox->setValue(this->chart1->warningValue);
    ui->doubleSpinBox_2->setValue(this->chart1->remindValue);
    ui->doubleSpinBox->setRange(this->chart1->yAxis->min(),this->chart1->yAxis->max());
    ui->doubleSpinBox_2->setRange(this->chart1->yAxis->min(),this->chart1->yAxis->max());
    qDebug()<<ui->doubleSpinBox->value();

    ui->doubleSpinBox_3->setValue(this->chart2->warningValue);
    ui->doubleSpinBox_4->setValue(this->chart2->remindValue);
    ui->doubleSpinBox_3->setRange(this->chart2->yAxis->min(),this->chart2->yAxis->max());
    ui->doubleSpinBox_4->setRange(this->chart2->yAxis->min(),this->chart2->yAxis->max());


    ui->horizontalSlider->setRange(ui->doubleSpinBox->minimum(),ui->doubleSpinBox->maximum());
    ui->horizontalSlider_2->setRange(ui->doubleSpinBox_2->minimum(),ui->doubleSpinBox_2->maximum());
    ui->horizontalSlider_3->setRange(ui->doubleSpinBox_3->minimum(),ui->doubleSpinBox_3->maximum());
    ui->horizontalSlider_4->setRange(ui->doubleSpinBox_4->minimum(),ui->doubleSpinBox_4->maximum());

    ui->horizontalSlider->setValue(ui->doubleSpinBox->value());
    ui->horizontalSlider_2->setValue(ui->doubleSpinBox_2->value());
    ui->horizontalSlider_3->setValue(ui->doubleSpinBox_3->value());
    ui->horizontalSlider_4->setValue(ui->doubleSpinBox_4->value());
}



settingWidget::~settingWidget()
{
    delete ui;
}

void settingWidget::setSerialPort(SerialportServer *serialport)
{
    this->serialport=serialport;
    ui->comboBox->addItems(serialport->coms);


}

void settingWidget::on_doubleSpinBox_valueChanged(double arg1)
{
    this->chart1->warningValue=arg1;
    ui->horizontalSlider->setValue(arg1);
     qDebug()<<"d";
}


void settingWidget::on_doubleSpinBox_2_valueChanged(double arg1)
{
    this->chart1->remindValue=arg1;
      ui->horizontalSlider_2->setValue(arg1);
}


void settingWidget::on_doubleSpinBox_3_valueChanged(double arg1)
{
    this->chart2->warningValue=arg1;
        ui->horizontalSlider_3->setValue(arg1);
}


void settingWidget::on_doubleSpinBox_4_valueChanged(double arg1)
{
    this->chart2->remindValue=arg1;
          ui->horizontalSlider_4->setValue(arg1);
}


void settingWidget::on_horizontalSlider_valueChanged(int value)
{
    ui->doubleSpinBox->setValue(value);
          qDebug()<<"s";
}


void settingWidget::on_horizontalSlider_2_valueChanged(int value)
{
     ui->doubleSpinBox_2->setValue(value);
}


void settingWidget::on_horizontalSlider_3_valueChanged(int value)
{
     ui->doubleSpinBox_3->setValue(value);
}


void settingWidget::on_horizontalSlider_4_valueChanged(int value)
{
     ui->doubleSpinBox_4->setValue(value);
}


void settingWidget::on_doubleSpinBox_5_valueChanged(double arg1)
{
    this->chart1->yAxis->setRange(arg1, this->chart1->yAxis->max());
     this->chart1->min=arg1;
     ui->horizontalSlider->setMinimum(arg1);
     ui->horizontalSlider_2->setMinimum(arg1);
     ui->doubleSpinBox->setMinimum(arg1);
     ui->doubleSpinBox_2->setMinimum(arg1);

}
void settingWidget::on_doubleSpinBox_6_valueChanged(double arg1)
{
     this->chart1->yAxis->setRange(this->chart1->yAxis->min(),arg1 );
     this->chart1->max=arg1;
    ui->doubleSpinBox->setMaximum(arg1);
     ui->doubleSpinBox_2->setMaximum(arg1);
    ui->horizontalSlider->setMaximum(arg1);
      ui->horizontalSlider_2->setMaximum(arg1);
}
void settingWidget::on_doubleSpinBox_7_valueChanged(double arg1)
{
     this->chart2->yAxis->setRange(arg1, this->chart2->yAxis->max());
      this->chart2->min=arg1;
     ui->doubleSpinBox_3->setMinimum(arg1);
     ui->doubleSpinBox_4->setMinimum(arg1);
     ui->horizontalSlider_3->setMinimum(arg1);
     ui->horizontalSlider_4->setMinimum(arg1);

}
void settingWidget::on_doubleSpinBox_8_valueChanged(double arg1)
{
    this->chart2->yAxis->setRange(this->chart2->yAxis->min(),arg1 );
     this->chart2->max=arg1;
     ui->doubleSpinBox_3->setMaximum(arg1);
     ui->doubleSpinBox_4->setMaximum(arg1);
     ui->horizontalSlider_3->setMaximum(arg1);
     ui->horizontalSlider_4->setMaximum(arg1);
}





void settingWidget::on_doubleSpinBox_6_textChanged(const QString &arg1)
{

}


void settingWidget::on_doubleSpinBox_7_textChanged(const QString &arg1)
{

}



