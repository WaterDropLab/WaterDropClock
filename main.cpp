#if _MSC_VER >=1600
#pragma execution_character_set("utf-8")
#endif
#ifndef ABOUTME_H
#define ABOUTME_H
#include "startwindow.h"
#include <QFile>
#include <QApplication>
#include <QSettings>
#include <QDir>
#include <QCoreApplication>
int main(int argc, char *argv[])
{
    QApplication *a=new QApplication(argc, argv);
    a->setQuitOnLastWindowClosed(0);
//    QApplication *app=new QApplication(argc, argv);
    QSettings *settings=new QSettings("WaterDropLab","WaterDropClock");
    int *type=new int;
    *type=settings->value("Theme/Type",1).toInt()==1;
    if(*type==1)
    {
            QFile file(":/qss/blacktheme.qss");
            QString str;

            file.open(QFile::ReadOnly);
           str=QString::fromLatin1(file.readAll());
                a->setStyleSheet(str);

    }

    QSettings run("Microsoft","Windows");
            //CurrentVersion\Run
    if(settings->value("Autorun",1).toBool()){


        run.setValue("CurrentVersion/Run/水滴时钟",QDir::toNativeSeparators(QCoreApplication::applicationFilePath()));
    }
    else {

        run.setValue("CurrentVersion/Run/水滴时钟","");
    }

    delete settings;
    delete type;
    StartWindow w;
    w.show();
    return a->exec();
}
