#ifndef TABLEVIEW_H
#define TABLEVIEW_H

#include <QWidget>
#include <QTableView>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QMessageBox>
#include <QSqlError>

class tableView : public QTableView
{
    Q_OBJECT
public:
    explicit tableView(QStringList *header,QStandardItemModel* model, QWidget *parenet);
    explicit tableView(QStringList* header, QString table_name, QWidget *parent = nullptr);
    ~tableView();
    inline QStandardItemModel* getModel(){
        return this->model;
    };
signals:

private:
    QStandardItemModel* model = nullptr;
    QSqlDatabase* db;
    void initmodel(QStringList* header, QString table_name);
    void initmodel(QStringList *header, QStandardItemModel* model);
    bool ConnetDb();
};

#endif // TABLEVIEW_H
