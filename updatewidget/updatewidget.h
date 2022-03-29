#ifndef UPDATEWIDGET_H
#define UPDATEWIDGET_H

#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QList>
#include <QString>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QVariant>
#include <QMessageBox>

class updatewidget : public QDialog
{
    Q_OBJECT
public:
    explicit updatewidget(QString username,QWidget *parent = nullptr);
    explicit updatewidget(QString teacher_id,bool have_teacher_id, QWidget *parenet = nullptr);
    explicit updatewidget(QString teacher_id,QString username, QWidget *parenet = nullptr);
signals:

public slots:
    void updateInfo();
    void updateInfo_no_info();

private:
    QLineEdit* idLine;
    QLineEdit* nameLine;
    QComboBox* sexLine;
    QLineEdit* birthdayLine;
    QLineEdit* idtyLine;
    QLineEdit* adrHomeLine;
    QComboBox* idty_red_line;
    QLineEdit* school_fromLine;
    QLineEdit* study_high_line;
    QLineEdit* collage_type;
    QLineEdit* address;

    QHBoxLayout* hlayout;
    QPushButton* addbtn;
    QPushButton* cancel;

    QFormLayout* flayout;

    QString* teacher_id;
    QString* username;
    QList<QString *> teacher_info;

    void initUI();
    bool getTeacherInfo();
};

#endif // UPDATEWIDGET_H
