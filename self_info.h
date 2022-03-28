#ifndef SELF_INFO_H
#define SELF_INFO_H

#include <QObject>
#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QMessageBox>
#include <QSqlError>
#include <QTabWidget>
#include <QLabel>
#include <QPushButton>
#include <QVector>
#include <QPair>
#include <QVariant>
#include "infoshow.h"
#include "statistician.h"



class self_info : public QWidget
{
    Q_OBJECT
public:
    explicit self_info(QWidget *parent = nullptr);
    explicit self_info(QString username , QWidget *parent = nullptr);


signals:

private:
    QLabel* avtavl;
    QLabel* name;
    QWidget* m_widget;
    QTabWidget* t_widget;
    infoshow* tab_1;
    QWidget* tab_2;
    QWidget* tab_3;
    QPushButton* work_add_btn;
    QPushButton* leave_btn;
    QPushButton* leave_ask_btn;
    QPushButton* close_btn;
    QString* username;
    QSqlDatabase* db;
    QString *teacher_id;

    QVector<QPair<QString, QString> *> userbaseinfo;
    QVector<QPair<QString, QString> *> userworkinfo;

    void initUI();
    bool ConnectDB();
    void getbaseinfo();
    void getworkinfo();
};

#endif // SELF_INFO_H
