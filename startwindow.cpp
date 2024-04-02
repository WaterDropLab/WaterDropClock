#if _MSC_VER >=1600
#pragma execution_character_set("utf-8")
#endif
#ifndef ABOUTME_H
#define ABOUTME_H
#include "startwindow.h"
#include "ui_startwindow.h"
#include <QPainter>
#include <QFile>
#include <QSettings>
#include <QMouseEvent>
#include <displaywindow.h>
#include <QFont>
#include <QMessageBox>
StartWindow::StartWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::StartWindow)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_TranslucentBackground);//设置窗口背景透明
        this->setWindowFlags(Qt::FramelessWindowHint);   //设置无边框窗口
state=0;
time=new QTimer;

time->setInterval(5000);

connect(time,SIGNAL(timeout()),this,SLOT(on_time_timout()));

time1=new QTimer;
ui->labMovie->setScaledContents(0);
time1->setInterval(2);
time1->start();
connect(time1,SIGNAL(timeout()),this,SLOT(on_time1_timout()));
}


StartWindow::~StartWindow()
{
    delete ui;

}

void StartWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QColor color;
    color.setRgb(97,97,97);
    QPen pen;
    pen.setWidth(0);

       painter.setRenderHint(QPainter::Antialiasing); // 设置抗锯齿，不然边框会有明显锯齿
       painter.setBrush(color);                   // 设置窗体颜色
       QRect rect = this->rect();
    painter.setPen(Qt::transparent);
       // 绘制方式1
       painter.drawRoundedRect(rect,13,13);


}

void StartWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_moving = true;

        //记录下鼠标相对于窗口的位置
        //event->globalPos()鼠标按下时，鼠标相对于整个屏幕位置
        //pos() this->pos()鼠标按下时，窗口相对于整个屏幕位置
        m_lastPos = event->globalPos() - pos();
    }
    return QDialog::mousePressEvent(event);  //
}

void StartWindow::mouseMoveEvent(QMouseEvent *event)
{
    //鼠标按下左键移动
        //(event->buttons() && Qt::LeftButton)按下是左键
        //鼠标移动事件需要移动窗口，窗口移动到哪里呢？就是要获取鼠标移动中，窗口在整个屏幕的坐标，然后move到这个坐标，怎么获取坐标？
        //通过事件event->globalPos()知道鼠标坐标，鼠标坐标减去鼠标相对于窗口位置，就是窗口在整个屏幕的坐标
        if (m_moving && (event->buttons() && Qt::LeftButton)
            && (event->globalPos()-m_lastPos).manhattanLength() > QApplication::startDragDistance())
        {
            move(event->globalPos()-m_lastPos);
            m_lastPos = event->globalPos() - pos();
        }
}

void StartWindow::mouseReleaseEvent(QMouseEvent *event)
{
     m_moving=false; //停止移动
}



void StartWindow::on_btndef_clicked()
{
    setWindowState(Qt::WindowMinimized);
}

void StartWindow::on_time_timout()
{

    DisplayWindow *dis=new DisplayWindow();
    setVisible(0);
    time->stop();
    time1->stop();
    dis->setWindowFlag(Qt::SplashScreen);
    dis->show();



    this->close();


}

void StartWindow::on_time1_timout()
{
    if(ui->labMovie->geometry().x()==30 && ui->labMovie->width() !=550)
    {
        ui->labMovie->resize(ui->labMovie->width()+1,ui->labMovie->height());

    }
    else if (ui->labMovie->geometry().x()==30 && ui->labMovie->width() ==550) {
        ui->labMovie->resize(ui->labMovie->width()-2,ui->labMovie->height());
        ui->labMovie->move(ui->labMovie->geometry().x()+1,ui->labMovie->geometry().y());
    }
    else if(ui->labMovie->geometry().x()==580 && ui->labMovie->width()==0)
    {
        ui->labMovie->setGeometry(30,ui->labMovie->geometry().y(),0,ui->labMovie->height());
        state++;
        if (state==3)
        {
            DisplayWindow *dis=new DisplayWindow(this);
            setVisible(0);
            time->stop();
            time1->stop();
            //dis->setWindowFlag(Qt::SplashScreen);
            dis->show();
        }
    }
    else if (ui->labMovie->geometry().x()!=30 && ui->labMovie->width() !=550) {
             ui->labMovie->resize(ui->labMovie->width()-1,ui->labMovie->height());
             ui->labMovie->move(ui->labMovie->geometry().x()+1,ui->labMovie->geometry().y());
    }


}
