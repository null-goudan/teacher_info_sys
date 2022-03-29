#include "updatewidget.h"

updatewidget::updatewidget(QString username, QWidget *parent) : QDialog(parent)
{
    idLine = new QLineEdit;
    nameLine = new QLineEdit;
    sexLine = new QComboBox;
    birthdayLine= new QLineEdit;
    idtyLine= new QLineEdit;
    adrHomeLine= new QLineEdit;
    idty_red_line= new QComboBox;
    school_fromLine= new QLineEdit;
    study_high_line= new QLineEdit;
    collage_type= new QLineEdit;
    address= new QLineEdit;
    hlayout = new QHBoxLayout();
    addbtn = new QPushButton("确定");
    cancel = new QPushButton("取消");
    flayout = new QFormLayout(this);
    this->teacher_id = nullptr;
    this->username = new QString(username);
    initUI();
    connect(this->cancel,&QPushButton::released, this, &QWidget::close);
}

updatewidget::updatewidget(QString teacher_id,bool have_teacher_id, QWidget *parenet): QDialog(parenet)
{
    idLine = new QLineEdit;
    nameLine = new QLineEdit;
    sexLine = new QComboBox;
    birthdayLine= new QLineEdit;
    idtyLine= new QLineEdit;
    adrHomeLine= new QLineEdit;
    idty_red_line= new QComboBox;
    school_fromLine= new QLineEdit;
    study_high_line= new QLineEdit;
    collage_type= new QLineEdit;
    address= new QLineEdit;
    hlayout = new QHBoxLayout();
    addbtn = new QPushButton("确定");
    cancel = new QPushButton("取消");
    flayout = new QFormLayout(this);
    this->teacher_id = new QString(teacher_id);
    initUI();
    connect(this->cancel,&QPushButton::released, this, &QWidget::close);
}

updatewidget::updatewidget(QString teacher_id, QString username, QWidget *parenet)
{
    idLine = new QLineEdit;
    nameLine = new QLineEdit;
    sexLine = new QComboBox;
    birthdayLine= new QLineEdit;
    idtyLine= new QLineEdit;
    adrHomeLine= new QLineEdit;
    idty_red_line= new QComboBox;
    school_fromLine= new QLineEdit;
    study_high_line= new QLineEdit;
    collage_type= new QLineEdit;
    address= new QLineEdit;
    hlayout = new QHBoxLayout();
    addbtn = new QPushButton("确定");
    cancel = new QPushButton("取消");
    flayout = new QFormLayout(this);
    this->teacher_id = new QString(teacher_id);
    this->username = new QString(username);
    initUI();
    connect(this->cancel,&QPushButton::released, this, &QWidget::close);
}

void updatewidget::updateInfo()
{
    QSqlQuery qr;
    if(this->teacher_id ==this->idLine->text()){
        qr.prepare("UPDATE teacher_info SET teacher_name=:name, \n"
                   "teacher_sex=:sex, \n"
                   "teacher_birthday=DATE(:date),\n"
                   "teacher_minzu=:idty,\n"
                   "teacher_addres = :address,\n"
                   "teacher_idty = :idty_red,\n"
                   "teacher_school = :school,\n"
                   "teacher_stu_his = :study_high,\n"
                   "teacher_stu_type = :collage_type,\n"
                   "teacher_add = :address,\n"
                   "username_id =:username where teacher_id = :teacher_id;");
    }else{
        qr.prepare("UPDATE teacher_info SET teacher_id=:id,"
                   "teacher_name=:name, \n"
                   "teacher_sex=:sex, \n"
                   "teacher_birthday=DATE(:date),\n"
                   "teacher_minzu=:idty,\n"
                   "teacher_addres = :address,\n"
                   "teacher_idty = :idty_red,\n"
                   "teacher_school = :school,\n"
                   "teacher_stu_his = :study_high,\n"
                   "teacher_stu_type = :collage_type,\n"
                   "teacher_add = :address,\n"
                   "username_id =:username where teacher_id = :teacher_id;");
        qr.bindValue(":id", this->idLine->text().toUInt());
    }
    qr.bindValue(":name", this->nameLine->text());
    qr.bindValue(":sex", this->sexLine->currentText());
    qr.bindValue(":date", this->birthdayLine->text());
    qr.bindValue(":idty", this->idtyLine->text());
    qr.bindValue(":address", this->adrHomeLine->text());
    qr.bindValue(":idty_red", this->idty_red_line->currentText());
    qr.bindValue(":school", this->school_fromLine->text());
    qr.bindValue(":study_high", this->study_high_line->text());
    qr.bindValue(":collage_type", this->collage_type->text());
    qr.bindValue(":address", address->text());
    qr.bindValue(":username", *this->username);
    qr.bindValue(":teacher_id", this->teacher_id->toUInt());
    if(qr.exec()){
        QMessageBox::warning(this, "成功", "更改信息成功");
        this->close();
        return ;
    }else{
        QMessageBox::warning(this, "失败", "失败原因"+ qr.lastError().text());
        return ;
    }
}

