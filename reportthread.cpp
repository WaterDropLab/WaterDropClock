#if _MSC_VER >=1600
#pragma execution_character_set("utf-8")
#endif
#ifndef ABOUTME_H
#define ABOUTME_H
#include "reportthread.h"
#include <QTextToSpeech>
#include <QSettings>
#include <QDate>
#include <qdebug.h>
reportthread::reportthread()
{


    settings=new QSettings("WaterDropLab","WaterDropClock");



}

void reportthread::speechStop()
{
    speech->stop();
}

void reportthread::run()
{
    msleep(5000);
    speech=new  QTextToSpeech;
    speech->setRate(settings->value("Report/Rate",0).toInt()/10.0);
     speech->setVolume(settings->value("Report/Volume",10).toInt()/10.0);


    if(!settings->value("Report/Enabled",1).toBool())
    {
        quit();
    }
    QDate dateTarget1=dateTarget1.fromString(settings->value("Report/Section1/TargetDate",QDate::currentDate().toString("yyyy-MM-dd")).toString(),"yyyy-MM-dd");
    QDate dateTarget2=dateTarget2.fromString(settings->value("Report/Section2/TargetDate",QDate::currentDate().toString("yyyy-MM-dd")).toString(),"yyyy-MM-dd");
    QString title1=settings->value("Report/Section1/Title","标题1未命名").toString();
    QString title2=settings->value("Report/Section2/Title","标题2未命名").toString();
    QString content1="";
    QString content2="";
    QString conPar="";
    bool a=0;
    int days1=QDate::currentDate().daysTo(dateTarget1);
    int days2=QDate::currentDate().daysTo(dateTarget2);
    if(days1>0 && settings->value("Report/Section1/Enabled",1).toBool())
    {
        content1="距离"+title1+"仅有，"+QString::number(days1)+"天，";
        a=1;
    }
    if(days2>0 && settings->value("Report/Section2/Enabled",1).toBool())
    {
        content2="距离"+title2+"仅有，"+QString::number(days2)+"天。";
        a=1;
    }
     if(a==0 || settings->value("Report/Paragraph/Enabled",1).toBool())
     {
         conPar=settings->value("Report/Paragraph/Content","无内容").toString();
     }
     speech->say("今日播报：同学们，"+content1+content2+conPar);
     //connect(speech,&QTextToSpeech::stateChanged,this,&reportthread::stateChanged);
        connect(speech,SIGNAL(stateChanged(QTextToSpeech::State)),this,SLOT(stateChanged(QTextToSpeech::State)),Qt::BlockingQueuedConnection);

}

void reportthread::stateChanged(QTextToSpeech::State state)
{

    emit reportStopped();
}
