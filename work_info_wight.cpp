#include "work_info_wight.h"

work_info_wight::work_info_wight()
{
    init_view();
}

void work_info_wight::on_Add()
{

}

void work_info_wight::on_Del()
{

}

void work_info_wight::on_Edit()
{

}

void work_info_wight::add_info(QString info)
{

}

void work_info_wight::init_view()
{
    QStringList* header = new QStringList();
    *header<<"职工号"<<"教师姓名"<<"时间"<<"类型";
    this->model()->clear();
    this->view = new tableView(header,this->model(), this);
    QStandardItemModel* model = this->model();
    QSqlQuery qr;
    qr.prepare("select * from work_record");
    if(!qr.exec()){
        QMessageBox::warning(this, "错误", "错误原因" + qr.lastError().text());
        return;
    }
    while(qr.next()){
        QSqlRecord qrc = qr.record();
        QList<QStandardItem*> l;
        QSqlQuery qr2;
        qr2.prepare("select * from teacher_info where teacher_id = :teacher_id");
        qr2.bindValue(":teacher_id", qr.value(1).toString());
        qr2.exec();
        qr2.next();
        QSqlRecord qrc2 = qr2.record();
        int teacher_id_idx = qrc2.indexOf("teacher_id");
        l<<new QStandardItem(qrc2.value(teacher_id_idx).toString());
        int teacher_name_idx = qrc2.indexOf("teacher_name");
        l<<new QStandardItem(qrc2.value(teacher_name_idx).toString());
        l<<new QStandardItem(qr.value(2).toDateTime().toString("yyyy-MM-dd hh:mm:ss"));
        l<<new QStandardItem("签到");
        model->insertRow(model->rowCount(), l);
    }
    qr.prepare("select * from leave_record");
    if(!qr.exec()){
        QMessageBox::warning(this, "错误", "错误原因" + qr.lastError().text());
        return;
    }
    while(qr.next()){
        QSqlRecord qrc = qr.record();
        QList<QStandardItem*> l;
        QSqlQuery qr2;
        qr2.prepare("select * from teacher_info where teacher_id = :teacher_id");
        qr2.bindValue(":teacher_id", qr.value(1).toString());
        qr2.exec();
        qr2.next();
        QSqlRecord qrc2 = qr2.record();
        int teacher_id_idx = qrc2.indexOf("teacher_id");
        l<<new QStandardItem(qrc2.value(teacher_id_idx).toString());
        int teacher_name_idx = qrc2.indexOf("teacher_name");
        l<<new QStandardItem(qrc2.value(teacher_name_idx).toString());
        l<<new QStandardItem(qr.value(2).toDateTime().toString("yyyy-MM-dd hh:mm:ss"));
        l<<new QStandardItem("签退");
        model->insertRow(model->rowCount(), l);
    }
    this->view->setModel(model);
}
