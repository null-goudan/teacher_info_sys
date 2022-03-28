#ifndef MANAGE_INFO_H
#define MANAGE_INFO_H

#include <QWidget>
#include <QGraphicsDropShadowEffect>
#include <QMouseEvent>
#include <QSqlTableModel>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QStandardItemModel>
#include <QStandardItem>

namespace Ui {
class manage_info;
}

class manage_info : public QWidget
{
    Q_OBJECT

public:
    explicit manage_info(QWidget *parent = nullptr);
    ~manage_info();

private slots:
    void on_close_btn_clicked();

    void on_min_btn_clicked();

    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    Ui::manage_info *ui;
    QPoint z;
    int mode_index;
    QStandardItemModel* model;
    void check_mode();
    bool init_model();
    void show_model();
};

#endif // MANAGE_INFO_H
