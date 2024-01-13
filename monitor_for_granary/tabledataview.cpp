#include "tabledataview.h"
#include "QLayout"
#include "QGroupBox"
#include "QHeaderView"
#include "QSizePolicy"
#include "QSqlQueryModel"
#include "QSqlQuery"
TableDataView::TableDataView(QWidget *parent)
    : QWidget{parent}
{

}

void TableDataView::setDatabase(QSqlDatabase &db)
{
    m_model = new QSqlTableModel(this,db);
    m_model->setTable("温度");
    m_model->setSort(m_model->fieldIndex("时间"),Qt::AscendingOrder);
    m_model->select();


    m_tableview = new QTableView(this);

    QHBoxLayout *hlayout = new QHBoxLayout();
    hlayout->addWidget(m_tableview);

    m_tableview->setModel(m_model);
    m_tableview->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_tableview->setAlternatingRowColors(true);
    m_tableview->setColumnWidth(0,350);
    RedBackgroundDelegate *delegate1 = new RedBackgroundDelegate(warningT);
    m_tableview->setItemDelegate(delegate1);


    QGroupBox* groupTemp = new QGroupBox(this);
    groupTemp->setTitle("历史温度");
    groupTemp->setLayout(hlayout);

    QHBoxLayout *hlayout2 = new QHBoxLayout(this);
    hlayout2->addWidget(groupTemp);

    m_model2 = new QSqlTableModel(this,db);
    m_model2->setTable("湿度");
    m_model2->setSort(m_model->fieldIndex("时间"),Qt::AscendingOrder);
    m_tableview2 = new QTableView(this);
    m_tableview2->setModel(m_model2);
    m_tableview2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_tableview2->setAlternatingRowColors(true);
    m_tableview2->setColumnWidth(0,350);
    RedBackgroundDelegate *delegate2 = new RedBackgroundDelegate(warningH);
    m_tableview2->setItemDelegate(delegate2);
    m_model2->select();

     QGroupBox* groupHumi = new QGroupBox(this);
     groupHumi->setTitle("历史湿度");
     QHBoxLayout *hlayout3 = new QHBoxLayout(groupHumi);
     hlayout3->addWidget(m_tableview2);
     hlayout2->addWidget(groupHumi);


}

