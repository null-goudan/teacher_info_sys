#ifndef INFOSHOW_H
#define INFOSHOW_H

#include <QObject>
#include <QWidget>
#include <QVector>
#include <QVariant>
#include <QLabel>
#include <QFormLayout>

class infoshow : public QWidget
{
    Q_OBJECT
public:
    explicit infoshow(QWidget *parent = nullptr);
    explicit infoshow(QVector<QPair<QString, QString>*> infos,QWidget *parent = nullptr);
signals:

private:
    void initUI();
    QFormLayout* mlayout;

protected:
    virtual void addRows(QPair<QString, QString>* item);
};

#endif // INFOSHOW_H