void updatewidget::updateInfo_no_info()
{
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
               "teacher_add,"
               "username_id)"
               "VALUES(:id,:name,:sex,DATE(:date),:idty,:address,:idty_red,:school,:study_high,:collage_type,:address, :username);");
    qr.bindValue(":id", this->idLine->text());
    qr.bindValue(":name", this->nameLine->text());
    qr.bindValue(":sex", this->sexLine->currentText());
    qr.bindValue(":date", this->birthdayLine->text());
    qr.bindValue(":idty", this->idtyLine->text());
    qr.bindValue(":address", this->adrHomeLine->text());
    qr.bindValue(":idty_red", this->idty_red_line->currentText());
    qr.bindValue(":school", this->school_fromLine->text());
    qr.bindValue(":study_high", this->study_high_line->text());
    qr.bindValue(":collage_type", this->collage_type->text());
    qr.bindValue(":address", address->text());
    qr.bindValue(":username", *this->username);
    if(qr.exec()){
        QMessageBox::warning(this, "成功", "填写信息成功");
        this->close();
        return ;
    }else{
        QMessageBox::warning(this, "失败", "失败原因"+ qr.lastError().text());
        return ;
    }
}

void updatewidget::initUI()
{
    hlayout->addWidget(addbtn);
    hlayout->addWidget(cancel);

    flayout->addRow("工号", this->idLine);
    flayout->addRow("教师姓名", this->nameLine);
    flayout->addRow("性别", this->sexLine);
    sexLine->addItem("男");
    sexLine->addItem("女");
    flayout->addRow("出生年月", this->birthdayLine);
    flayout->addRow("民族", this->idtyLine);
    flayout->addRow("籍贯所在地", this->adrHomeLine);
    flayout->addRow("政治面貌", this->idty_red_line);
    idty_red_line->addItem("共产党员");
    idty_red_line->addItem("群众");
    idty_red_line->addItem("其他党派");
    flayout->addRow("毕业院校", this->school_fromLine);
    flayout->addRow("最高学历", this->study_high_line);
    flayout->addRow("学位类型", this->collage_type);
    flayout->addRow("家庭住址", this->address);

    if(teacher_id == nullptr && username != nullptr){
        connect(this->addbtn, &QPushButton::released, this, &updatewidget::updateInfo_no_info);
    }else if(teacher_id != nullptr){
        QSqlQuery qr;
        qr.prepare("select * from teacher_info where teacher_id = :id");
        qr.bindValue(":id", *this->teacher_id);
        qr.exec();
        if(qr.next()){
           QSqlRecord qrc = qr.record();
           int indexOfid = qrc.indexOf("teacher_id");
           this->idLine->setText(qr.value(indexOfid).toString());
           int indexOfname = qrc.indexOf("teacher_name");
           this->nameLine->setText(qr.value(indexOfname).toString());
           int indexOfsex = qrc.indexOf("teacher_sex");
           this->sexLine->setCurrentText(qr.value(indexOfsex).toString());
           int indexOfbirthday = qrc.indexOf("teacher_birthday");
           this->birthdayLine->setText(qr.value(indexOfbirthday).toString());
           int indexOfminzu = qrc.indexOf("teacher_minzu");
           this->idtyLine->setText(qr.value(indexOfminzu).toString());
           int indexOfaddres = qrc.indexOf("teacher_addres");
           this->adrHomeLine->setText(qr.value(indexOfaddres).toString());
           int indexOfidty = qrc.indexOf("teacher_idty");
           this->idty_red_line->setCurrentText(qr.value(indexOfidty).toString());
           int indexOfschool = qrc.indexOf("teacher_school");
           this->school_fromLine->setText(qr.value(indexOfschool).toString());
           int indexOfstu_his = qrc.indexOf("teacher_stu_his");
           this->study_high_line->setText(qr.value(indexOfstu_his).toString());
           int indexOftype = qrc.indexOf("teacher_stu_type");
           this->collage_type->setText(qr.value(indexOftype).toString());
           int indexOfadd = qrc.indexOf("teacher_add");
           this->address->setText(qr.value(indexOfadd).toString());
        }
        connect(this->addbtn, &QPushButton::released, this, &updatewidget::updateInfo);
    }
    flayout->addRow(hlayout);
}
