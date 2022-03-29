#include "self_info.h"
#include <QFile>
#include <QDebug>
#include <QDateTime>
#include "updatewidget.h"

self_info::self_info(QWidget *parent) : QWidget(parent),
    m_widget(new QWidget(this)),t_widget(new QTabWidget(m_widget))
{
    initUI();
    connect(this->close_btn, &QPushButton::released, this, &QWidget::close);
}

self_info::self_info(QString username, QWidget *parent): QWidget(parent),
    m_widget(new QWidget(this)),t_widget(new QTabWidget(m_widget))
{
    this->username =new QString(username);
    initUI();
    this->leave_btn->setDisabled(true);
    connect(this->close_btn, &QPushButton::released, this, &QWidget::close);
    connect(this->work_add_btn, &QPushButton::released, this, [this](){
        QSqlQuery qr;
        qr.prepare("INSERT INTO work_record (user_id,work_date) VALUES (:teacher_id ,NOW());");
        qr.bindValue(":teacher_id", *(this->teacher_id));
        if(qr.exec()){
            QMessageBox::warning(this, "成功", "签到时间： "+ QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss"));
            this->userworkinfo.last()->second = "已签到" ;
        }else{
            QMessageBox::warning(this, "失败", "签到失败" + qr.lastError().text());
        }
        statistician sta(*this->teacher_id, QDate::currentDate().month());
        if(sta.isTodayWork()){
            this->work_add_btn->setDisabled(true);
            if(sta.isTodayLeave()){
                this->leave_btn->setDisabled(true);
            }else{
                this->leave_btn->setDisabled(false);
            }
        }else{
            this->work_add_btn->setDisabled(false);
        }
        reflash();
    });
    connect(this->leave_btn, &QPushButton::released, this, [this](){
        QSqlQuery qr;
        qr.prepare("INSERT INTO leave_record (user_id,leave_time) VALUES (:teacher_id ,NOW());");
        qr.bindValue(":teacher_id", *(this->teacher_id));
        if(qr.exec()){
            QMessageBox::warning(this, "成功", "签退时间 "+ QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss"));
            this->userworkinfo.last()->second = "已签到并签退" ;
        }else{
            QMessageBox::warning(this, "失败", "签退失败" + qr.lastError().text());
        }
        statistician sta(*this->teacher_id, QDate::currentDate().month());
        if(sta.isTodayWork()){
            this->work_add_btn->setDisabled(true);
            if(sta.isTodayLeave()){
                this->leave_btn->setDisabled(true);
            }else{
                this->leave_btn->setDisabled(false);
            }
        }else{
            this->work_add_btn->setDisabled(false);
        }
        reflash();
    });
    getworkinfo();
    connect(this->leave_ask_btn, &QPushButton::released, this, &self_info::reflash);
}

void self_info::initUI()
{
    ConnectDB();
    if(!this->username->isEmpty()){
        getbaseinfo();
        for(auto i : this->userbaseinfo){
            if(i->first=="教师工号"){
                teacher_id = new QString(i->second);
                break;
            }
        }
        getworkinfo();

    }
    tab_1 = new infoshow(this->userbaseinfo);
    tab_2 = new infoshow(this->userworkinfo);
    m_widget->setGeometry(2,2,410,380);
    this->m_widget->setGeometry(1,1,415,385);
    this->m_widget->setParent(this);
    this->m_widget->setObjectName("m_widget");
    t_widget->setGeometry(130,50, 270, 320);
    t_widget->addTab(tab_1,"基本信息");
    t_widget->addTab(tab_2,"工作信息");
    this->avtavl = new QLabel(m_widget);
    this->avtavl->setGeometry(35, 35, 70, 70);
    this->avtavl->setStyleSheet("*{background-color: rgb(255,255,255);}");
    this->name = new QLabel(m_widget);
    this->name->setText("名字");
    this->name->setGeometry(10, 120, 115, 35);
    this->name->setStyleSheet("*{text-align: center;}");
    this->work_add_btn = new QPushButton("工作打卡", m_widget);
    this->work_add_btn->setGeometry(10 ,this->m_widget->height()-140, 110, 35);
    this->leave_btn = new QPushButton("签退", m_widget);
    this->leave_btn->setGeometry(10 ,this->m_widget->height()-95, 110, 35);
    this->leave_ask_btn = new QPushButton("请假", m_widget);
    this->leave_ask_btn->setGeometry(10 ,this->m_widget->height()-45, 110, 35);
    this->close_btn = new QPushButton("×", m_widget);
    this->close_btn->setGeometry(this->m_widget->width()-35, 0, 35,35);
    this->close_btn->setObjectName("close_btn");
    for(auto i : this->userbaseinfo){
        if(i->first=="教师姓名"){
            this->name->setText("   姓名:  "+i->second);
            break;
        }
    }

    statistician* sta = new statistician(*this->teacher_id, QDate::currentDate().month());
    if(sta->isTodayWork()){
        this->userworkinfo.append(new QPair<QString, QString>("今日签到状态：", "已签到"));
        this->work_add_btn->setDisabled(true);
        if(sta->isTodayLeave()){
            this->leave_btn->setDisabled(true);
        }
    }
    QPushButton *update_self_info = new QPushButton("更改自己的信息");
    this->tab_1->addWidget(update_self_info);
    if(this->userbaseinfo.length()>3){
        connect(update_self_info, &QPushButton::released, this, [=]{
            updatewidget* uw = new updatewidget( *this->teacher_id,*this->username);
            uw->exec();
            reflash();
        });
    }else{
        connect(update_self_info, &QPushButton::released, this, [=]{
            updatewidget* uw = new updatewidget(*this->username);
            uw->exec();
            reflash();
        });
    }
    QFile f(":/image/self_info.css");
    f.open(QIODevice::ReadOnly);
    QString style = f.readAll();
    this->setStyleSheet(style);

    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
}

bool self_info::ConnectDB()
{
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
    return true;
}

void self_info::getbaseinfo()
{
    QSqlQuery qr;
    qr.prepare("select * from teacher_info where username_id = :username");
    qr.bindValue(":username", *this->username);
    if(qr.exec()){
        qr.next();
        QSqlRecord qrc = qr.record();
        int teacher_id_idx =qrc.indexOf("teacher_id");
        this->userbaseinfo.append(new QPair<QString, QString>("教师工号", qrc.value(teacher_id_idx).toString()));
        int teacher_name_idx =qrc.indexOf("teacher_name");
        this->userbaseinfo.append(new QPair<QString, QString>("教师姓名", qrc.value(teacher_name_idx).toString()));
        int teacher_sex_idx =qrc.indexOf("teacher_sex");
        this->userbaseinfo.append(new QPair<QString, QString>("性别", qrc.value(teacher_sex_idx).toString()));
        int teacher_birthday_idx =qrc.indexOf("teacher_birthday");
        this->userbaseinfo.append(new QPair<QString, QString>("出生年月", qrc.value(teacher_birthday_idx).toString()));
        int teacher_minzu_idx =qrc.indexOf("teacher_minzu");
        this->userbaseinfo.append(new QPair<QString, QString>("民族", qrc.value(teacher_minzu_idx).toString()));
        int teacher_addres_idx =qrc.indexOf("teacher_addres");
        this->userbaseinfo.append(new QPair<QString, QString>("籍贯所在地", qrc.value(teacher_addres_idx).toString()));
        int teacher_idty_idx =qrc.indexOf("teacher_idty");
        this->userbaseinfo.append(new QPair<QString, QString>("政治面貌", qrc.value(teacher_idty_idx).toString()));
        int teacher_school_idx =qrc.indexOf("teacher_school");
        this->userbaseinfo.append(new QPair<QString, QString>("毕业院校", qrc.value(teacher_school_idx).toString()));
        int teacher_stu_his_idx =qrc.indexOf("teacher_stu_his");
        this->userbaseinfo.append(new QPair<QString, QString>("最高学历", qrc.value(teacher_stu_his_idx).toString()));
        int teacher_stu_type_idx =qrc.indexOf("teacher_stu_type");
        this->userbaseinfo.append(new QPair<QString, QString>("学位类型", qrc.value(teacher_stu_type_idx).toString()));
        int teacher_add_idx =qrc.indexOf("teacher_add");
        this->userbaseinfo.append(new QPair<QString, QString>("家庭住址", qrc.value(teacher_add_idx).toString()));
    }else{
        qDebug()<<qr.lastError().text();
    }
}

void self_info::getworkinfo()
{
    statistician* sta = new statistician(*this->teacher_id, QDateTime::currentDateTime().date().month());
    QString temp = QString("%1");
    QString num_work_late = QString(temp.arg(sta->getNumOfWorkLate(QDateTime::currentDateTime().date().month())));
    this->userworkinfo.append(new QPair<QString, QString>("迟到次数：", num_work_late));
    QString num_leave_early = QString(temp.arg(sta->getNumOfLeaveEarly(QDateTime::currentDateTime().date().month())));
    this->userworkinfo.append(new QPair<QString, QString>("早退次数", num_leave_early));
    QString num_work_day = QString(temp.arg(sta->getNumOfWorkDayMouth()));
    this->userworkinfo.append(new QPair<QString, QString>("签到次数", num_work_day));
    QString num_outwork_day = QString(temp.arg(sta->getNumOFoutWorkDayMouth()));
    this->userworkinfo.append(new QPair<QString, QString>("缺勤次数", num_outwork_day));
    if(sta->isTodayWork()){
        this->userworkinfo.append(new QPair<QString, QString>("今日签到状态：", "已签到"));
        if(sta->isTodayLeave()){
            this->userworkinfo.last()->second = "已签到并签退";
        }
        //this->work_add_btn->setDisabled(true);
    }else{
        this->userworkinfo.append(new QPair<QString, QString>("今日签到状态：", "未签到"));
    }
}

void self_info::reflash()
{
    QSqlQuery qr;
    qr.prepare("select * from teacher_info where username_id = :username");
    qr.bindValue(":username", *this->username);
    if(qr.exec()){
        qr.next();
        QSqlRecord qrc = qr.record();
        int teacher_id_idx =qrc.indexOf("teacher_id");
        this->userbaseinfo.first()->second = qrc.value(teacher_id_idx).toString();
        int teacher_name_idx =qrc.indexOf("teacher_name");
        this->userbaseinfo.at(1)->second =  qrc.value(teacher_name_idx).toString();
        int teacher_sex_idx =qrc.indexOf("teacher_sex");
        this->userbaseinfo.at(2)->second =  qrc.value(teacher_sex_idx).toString();
        int teacher_birthday_idx =qrc.indexOf("teacher_birthday");
        this->userbaseinfo.at(3)->second =  qrc.value(teacher_birthday_idx).toString();
        int teacher_minzu_idx =qrc.indexOf("teacher_minzu");
        this->userbaseinfo.at(4)->second =  qrc.value(teacher_minzu_idx).toString();
        int teacher_addres_idx =qrc.indexOf("teacher_addres");
        this->userbaseinfo.at(5)->second =  qrc.value(teacher_addres_idx).toString();
        int teacher_idty_idx =qrc.indexOf("teacher_idty");
        this->userbaseinfo.at(6)->second =  qrc.value(teacher_idty_idx).toString();
        int teacher_school_idx =qrc.indexOf("teacher_school");
        this->userbaseinfo.at(7)->second =  qrc.value(teacher_school_idx).toString();
        int teacher_stu_his_idx =qrc.indexOf("teacher_stu_his");
        this->userbaseinfo.at(8)->second =  qrc.value(teacher_stu_his_idx).toString();
        int teacher_stu_type_idx =qrc.indexOf("teacher_stu_type");
        this->userbaseinfo.at(9)->second =  qrc.value(teacher_stu_type_idx).toString();
        int teacher_add_idx =qrc.indexOf("teacher_add");
       this->userbaseinfo.at(10)->second =  qrc.value(teacher_add_idx).toString();
    }

    infoshow* deletetab = tab_1;
    tab_1 = new infoshow(this->userbaseinfo);
    QPushButton *update_self_info = new QPushButton("更改自己的信息");
    this->tab_1->addWidget(update_self_info);
    if(this->userbaseinfo.length()>3){
        connect(update_self_info, &QPushButton::released, this, [=]{
            updatewidget* uw = new updatewidget( *this->teacher_id,*this->username);
            uw->exec();
            reflash();
        });
    }else{
        connect(update_self_info, &QPushButton::released, this, [=]{
            updatewidget* uw = new updatewidget(*this->username);
            uw->exec();
            reflash();
        });
    }

    delete deletetab;
    infoshow* deletetab_2 = static_cast<infoshow*>(tab_2);
    this->userworkinfo.clear();
    getworkinfo();
    tab_2 = new infoshow(this->userworkinfo);
    delete deletetab_2;

    this->t_widget->addTab(tab_1, "基本信息");
    this->t_widget->addTab(tab_2, "工作信息");
}
