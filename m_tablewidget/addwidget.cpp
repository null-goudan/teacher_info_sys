#include "addwidget.h"

addWidget::addWidget(QWidget *parent) : QDialog(parent)
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
    initUI();
    connect(this->cancel,&QPushButton::released, this, &QWidget::close);
    connect(this->addbtn,&QPushButton::released, this, &addWidget::onAdd);
}

void addWidget::initUI()
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
    flayout->addRow(hlayout);
}

void addWidget::onAdd()
{
    QString info = "";
    info += idLine->text()+",";
    info += nameLine->text()+",";
    info += sexLine->currentText()+",";
    info += birthdayLine->text()+",";
    info += idtyLine->text()+",";
    info += adrHomeLine->text()+",";
    info += idty_red_line->currentText()+",";
    info += school_fromLine->text()+",";
    info += study_high_line->text()+",";
    info += collage_type->text()+",";
    info += address->text();
    entryList(info);
    this->close();
}


