#include "toolbar.h"

toolBar::toolBar(QWidget *parent) : QWidget(parent),
    addbtn(new QPushButton(QIcon(":/img/add.png"),"添加")), delbtn(new QPushButton(QIcon(":/img/delete.png"),"删除")),
    updatebtn(new QPushButton(QIcon(":/img/edit.png"),"更改"))
{
    this->mlayout = new QHBoxLayout(this);
    mlayout->addWidget(addbtn);
    mlayout->addWidget(updatebtn);
    mlayout->addWidget(delbtn);
    mlayout->addStretch();

    connect(this->addbtn, &QPushButton::released, this, &toolBar::sig_Add);
    connect(this->updatebtn, &QPushButton::released, this, &toolBar::sig_Edit);
    connect(this->delbtn, &QPushButton::released, this, &toolBar::sig_Del);
}

toolBar::~toolBar()
{
    delete addbtn;
    delete delbtn;
    delete updatebtn;
}

void toolBar::addWight(QWidget *other)
{
    this->mlayout->insertWidget(mlayout->count()-1, other);
}
