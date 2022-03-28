#include "m_tablewidget.h"

m_tablewidget::m_tablewidget(QWidget *parent) : QWidget(parent), addwidget(new addWidget())
{
    tool = new toolBar(this);
    init_view();

    mlayout = new QVBoxLayout(this);

    mlayout->addWidget(tool);
    mlayout->addWidget(view);

    view->setEditTriggers(QAbstractItemView::NoEditTriggers);
    view->setSelectionBehavior(QAbstractItemView::SelectRows);
    connect(this->toolbar(), &toolBar::sig_Add, this, &m_tablewidget::on_Add);
    connect(this->toolbar(), &toolBar::sig_Del, this, &m_tablewidget::on_Del);
    connect(this->toolbar(), &toolBar::sig_Edit, this, &m_tablewidget::on_Edit);
    connect(this->addwidget, &addWidget::entryList, this, &m_tablewidget::add_info);
}

m_tablewidget::~m_tablewidget()
{
    delete tool;
    delete view;
    delete mlayout;
}

QStandardItemModel *m_tablewidget::model()
{
    return this->view->getModel();
}

toolBar *m_tablewidget::toolbar()
{
    return this->tool;
}

void m_tablewidget::init_view()
{
    QStringList* header = new QStringList();
    *header<<"职工号"<<"教师姓名"<<"性别"<<"出生年月"<<"民族"<<"籍贯所在地"
            <<"政治面貌"<<"毕业院校"<<"最高学历"<<"学位类型"
            <<"家庭住址"<<"用户名";

    this->view = new tableView(header, QString("teacher_info"),this);
}

void m_tablewidget::on_Add()
{
    qDebug()<<"add";
    this->addwidget->exec();
}

void m_tablewidget::on_Del()
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

void m_tablewidget::on_Edit()
{
    qDebug()<<"edit";
}

void m_tablewidget::add_info(QString info)
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
