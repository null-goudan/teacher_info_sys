#ifndef STATISTICIAN_H
#define STATISTICIAN_H

#include <QDateTime>
#include <QDate>
#include <QTime>
#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QVariant>

class statistician
{
public:
    statistician(QString teacher_id, int mouth);
    int getNumOfWorkLate(int mouth);
    int getNumOfLeaveEarly(int mouth);
    int getNumOfWorkDayMouth();
    int getNumOFoutWorkDayMouth();
    bool isTodayWork();
    bool isTodayLeave();
private:
    QSqlDatabase* db;
    QList<QDateTime*> workdatetime;
    QList<QDateTime*> leavedatetime;

    const int workTime_h = 8;
    const int leaveTime_h = 17;

    bool ConnectDb();
    void getWorkTimePerMouth(QString teacher_id, int mouth);
    void getLeaveTimePerMouth(QString teacher_id, int mouth);
};

#endif // STATISTICIAN_H
