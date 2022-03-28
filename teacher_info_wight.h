#ifndef TEACHER_INFO_WIGHT_H
#define TEACHER_INFO_WIGHT_H

#include <QObject>
#include <QWidget>
#include "m_tablewidget.h"

class teacher_info_wight : public m_tablewidget
{
    Q_OBJECT
public:
    explicit teacher_info_wight(QWidget *parent = nullptr);

signals:

public slots:
    void on_Add() override;
    void on_Del() override;
    void on_Edit() override;
    void add_info(QString info) override;
protected:
    void init_view() override;
};

#endif // TEACHER_INFO_WIGHT_H
