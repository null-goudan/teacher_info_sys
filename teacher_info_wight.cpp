#include "teacher_info_wight.h"

teacher_info_wight::teacher_info_wight(QWidget *parent) : m_tablewidget(parent)
{

}

void teacher_info_wight::on_Add()
{
    this->addwidget->exec();
}

void teacher_info_wight::on_Del()
{
    int idx_row = this->view->currentIndex().row();
    int idx_col = this->view->currentIndex().column();
    QString id = this->model()->index(idx_row, idx_col).data().toString();
    qDebug()<<"del " + id;
    QSqlQuery qr;
    qr.prepare("DELETE from teacher_info where teacher_id = :id");
    qr.bindValue(":id", id);
    if(qr.exec()){
       QMessageBox::information(this, "成功", "删除成功");
       this->view->getModel()->removeRow(idx_row);
    }else{
        QMessageBox::warning(this, "失败", "失败"+ qr.lastError().text());
    }
}

void teacher_info_wight::on_Edit()
{
    qDebug()<<"add"<<endl;
}

void teacher_info_wight::add_info(QString info)
{
    QStringList l = info.split(",");
    QSqlQuery qr;
    qr.prepare("INSERT INTO teacher_info"
               "(teacher_id,"
               "teacher_name,"
               "teacher_sex,"
               "teacher_birthday,"
               "teacher_minzu,"
               "teacher_addres ,"
               "teacher_idty,"
               "teacher_school,"
               "teacher_stu_his,"
               "teacher_stu_type,"
               "teacher_add)"
               "VALUES(:id,:name,:sex,DATE(:date),:idty,:address,:idty_red,:school,:study_high,:collage_type,:address);");
    qr.bindValue(":id", QString(l[0]));
    qr.bindValue(":name", QString(l[1]));
    qr.bindValue(":sex", QString(l[2]));
    qr.bindValue(":date", QString(l[3]));
    qr.bindValue(":idty", QString(l[4]));
    qr.bindValue(":address", QString(l[5]));
    qr.bindValue(":idty_red", QString(l[6]));
    qr.bindValue(":school", QString(l[7]));
    qr.bindValue(":study_high", QString(l[8]));
    qr.bindValue(":collage_type", QString(l[9]));
    qr.bindValue(":address", QString(l[10]));
    QSqlRecord qrc = qr.record();
    if(qr.exec()){
       QMessageBox::information(this, "成功", "添加成功");
       QList<QStandardItem*> litem;
       for(auto s:l){
            litem<<new QStandardItem(s);
       }
       this->model()->appendRow(litem);
    }else{
        QMessageBox::warning(this, "失败", "失败"+ qr.lastError().text());
    }
}

void teacher_info_wight::init_view()
{
    QStringList* header = new QStringList();
    *header<<"职工号"<<"教师姓名"<<"性别"<<"出生年月"<<"民族"<<"籍贯所在地"
            <<"政治面貌"<<"毕业院校"<<"最高学历"<<"学位类型"
            <<"家庭住址"<<"用户名";

    this->view = new tableView(header, QString("teacher_info"),this);
}
