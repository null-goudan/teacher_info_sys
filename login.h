#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QPoint>
#include <QMouseEvent>
#include <QGraphicsDropShadowEffect>
#include <QSqlDriver>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QSqlRecord>
#include <QDebug>
#include "self_info.h"
#include "manager_admin.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Login; }
QT_END_NAMESPACE

class Login : public QWidget
{
    Q_OBJECT

public:
    Login(QWidget *parent = nullptr);
    ~Login();

private slots:
    void on_CloseBtn_clicked();
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    Ui::Login *ui;
    QPoint z;

    QSqlQuery* query;
    QSqlDatabase* db;

    bool ConnetDb();
    void login();
};
#endif // LOGIN_H
