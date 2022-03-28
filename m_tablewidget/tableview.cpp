#include "tableview.h"
#include <QDebug>
#include <stdio.h>

tableView::tableView(QStringList *header,QStandardItemModel* model, QWidget *parenet):model(new QStandardItemModel())
{
    ConnetDb();
    initmodel(header, model);
}

tableView::tableView(QStringList* header, QString table_name, QWidget *parent): QTableView(parent),model(new QStandardItemModel())
{
    ConnetDb();
    initmodel(header, table_name);
}

tableView::~tableView()
{
    if(db->isOpen()){
        db->close();
    }
    delete db;
    delete model;
}



bool tableView::ConnetDb(){
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("123456");
    db.setDatabaseName("human_res");
    if(!db.open()){
        QMessageBox::warning(this,"错误",db.lastError().text());
        return false;
    }
    this->db = new QSqlDatabase(db);
//    initmodel();
    return true;
}

void tableView::initmodel(QStringList* header, QString table_name)
{
    model->setHorizontalHeaderLabels(*header);
    // 读取数据库数据
    QSqlQuery qy;
    qy.prepare(QString("select * from %1").arg(table_name));
    if(!qy.exec()){
        QMessageBox::warning(this,"错误",qy.lastError().text());
        qDebug()<<qy.lastError().text()<<endl<<qy.lastQuery();
    }
    while(qy.next()){
        QSqlRecord qrc;
        qrc = qy.record();
        QList<QStandardItem*> l;
        for(int i=0;i<qrc.count();i++){
            l<<new QStandardItem(qy.value(i).toString());
        }
        model->insertRow(model->rowCount(), l);
    }
    //
    this->setModel(model);
}

void tableView::initmodel(QStringList *header, QStandardItemModel* model)
{
    model->setHorizontalHeaderLabels(*header);
}
