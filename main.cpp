#include "login.h"

#include <QApplication>
#include "m_tablewidget.h"
#include "manager_admin.h"
#include "self_info.h"
#include "work_info_wight.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    self_info w("837471654");
    //Login w;
    //manager_admin w;
    //work_info_wight w;
    w.show();
    return a.exec();
}
