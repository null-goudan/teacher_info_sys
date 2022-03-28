#ifndef WORK_INFO_WIGHT_H
#define WORK_INFO_WIGHT_H

#include <QObject>
#include <QWidget>
#include "m_tablewidget.h"

class work_info_wight : public m_tablewidget
{
    Q_OBJECT
public:
    explicit work_info_wight();

public slots:
    void on_Add() override;
    void on_Del() override;
    void on_Edit() override;
    void add_info(QString info) override;
protected:
    void init_view() override;

    QVBoxLayout* mlayout;
    tableView* view;
    toolBar* tool;
    addWidget* addwidget;
};

#endif // WORK_INFO_WIGHT_H
