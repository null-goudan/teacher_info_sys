#include "statistician.h"
#include <QDebug>

statistician::statistician(QString teacher_id, int mouth)
{
    ConnectDb();
    getWorkTimePerMouth(teacher_id, mouth);
    getLeaveTimePerMouth(teacher_id, mouth);
}

int statistician::getNumOfWorkLate(int mouth)
{
    int cnt = 0;
    for(auto i: workdatetime){
        if(i->date().month()==mouth){
            if(i->time().hour() > this->workTime_h){
                cnt++;
            }
        }
    }
    return cnt;
}

int statistician::getNumOfLeaveEarly(int mouth)
{
    int cnt = 0;
    for(auto i: leavedatetime){
        if(i->date().month()==mouth){
            if(i->time().hour() < this->leaveTime_h){
                cnt++;
            }
        }
    }
    return cnt;
}

int statistician::getNumOfWorkDayMouth()
{
    return workdatetime.length();
}

int statistician::getNumOFoutWorkDayMouth()
{
    QDate today = QDate::currentDate();
    int mouth = today.month();
    if( mouth == 1|| mouth == 3 || mouth == 5 || mouth == 7 || mouth == 8 ||
            mouth == 10 || mouth == 12)
        return 31-getNumOfWorkDayMouth();
    else if(mouth == 2){
        return 28-getNumOfWorkDayMouth();
    }else{
        return 30-getNumOfWorkDayMouth();
    }
}

bool statistician::isTodayWork()
{
    QDate today = QDate::currentDate();
    for(auto i: workdatetime){
        if(i->date().day() == today.day() && i->date().month() == today.month()){
            return true;
        }
    }
    return false;
}

bool statistician::isTodayLeave()
{
    QDate today = QDate::currentDate();
    for(auto i: leavedatetime){
        if(i->date().day() == today.day() && i->date().month() == today.month()){
            return true;
        }
    }
    return false;
}

bool statistician::ConnectDb()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("123456");
    db.setDatabaseName("human_res");
    if(!db.open()){
        return false;
    }
    this->db = new QSqlDatabase(db);
    return true;
}

void statistician::getWorkTimePerMouth(QString teacher_id, int mouth)
{
    QSqlQuery qr;
    qr.prepare("select * from work_record where user_id = :teacher_id");
    qr.bindValue(":teacher_id", teacher_id);
    if(qr.exec()){
        while(qr.next()){
            QSqlRecord qrc = qr.record();
            int datetime_idx = qrc.indexOf("work_date");
            QDateTime* work_time = new QDateTime(qr.value(datetime_idx).toDateTime());
            if(work_time->date().month()==mouth){
                workdatetime<<work_time;
            }else{
                delete work_time;
            }
        }
    }else{
        qDebug()<<"失败"<<qr.lastError();
    }
}

void statistician::getLeaveTimePerMouth(QString teacher_id, int mouth)
{
    QSqlQuery qr;
    qr.prepare("select * from leave_record where user_id = :teacher_id");
    qr.bindValue(":teacher_id", teacher_id);
    if(qr.exec()){
        while(qr.next()){
            QSqlRecord qrc = qr.record();
            int datetime_idx = qrc.indexOf("leave_time");
            QDateTime* leave_time = new QDateTime(qr.value(datetime_idx).toDateTime());
            if(leave_time->date().month()==mouth){
                leavedatetime<<leave_time;
            }else{
                delete leave_time;
            }
        }
    }else{
        qDebug()<<"失败"<<qr.lastError();
    }
}
