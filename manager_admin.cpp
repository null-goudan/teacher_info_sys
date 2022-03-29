#include "manager_admin.h"
#include <QFile>

manager_admin::manager_admin(QWidget *parent) : QWidget(parent),
    m_wighet(new QWidget(this)), m_window(new QStackedWidget), info_widget(new teacher_info_wight)
{

    this->m_wighet->setObjectName("m_wighet");
    initUI();

    connect(this->close_btn, &QPushButton::released, this, &QWidget::close);
    connect(this->min_btn, &QPushButton::released, this, &QWidget::showMinimized);
    connect(this->teacher_info_btn, &QPushButton::released, this, [=](){
        this->m_window->setCurrentIndex(0);
    });
    connect(this->teacher_work_info_btn, &QPushButton::released, this, [=](){
        this->m_window->setCurrentIndex(1);
    });
}

void manager_admin::initUI()
{
    this->setMinimumSize(1350, 700);
    this->m_wighet->setGeometry(1,1, 1310, 650);
    windowtitle = new QLabel("教师信息管理", this->m_wighet);
    windowtitle->setGeometry(0, 0, 170, 60);
    windowtitle->setObjectName("windowtitle");
    close_btn = new QPushButton("×", this->m_wighet);
    close_btn->setObjectName("close_btn");
    close_btn->setGeometry(this->m_wighet->width()-30,0,30,30);
    min_btn = new QPushButton("-", this->m_wighet);
    min_btn->setObjectName("min_btn");
    min_btn->setGeometry(this->m_wighet->width()-60,0,30,30);
    teacher_info_btn = new QPushButton("教师基本信息管理", this->m_wighet);
    teacher_info_btn->setObjectName("teacher_info_btn");
    teacher_info_btn->setGeometry(5,70,180,35);
    teacher_work_info_btn = new QPushButton("教师考勤信息",this->m_wighet);
    teacher_work_info_btn->setObjectName("teacher_work_info_btn");
    teacher_work_info_btn->setGeometry(5,105,180,35);
    teacher_level_info_btn = new QPushButton("教师统计信息",this->m_wighet);
    teacher_level_info_btn->setObjectName("teacher_level_info_btn");
    teacher_level_info_btn->setGeometry(5,140,180,35);
    m_window = new QStackedWidget(this->m_wighet);
    work_info_widget = new work_info_wight();
    m_window->addWidget(this->info_widget);
    m_window->addWidget(this->work_info_widget);
    m_window->setGeometry(180,70,1125,580);
    m_window->setObjectName("m_window");

    QFile f(":/image/manager_admin.css");
    f.open(QIODevice::ReadOnly);
    QString style = f.readAll();
    this->setStyleSheet(style);

    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
//    QGraphicsDropShadowEffect *shadow  = new QGraphicsDropShadowEffect();
//    //设置圆角
//    shadow->setBlurRadius(15);
//    shadow->setColor(Qt::black);
//    //设置偏移量
//    shadow->setOffset(0, 0);
//    this->setGraphicsEffect(shadow);
}
//重写鼠标移动事件
void manager_admin::mouseMoveEvent ( QMouseEvent * event )
{
    //鼠标相对于桌面左上角的位置，全局位置
    QPoint y = event->globalPos();
    QPoint x = y - this->z;

    this->move(x);
}

//重写鼠标按下事件
void manager_admin::mousePressEvent ( QMouseEvent * event )
{
    //获取鼠标全局x、y坐标
    QPoint y = event->globalPos();
    QPoint x = this->geometry().topLeft();

    this->z = y - x;
}

void manager_admin::mouseReleaseEvent ( QMouseEvent * event )
{

}
