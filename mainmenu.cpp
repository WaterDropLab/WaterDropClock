#if _MSC_VER >=1600
#pragma execution_character_set("utf-8")
#endif
#ifndef ABOUTME_H
#define ABOUTME_H
#include "mainmenu.h"
#include "ui_mainmenu.h"
#include <QPaintEvent>
#include <QPainter>
#include <configwindow.h>
#include <aboutme.h>
#include <QDesktopServices>
MainMenu::MainMenu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainMenu)
{
    this->setAttribute(Qt::WA_TranslucentBackground);//设置窗口背景透明
        this->setWindowFlags(Qt::FramelessWindowHint|Qt::Popup);
    ui->setupUi(this);
}

void MainMenu::paintEvent(QPaintEvent *event)
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
MainMenu::~MainMenu()
{
    delete ui;
}

void MainMenu::on_btnExit_clicked()
{
    QApplication* app;
    app->exit(0);
}

void MainMenu::on_btnSetting_clicked()
{
    ConfigWindow *con=new ConfigWindow();
    con->setAttribute(Qt::WA_DeleteOnClose);
   con->show();

}

void MainMenu::on_btnAbout_clicked()
{
   AboutMe *m =new AboutMe();

   m->show();
}

void MainMenu::on_btnAboutUs_clicked()
{
   QDesktopServices::openUrl(QUrl(QLatin1String("https://github.com/WaterDropLab/About-us/blob/main/README.md#about-us")));
   close();
}

void MainMenu::on_btnUpDate_clicked()
{
    QDesktopServices::openUrl(QUrl(QLatin1String("https://github.com/WaterDropLab/WaterDropClock/releases")));
    close();
}
