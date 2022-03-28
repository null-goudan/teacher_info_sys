#ifndef TEACHER_INFO_WIDGET_H
#define TEACHER_INFO_WIDGET_H

#include <QWidget>
#include "tableview.h"
#include "toolbar.h"
#include <QDebug>
#include "addwidget.h"

class m_tablewidget : public QWidget
{
    Q_OBJECT
public:
    explicit m_tablewidget(QWidget *parent = nullptr);
    ~m_tablewidget();
    QStandardItemModel* model();
    inline toolBar* toolbar();

signals:

protected:
    QVBoxLayout* mlayout;
    tableView* view;
    toolBar* tool;
    addWidget* addwidget;

    virtual void init_view();
public slots:
    virtual void on_Add();
    virtual void on_Del();
    virtual void on_Edit();
    virtual void add_info(QString info);


};

#endif // TEACHER_INFO_WIDGET_H
