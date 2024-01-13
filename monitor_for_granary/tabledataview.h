#ifndef TABLEDATAVIEW_H
#define TABLEDATAVIEW_H

#include <QWidget>
#include <QSqlTableModel>
#include <QTableView>
#include <QPainter>

#include <QStyledItemDelegate>
class TableDataView : public QWidget
{
    Q_OBJECT
public:
    explicit TableDataView(QWidget *parent = nullptr);
    void setDatabase(QSqlDatabase &db);
    float warningT;
    float warningH;
private:
    QSqlTableModel *m_model;
     QSqlTableModel *m_model2;
    QTableView *m_tableview;
    QTableView *m_tableview2;
    QSqlDatabase *db;




signals:

};

class RedBackgroundDelegate : public QStyledItemDelegate {
public:
    RedBackgroundDelegate(float warningVal,QObject *parent = nullptr) : QStyledItemDelegate(parent),warningVal(warningVal) {}

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override {
        // 获取单元格的数据
        QVariant data = index.data(Qt::DisplayRole);

        // 检查是否为数字并且超过特定值
        if (data.canConvert(QMetaType::Double) && data.toDouble() >warningVal ) {
            // 如果条件满足，设置红色背景
            painter->fillRect(option.rect,QColor(255, 106, 106));
            painter->setPen(Qt::white);
        }

        // 继续绘制正常的内容
        QStyledItemDelegate::paint(painter, option, index);
    }
private:
    float warningVal;
};

#endif // TABLEDATAVIEW_H
