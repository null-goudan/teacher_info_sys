#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QBoxLayout>

class toolBar : public QWidget
{
    Q_OBJECT
public:
    explicit toolBar(QWidget *parent = nullptr);
    ~toolBar();
    void addWight(QWidget* other);
signals:
    void sig_Add();
    void sig_Del();
    void sig_Edit();
private:
    QHBoxLayout* mlayout;
    QPushButton* addbtn;
    QPushButton* delbtn;
    QPushButton* updatebtn;
};

#endif // TOOLBAR_H
