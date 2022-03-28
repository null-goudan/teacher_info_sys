#ifndef MANAGER_ADMIN_H
#define MANAGER_ADMIN_H

#include <QObject>
#include <QWidget>
#include <QStackedWidget>
#include <teacher_info_wight.h>
#include <QLabel>
#include <QGraphicsDropShadowEffect>
#include <QMouseEvent>
#include <QPoint>
#include "work_info_wight.h"

class manager_admin : public QWidget
{
    Q_OBJECT
public:
    explicit manager_admin(QWidget *parent = nullptr);
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

signals:

private:
    QWidget* m_wighet;
    QLabel* windowtitle;
    QPushButton* close_btn;
    QPushButton* min_btn;
    QPushButton* teacher_info_btn;
    QPushButton* teacher_work_info_btn;
    QPushButton* teacher_level_info_btn;
    QStackedWidget* m_window;
    teacher_info_wight* info_widget;
    work_info_wight* work_info_widget;

    QPoint z;

    void initUI();
};

#endif // MANAGER_ADMIN_H
