#include "infoshow.h"

infoshow::infoshow(QWidget *parent) : QWidget(parent)
{
    initUI();

}

infoshow::infoshow(QVector<QPair<QString, QString> *> infos, QWidget *parent)
{
    initUI();
    for(auto i:infos){
        this->addRows(i);
    }
}

void infoshow::addWidget(QWidget *pos)
{
    mlayout->addRow(pos);
}

void infoshow::initUI()
{
    mlayout = new QFormLayout(this);
    mlayout->addWidget(new QLabel("基本信息"));
}

void infoshow::addRows(QPair<QString, QString> *item)
{
    mlayout->addRow(item->first, new QLabel(item->second));
}
