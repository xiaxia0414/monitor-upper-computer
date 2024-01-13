#ifndef MONITORWIDGET_H
#define MONITORWIDGET_H

#include <QWidget>
#include <QLayout>
#include <QPushButton>
#include <QFrame>
#include <QButtonGroup>
#include <QStackedLayout>
#include "monitorwindow.h"
#include "settingwidget.h"
#include "tabledataview.h"
class HoverBtn;
class monitorWidget : public QWidget
{
    Q_OBJECT

public:
    monitorWidget(QWidget *parent = nullptr);
    ~monitorWidget();
    MonitorWindow *w;
    settingWidget *stw;
    TableDataView *dataView;
    QSqlDatabase *datab;
private:
    QHBoxLayout *hlayout1;

};

class TabWidget : public QFrame
{
    Q_OBJECT

public:
    TabWidget(QWidget *parent = nullptr);
    ~TabWidget();
private:
    QVBoxLayout *vlayout1;
public:
    HoverBtn *monitorBtn;
    HoverBtn *settingBtn;
    HoverBtn *tableBtn;

};
class HoverBtn : public QPushButton
{
    Q_OBJECT
public:
    HoverBtn(QString icon=0,QString iconHover=0,QString iconChecked=0,QString text=0,QWidget *parent = nullptr);
public slots:
    void changeColor(bool isCheck);
private:
    QString icon;
    QString iconHover;
    QString iconChecked;



    // QWidget interface
protected:
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
};




class StackWidget : public QFrame
{
    Q_OBJECT

public:
    StackWidget(QWidget *parent = nullptr);
    QStackedLayout *stackedLayout;
};
#endif // MONITORWIDGET_H
