#include "monitorwidget.h"
#include "QLabel"
monitorWidget::monitorWidget(QWidget *parent)
    : QWidget(parent)
{
    this->resize(1280,720);
    hlayout1= new QHBoxLayout(this);
    hlayout1 ->setContentsMargins(0,0,0,0);
    hlayout1->setMargin(0);
    hlayout1->setSpacing(0);
    TabWidget *tabwidget= new TabWidget(this);
    hlayout1->addWidget(tabwidget);
    StackWidget *stack = new StackWidget(this);
    hlayout1->addWidget(stack);
//    QLabel *lab1 = new QLabel(this);
//    lab1->setText("监测页面");

    w =new MonitorWindow(this);
//    QLabel *lab2 = new QLabel(this);
//    lab2->setText("设置页面");
    stw = new settingWidget(w->chart,w->chart2,this);
    dataView = new TableDataView(this);
    dataView->warningT=w->chart->warningValue;
    dataView->warningH = w->chart2->warningValue;

    stack->stackedLayout->addWidget(w);
    stack->stackedLayout->addWidget(stw);
    stack->stackedLayout->addWidget(dataView);

    connect(tabwidget->monitorBtn,&QPushButton::clicked,this,[=](){
        stack->stackedLayout->setCurrentIndex(0);
    });
    connect(tabwidget->settingBtn,&QPushButton::clicked,this,[=](){
        stack->stackedLayout->setCurrentIndex(1);
    });
    connect(tabwidget->tableBtn,&QPushButton::clicked,this,[=](){
        stack->stackedLayout->setCurrentIndex(2);

    });




    this->setObjectName("monitorWidget");
    this->setStyleSheet("#monitorWidget{background-color:rgb(235,233,233);}");
      stack->stackedLayout->setCurrentIndex(0);
      tabwidget->monitorBtn->setChecked(true);

}

monitorWidget::~monitorWidget()
{

}


TabWidget::TabWidget(QWidget *parent) : QFrame (parent)
{
    this->setFixedWidth(120);

    vlayout1 = new QVBoxLayout(this);
    vlayout1 ->setContentsMargins(0,0,0,0);
    vlayout1->setMargin(0);
    vlayout1->setSpacing(0);

    monitorBtn = new HoverBtn(":/images/icons8-imac-90.png",
                              ":/images/icons8-imac-90(2).png",
                              ":/images/icons8-imac-90(1).png",
                              "粮仓监测",this);
    settingBtn =new HoverBtn(":/images/icons8-setting-96.png",
                          ":/images/icons8-setting-96(2).png",
                          ":/images/icons8-setting-96(1).png",
                          "粮仓设置",this);
    tableBtn = new HoverBtn(":/images/icons8-spreadsheet-96.png",
                            ":/images/icons8-spreadsheet-96(2).png",
                            ":/images/icons8-spreadsheet-96(1).png",
                            "历史数据",this);



    QButtonGroup *btnGroup =new QButtonGroup(this);
    btnGroup->addButton(monitorBtn);
    btnGroup->addButton(settingBtn);
    btnGroup->addButton(tableBtn);
    btnGroup->setExclusive(true);



    vlayout1->addWidget(monitorBtn);
    vlayout1->addWidget(settingBtn);
    vlayout1->addWidget(tableBtn);
    vlayout1->addStretch();
    this->setStyleSheet("TabWidget{background-color:rgb(235,233,233);}");


}

TabWidget::~TabWidget()
{

}

StackWidget::StackWidget(QWidget *parent): QFrame (parent)
{
    this->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::Expanding);
    this->setStyleSheet("StackWidget{background-color:rgb(245, 245, 245);"
                        "border-radius:10px;}");
    stackedLayout= new QStackedLayout(this);
    stackedLayout->setContentsMargins(0,0,0,0);
}



HoverBtn::HoverBtn(QString icon, QString iconHover, QString iconChecked,QString text, QWidget *parent) :QPushButton(parent)
{
    this->icon=icon;
    this->iconHover=iconHover;
    this->iconChecked = iconChecked;
    this->setAttribute(Qt::WA_Hover);

    this->setCheckable(true);
    this->setFixedHeight(50);
    this->setStyleSheet("QPushButton{background-color:rgb(235, 233, 233);"
                              "border:none;"
                        "color:rgb(121, 121, 121);"
                        "font:17px;}"
                        "QPushButton:hover{background-color:rgb(200,200,200);color:rgb(0, 141, 235);}"
                        "QPushButton:checked{background-color:rgb(0, 141, 235);color:rgb(255,255,255);"
                        ""
                        "}");
    this->setIcon(QIcon(icon));
    this->setIconSize(QSize(30,30));
    this->setText(text);

    connect(this,SIGNAL(toggled(bool)),this,SLOT(changeColor(bool)));


}

void HoverBtn::changeColor(bool isCheck)
{
    if(isCheck)
    {
        this->setIcon(QIcon(iconChecked));
    }
    else
    {
        this->setIcon(QIcon(icon));
    }
}
void HoverBtn::enterEvent(QEvent *event)
{
    if(!this->isChecked())
    {
    this->setIcon(QIcon(iconHover));
    }
}

void HoverBtn::leaveEvent(QEvent *event)
{
    if(!this->isChecked()){
        this->setIcon(QIcon(icon));}
}

