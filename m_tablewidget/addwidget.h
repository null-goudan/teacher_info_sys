#ifndef ADDWIDGET_H
#define ADDWIDGET_H

#include <QObject>
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QFormLayout>

class addWidget : public QDialog
{
    Q_OBJECT
public:
    explicit addWidget(QWidget *parent = nullptr);
    void initUI();

signals:
    void entryList(QString info);

public slots:
    void onAdd();

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
};

#endif // ADDWIDGET_H
