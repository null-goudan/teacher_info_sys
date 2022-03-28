#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);
    ui->PassWord->setEchoMode(QLineEdit::Password);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    QGraphicsDropShadowEffect *shadow  = new QGraphicsDropShadowEffect();
    //设置圆角
    shadow->setBlurRadius(15);
    shadow->setColor(Qt::black);
    //设置偏移量
    shadow->setOffset(0, 0);
    ui->widget->setGraphicsEffect(shadow);
    this->ConnetDb();

    connect(this->ui->LoginBtn, &QPushButton::clicked, this, &Login::login);
}

Login::~Login()
{
    delete db;
    delete ui;
}


void Login::on_CloseBtn_clicked()
{
    if(db->isOpen()){
        db->close();
    }
    this->close();
}

//重写鼠标移动事件
void Login::mouseMoveEvent ( QMouseEvent * event )
{
    //鼠标相对于桌面左上角的位置，全局位置
    QPoint y = event->globalPos();
    QPoint x = y-this->z;
    this->move(x);
}

//重写鼠标按下事件
void Login::mousePressEvent ( QMouseEvent * event )
{
    //获取鼠标全局x、y坐标
    QPoint y = event->globalPos();
    QPoint x = this->geometry().topLeft();

    this->z = y - x;
}

void Login::mouseReleaseEvent ( QMouseEvent * event )
{

}

bool Login::ConnetDb(){
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("123456");
    db.setDatabaseName("human_res");
    if(!db.open()){
        QMessageBox::warning(this,"错误",db.lastError().text());
        return false;
    }
    this->db = new QSqlDatabase(db);
    return true;
}

void Login::login()
{
    int idy = 0;
    QSqlQuery qy;
    if (this->ui->Teacher_user->isChecked()){
        idy = 1;
        qy.prepare("select * from normal_user where username = :input_username;");
    }else if(this->ui->Admin_user->isChecked()){
        idy = 2;
        qy.prepare("select * from admin_user where username = :input_username;");
    }else{
        QMessageBox::warning(this,"提示", "请选择用户");
        return ;
    }
    qy.bindValue(":input_username", QString(this->ui->UserName->currentText()));
    QSqlRecord qrc = qy.record();
    qDebug()<<this->ui->UserName->currentText();
    qy.exec();
    if(qy.next()){
        qrc = qy.record();
        int passcol = qrc.indexOf("password");
        QString password = qy.value(passcol).toString();
        if(password == this->ui->PassWord->text()){
            QMessageBox::warning(this,"成功", "登录成功");
            if (idy==1){
                self_info* s_info = new self_info(this->ui->UserName->currentText());
                s_info->show();
            }else if (idy==2){
                manager_admin* m_admin = new manager_admin();
                m_admin->show();
            }
            this->close();
        }else{
            QMessageBox::warning(this,"密码错误","登录失败");
        }
    }else{
        QMessageBox::warning(this,"错误","没有该用户名");
    }
}

