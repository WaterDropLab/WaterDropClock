#include "configwindow.h"
#include "ui_configwindow.h"
#include <QPaintEvent>
#include <QSettings>
#include <QFont>
#include "fontselecterdialog.h"
#include "parfontselector.h"
#include <QtTextToSpeech>
#include <QVoice>
#include <QTime>
#include <QCoreApplication>
#include <QDir>

ConfigWindow::ConfigWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigWindow)
{
    ui->setupUi(this);
    sound=new QSoundEffect;

    sound->setSource(QUrl::fromLocalFile(":/wav/res/DingDong.wav"));
    report=new reportthread;
    connect(report,&reportthread::reportStopped,this,&ConfigWindow::speechEnded);
   settings=new QSettings("WaterDropLab","WaterDropClock");
    ui->pic->setScaledContents(1);

    this->setAttribute(Qt::WA_TranslucentBackground);//设置窗口背景透明

    this->setWindowFlags
    (this->windowFlags()|Qt::FramelessWindowHint);

    iniSettings();
    on_tabDisplay_clicked();
    ui->tabDisplay->setFocus();
    //设置动画效果
/*
    QPropertyAnimation *hoverAnimation=new QPropertyAnimation(ui->test, "geometry");
       hoverAnimation->setDuration(200);
       hoverAnimation->setStartValue(ui->btnEdit1->geometry());
       hoverAnimation->setEndValue(ui->test->geometry().adjusted(-10, -10, 10, 10));

       QPropertyAnimation *pressAnimation=new QPropertyAnimation(ui->test, "geometry");
       pressAnimation->setDuration(100);
       pressAnimation->setStartValue(hoverAnimation->endValue());
       pressAnimation->setEndValue(hoverAnimation->startValue());

       QSequentialAnimationGroup *buttonAnimation=new QSequentialAnimationGroup;
       buttonAnimation->addAnimation(hoverAnimation);
       buttonAnimation->addAnimation(pressAnimation);
*/
      }

ConfigWindow::~ConfigWindow()
{
    delete ui;
}

void ConfigWindow::iniSettings()
{
    QSettings *settings=new QSettings("WaterDropLab","WaterDropClock");
    //对于主标题

{
        QDate dateTarget=dateTarget.fromString(settings->value("Display/Section1/TargetDate",QDate::currentDate().toString("yyyy-MM-dd")).toString(),"yyyy-MM-dd");

         QFont font;
         font.setPointSize(settings->value("Display/Section1/FontSize",36).toInt());
         font.setFamily(settings->value("Display/Section1/FontName","幼圆").toString());
         mainFont=font;
         ui->date1->setDate(dateTarget);
         ui->spinInterval1->setValue(settings->value("Display/Section1/Interval",5).toInt());
         ui->txtTitle1->setText(settings->value("Display/Section1/Title","标题1未命名").toString());
         ui->spinInterval1->setValue(settings->value("Display/Section1/Interval",5).toInt());
    if(settings->value("Display/Section1/Enabled",1).toBool())
    {
        ui->txtTitle1->setEnabled(1);
        ui->date1->setEnabled(1);
        ui->spinInterval1->setEnabled(1);
        ui->chk1->setChecked(1);
        ui->btnEdit1->setEnabled(1);

    }
    else {
        ui->txtTitle1->setEnabled(0);
        ui->date1->setEnabled(0);
        ui->spinInterval1->setEnabled(0);
                ui->chk1->setChecked(0);
                ui->btnEdit1->setEnabled(0);
    }





}


    //对于副标题

    {
            QDate dateTarget=dateTarget.fromString(settings->value("Display/Section2/TargetDate",QDate::currentDate().toString("yyyy-MM-dd")).toString(),"yyyy-MM-dd");

             QFont font;
             font.setPointSize(settings->value("Display/Section2/FontSize",36).toInt());
             font.setFamily(settings->value("Display/Section2/FontName","幼圆").toString());
             subFont=font;
             ui->date2->setDate(dateTarget);
             ui->spinInterval2->setValue(settings->value("Display/Section2/Interval",5).toInt());
             ui->txtTitle2->setText(settings->value("Display/Section2/Title","标题2未命名").toString());
             ui->spinInterval2->setValue(settings->value("Display/Section2/Interval",5).toInt());
             if(settings->value("Display/Section2/Enabled",1).toBool())
        {
            ui->txtTitle2->setEnabled(1);
            ui->date2->setEnabled(1);
            ui->spinInterval2->setEnabled(1);
            ui->chk2->setChecked(1);
            ui->btnEdit2->setEnabled(1);
        }
        else {
            ui->txtTitle2->setEnabled(0);
            ui->date2->setEnabled(0);
            ui->spinInterval2->setEnabled(0);
                    ui->chk2->setChecked(0);
                    ui->btnEdit2->setEnabled(0);
        }

    }

//对于段落

{
        QFont font;
        font.setPointSize(settings->value("Display/Paragraph/FontSize",36).toInt());
        font.setFamily(settings->value("Display/Paragraph/FontName","幼圆").toString());
        ui->spinInterval3->setValue(settings->value("Display/Paragraph/Interval",5).toInt());
        parFont=font;
        ui->txtParagraph->setPlainText(settings->value("Display/Paragraph/Content","无内容").toString());
        ui->spinInterval3->setValue(settings->value("Display/Paragraph/Interval",5).toInt());
        if(settings->value("Display/Paragraph/Enabled",1).toBool())
       {

         ui->txtParagraph->setEnabled(1);
         ui->chk3->setChecked(1);
          ui->spinInterval3->setEnabled(1);
          ui->btnEditPar->setEnabled(1);

       }
        else
        {
            ui->txtParagraph->setEnabled(0);
            ui->chk3->setChecked(0);
             ui->spinInterval3->setEnabled(0);
             ui->btnEditPar->setEnabled(0);
        }
    }
//对于播报
    m_speech=new QTextToSpeech;
    ui->runChk_2->setChecked(settings->value("Report/ForceRegulateSystemVolume",0).toBool());
    ui->spnVolSys->setEnabled(settings->value("Report/ForceRegulateSystemVolume",0).toBool());
    ui->spnVolSys->setValue(settings->value("Report/SystemVolume",50).toInt());

    ui->sliVol->setValue(settings->value("Report/Volume",10).toInt());
    ui->sliRate->setValue(settings->value("Report/Rate",0).toInt());
    QTime time=time.fromString(settings->value("Report/Time","07:30:00").toString(),"HH:mm:ss");
    ui->timRe->setTime(time);
    if (settings->value("Report/Enabled",1).toBool())
    {
        on_rechk_clicked(1);

        ui->rechk->setChecked(1);

    }
    else{
        on_rechk_clicked(0);
        ui->rechk->setChecked(0);
    }
//对于播报的时间1
    {
        QDate dateTarget=dateTarget.fromString(settings->value("Report/Section1/TargetDate",QDate::currentDate().toString("yyyy-MM-dd")).toString(),"yyyy-MM-dd");

         ui->redate1->setDate(dateTarget);

         ui->retxtTitle1->setText(settings->value("Report/Section1/Title","标题1未命名").toString());

    if(settings->value("Report/Section1/Enabled",1).toBool())
    {
        ui->retxtTitle1->setEnabled(1);
        ui->redate1->setEnabled(1);

        ui->rechk1->setChecked(1);

    }
    else {
        ui->retxtTitle1->setEnabled(0);
        ui->redate1->setEnabled(0);

        ui->rechk1->setChecked(0);

    }
  }
//对于播报的时间2
    {
        QDate dateTarget=dateTarget.fromString(settings->value("Report/Section2/TargetDate",QDate::currentDate().toString("yyyy-MM-dd")).toString(),"yyyy-MM-dd");

         ui->redate2->setDate(dateTarget);

         ui->retxtTitle2->setText(settings->value("Report/Section2/Title","标题2未命名").toString());

    if(settings->value("Report/Section2/Enabled",1).toBool())
    {
        ui->retxtTitle2->setEnabled(1);
        ui->redate2->setEnabled(1);

        ui->rechk2->setChecked(1);

    }
    else {
        ui->retxtTitle2->setEnabled(0);
        ui->redate2->setEnabled(0);

        ui->rechk2->setChecked(0);

    }
    }
//对于播报的段落
    {

        ui->retxtParagraph->setPlainText(settings->value("Report/Paragraph/Content","无内容").toString());

        if(settings->value("Report/Paragraph/Enabled",1).toBool())
       {

         ui->retxtParagraph->setEnabled(1);
         ui->rechk3->setChecked(1);



       }
        else
        {
            ui->retxtParagraph->setEnabled(0);
            ui->rechk3->setChecked(0);
        }
    }
//For Autorun
    QSettings run("Microsoft","Windows");
            //CurrentVersion\Run
    if(settings->value("Autorun",1).toBool()){

        ui->runChk->setChecked(1);
        run.setValue("CurrentVersion/Run/水滴时钟",QDir::toNativeSeparators(QCoreApplication::applicationFilePath()));
    }
    else {
        ui->runChk->setChecked(0);
        run.setValue("CurrentVersion/Run/水滴时钟","");
    }

ui->frame->setVisible(0);

}
void ConfigWindow::paintEvent(QPaintEvent *event)
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
       painter.drawRoundedRect(rect,10,10);

}

void ConfigWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_moving = true;

        //记录下鼠标相对于窗口的位置
        //event->globalPos()鼠标按下时，鼠标相对于整个屏幕位置
        //pos() this->pos()鼠标按下时，窗口相对于整个屏幕位置
        m_lastPos = event->globalPos() - pos();
    }

}

void ConfigWindow::mouseMoveEvent(QMouseEvent *event)
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

void ConfigWindow::mouseReleaseEvent(QMouseEvent *event)
{
 m_moving=false; //停止移动

}

void ConfigWindow::on_btndef_2_clicked()
{
  close();
}

void ConfigWindow::on_btndef_clicked()
{

}



void ConfigWindow::on_tabDisplay_clicked()
{

 ui->tabDisplay->setStyleSheet("#tabDisplay{background-color:rgb(80,80, 80);border: 0px solid rgb(97, 97,97);}");
 ui->tabReport->setStyleSheet("#tabReport{background-color:rgb(97, 97,97);border: 0px solid rgb(97, 97,97);}");
 ui->tabOthers->setStyleSheet("#tabOthers{background-color:rgb(97, 97,97);border: 0px solid rgb(97, 97,97);}");
ui->staMain->setCurrentIndex(0);
}

void ConfigWindow::on_tabReport_clicked()
{
    ui->tabDisplay->setStyleSheet("#tabDisplay{background-color:rgb(97, 97,97);border: 0px solid rgb(97, 97,97);}");
    ui->tabReport->setStyleSheet("#tabReport{background-color:rgb(80,80, 80);border: 0px solid rgb(97, 97,97);}");
    ui->tabOthers->setStyleSheet("#tabOthers{background-color:rgb(97, 97,97);border: 0px solid rgb(97, 97,97);}");
ui->staMain->setCurrentIndex(1);
}

void ConfigWindow::on_tabOthers_clicked()
{
    ui->tabDisplay->setStyleSheet("#tabDisplay{background-color:rgb(97, 97,97);border: 0px solid rgb(97, 97,97);}");
    ui->tabReport->setStyleSheet("#tabReport{background-color:rgb(97, 97,97);border: 0px solid rgb(97, 97,97);}");
    ui->tabOthers->setStyleSheet("#tabOthers{background-color:rgb(80,80, 80);border: 0px solid rgb(97, 97,97);}");
ui->staMain->setCurrentIndex(2);
}



void ConfigWindow::on_chk1_clicked(bool checked)
{
    if(checked)
    {
        ui->txtTitle1->setEnabled(1);
        ui->date1->setEnabled(1);
        ui->spinInterval1->setEnabled(1);
        ui->chk1->setChecked(1);
        ui->btnEdit1->setEnabled(1);

    }
    else
    {
        ui->txtTitle1->setEnabled(0);
        ui->date1->setEnabled(0);
        ui->spinInterval1->setEnabled(0);
        ui->chk1->setChecked(0);
         ui->btnEdit1->setEnabled(0);
    }
    settings->setValue("Display/Section1/Enabled",checked);
}

void ConfigWindow::on_chk2_clicked(bool checked)
{
    if(checked)
    {
        ui->txtTitle2->setEnabled(1);
        ui->date2->setEnabled(1);
        ui->spinInterval2->setEnabled(1);
        ui->chk2->setChecked(1);
         ui->btnEdit2->setEnabled(1);
    }
    else
    {
        ui->txtTitle2->setEnabled(0);
        ui->date2->setEnabled(0);
        ui->spinInterval2->setEnabled(0);
        ui->chk2->setChecked(0);
         ui->btnEdit2->setEnabled(0);
    }
     settings->setValue("Display/Section2/Enabled",checked);
}

void ConfigWindow::on_chk3_clicked(bool checked)
{
    if(checked)
    {
        ui->txtParagraph->setEnabled(1);
        ui->chk3->setChecked(1);
         ui->spinInterval3->setEnabled(1);
         ui->btnEditPar->setEnabled(1);

    }
    else
    {
        ui->txtParagraph->setEnabled(0);
        ui->chk3->setChecked(0);
         ui->spinInterval3->setEnabled(0);
         ui->btnEditPar->setEnabled(0);

    }
    settings->setValue("Display/Paragraph/Enabled",checked);
}

void ConfigWindow::on_txtTitle1_textChanged(const QString &arg1)
{
    settings->setValue("Display/Section1/Title",ui->txtTitle1->text());

}

void ConfigWindow::on_txtTitle2_textChanged(const QString &arg1)
{
    settings->setValue("Display/Section2/Title",ui->txtTitle2->text());
}

void ConfigWindow::on_txtParagraph_textChanged()
{
    settings->setValue("Display/Paragraph/Content",ui->txtParagraph->toPlainText());
}

void ConfigWindow::on_spinInterval1_valueChanged(int arg1)
{
     settings->setValue("Display/Section1/Interval",arg1);

}

void ConfigWindow::on_spinInterval2_valueChanged(int arg1)
{
    settings->setValue("Display/Section2/Interval",arg1);
}

void ConfigWindow::on_spinInterval3_valueChanged(int arg1)
{
    settings->setValue("Display/Paragraph/Interval",arg1);
}

void ConfigWindow::on_date1_userDateChanged(const QDate &date)
{
    settings->setValue("Display/Section1/TargetDate",date.toString("yyyy-MM-dd"));
}

void ConfigWindow::on_date2_userDateChanged(const QDate &date)
{
     settings->setValue("Display/Section2/TargetDate",date.toString("yyyy-MM-dd"));
}

void ConfigWindow::on_btnEdit1_clicked()
{
    fontSelecterDialog *fo=new fontSelecterDialog(mainFont,ui->txtTitle1->text(),this);
    fo->setStyleSheet("");
    if(fo->exec()==QDialog::Accepted)
    {



        settings->setValue("Display/Section1/FontName",fo->cfont.family());
         settings->setValue("Display/Section1/FontSize",fo->cfont.pointSize());
         ui->txtTitle1->setText(fo->reStr);
         mainFont=fo->cfont;
    }
    delete fo;

}

void ConfigWindow::on_btnEdit2_clicked()
{
    fontSelecterDialog *fot=new fontSelecterDialog(subFont,ui->txtTitle2->text(),this);
    if(fot->exec()==QDialog::Accepted)
    {



        settings->setValue("Display/Section2/FontName",fot->cfont.family());
         settings->setValue("Display/Section2/FontSize",fot->cfont.pointSize());
         ui->txtTitle2->setText(fot->reStr);
         subFont=fot->cfont;}
    delete fot;
}

void ConfigWindow::on_btnEditPar_clicked()
{

    parFontSelector *fo1=new parFontSelector(parFont,ui->txtParagraph->toPlainText(),this);
    fo1->setStyleSheet("");
    if(fo1->exec()==QDialog::Accepted)
    {



        settings->setValue("Display/Paragraph/FontName",fo1->cfont.family());
         settings->setValue("Display/Paragraph/FontSize",fo1->cfont.pointSize());
         ui->txtParagraph->setPlainText(fo1->reStr);
         parFont=fo1->cfont;
    }
    delete fo1;
}

void ConfigWindow::on_rechk1_clicked(bool checked)
{
    if(checked)
    {
         ui->rechk1->setChecked(1);
        ui->retxtTitle1->setEnabled(1);
        ui->redate1->setEnabled(1);

    }
    else
    {
         ui->rechk1->setChecked(0);
        ui->retxtTitle1->setEnabled(0);
        ui->redate1->setEnabled(0);

    }
    settings->setValue("Report/Section1/Enabled",checked);
}

void ConfigWindow::on_rechk2_clicked(bool checked)
{
    if(checked)
    {
         ui->rechk2->setChecked(1);
        ui->retxtTitle2->setEnabled(1);
        ui->redate2->setEnabled(1);


    }
    else
    {
         ui->rechk2->setChecked(0);
        ui->retxtTitle2->setEnabled(0);
        ui->redate2->setEnabled(0);

    }
    settings->setValue("Report/Section2/Enabled",checked);
}

void ConfigWindow::on_rechk3_clicked(bool checked)
{
    if(checked)
    {
         ui->rechk3->setChecked(1);
        ui->retxtParagraph->setEnabled(1);


    }
    else
    {
         ui->rechk3->setChecked(0);
       ui->retxtParagraph->setEnabled(0);

    }
    settings->setValue("Report/Paragraph/Enabled",checked);
}

void ConfigWindow::on_rechk_clicked(bool checked)
{
    if(checked)
    {

       ui->retxtTitle1->setEnabled(1);
       ui->redate1->setEnabled(1);
      ui->rechk2->setEnabled(1);
      ui->rechk1->setEnabled(1);
      ui->rechk3->setEnabled(1);
      ui->retxtTitle2->setEnabled(1);
      ui->redate2->setEnabled(1);
        ui->timRe->setEnabled(1);
        ui->retxtParagraph->setEnabled(1);
        ui->sliVol->setEnabled(1);
        ui->sliRate->setEnabled(1);
        ui->bthListen->setEnabled(1);

    }
    else
    {

       ui->retxtTitle1->setEnabled(0);
       ui->redate1->setEnabled(0);
       ui->rechk2->setEnabled(0);
       ui->rechk1->setEnabled(0);
       ui->rechk3->setEnabled(0);
      ui->retxtTitle2->setEnabled(0);
      ui->redate2->setEnabled(0);
       ui->timRe->setEnabled(0);
        ui->retxtParagraph->setEnabled(0);
        ui->sliVol->setEnabled(0);
        ui->sliRate->setEnabled(0);
        ui->bthListen->setEnabled(0);
    }
    settings->setValue("Report/Enabled",checked);
}

void ConfigWindow::on_timRe_userTimeChanged(const QTime &time)
{
    settings->setValue("Report/Time",time.toString("HH:mm:ss"));
}

void ConfigWindow::on_sliVol_sliderMoved(int position)
{
    settings->setValue("Report/Volume",position);
}

void ConfigWindow::on_sliRate_sliderMoved(int position)
{
    settings->setValue("Report/Rate",position);
}

void ConfigWindow::on_retxtTitle1_textChanged(const QString &arg1)
{
     settings->setValue("Report/Section1/Title",arg1);
}

void ConfigWindow::on_retxtTitle2_cursorPositionChanged(int arg1, int arg2)
{

}

void ConfigWindow::on_retxtParagraph_textChanged()
{
      settings->setValue("Report/Paragraph/Content",ui->retxtParagraph->toPlainText());
}

void ConfigWindow::on_retxtTitle2_textChanged(const QString &arg1)
{
    settings->setValue("Report/Section2/Title",arg1);
}

void ConfigWindow::on_redate1_dateChanged(const QDate &date)
{
    settings->setValue("Report/Section1/TargetDate",date.toString("yyyy-MM-dd"));
}

void ConfigWindow::on_redate2_dateChanged(const QDate &date)
{
     settings->setValue("Report/Section2/TargetDate",date.toString("yyyy-MM-dd"));
}

void ConfigWindow::on_bthListen_clicked(bool checked)
{
    if(checked)
    {
    ui->bthListen->setText("停止(&S)");
    startSpeak();
 // report->start();
 //connect(sound,&QSoundEffect::statusChanged,this,&ConfigWindow::soundStopped);
     //sound->play();


    }
    else
    {
        ui->bthListen->setText("试听(&L)");
        //report->speechStop();
        m_speech->stop();
        disconnect(m_speech,&QTextToSpeech::stateChanged,this,&ConfigWindow::speechEnded);
    }




}

void ConfigWindow::soundStopped()
{

        startSpeak();

}

void ConfigWindow::startSpeak()
{
    connect(m_speech,&QTextToSpeech::stateChanged,this,&ConfigWindow::speechEnded);
    m_speech->setRate(settings->value("Report/Rate",0).toInt()/10.0);
     m_speech->setVolume(settings->value("Report/Volume",10).toInt()/10.0);



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
    if(days1>=0 && settings->value("Report/Section1/Enabled",1).toBool())
    {
        content1="距离"+title1+"仅有，"+QString::number(days1)+"天，";
        a=1;
    }
    if(days2>=0 && settings->value("Report/Section2/Enabled",1).toBool())
    {
        content2="距离"+title2+"仅有，"+QString::number(days2)+"天。";
        a=1;
    }
     if(a==0 || settings->value("Report/Paragraph/Enabled",1).toBool())
     {
         conPar=settings->value("Report/Paragraph/Content","无内容").toString();
     }
     m_speech->say("今日播报：同学们，"+content1+content2+conPar);
}

void ConfigWindow::speechEnded()


{
    if(m_speech->state()==QTextToSpeech::Ready){
    ui->bthListen->setText("试听(&L)");
    ui->bthListen->setChecked(0);
    disconnect(m_speech,&QTextToSpeech::stateChanged,this,&ConfigWindow::speechEnded);}
}

void ConfigWindow::on_runChk_clicked(bool checked)
{
    QSettings run("Microsoft","Windows");
            //CurrentVersion\Run
    if(checked){

        settings->setValue("Autorun",1);
        run.setValue("CurrentVersion/Run/水滴时钟",QDir::toNativeSeparators(QCoreApplication::applicationFilePath()));
    }
    else {
        settings->setValue("Autorun",0);
        run.setValue("CurrentVersion/Run/水滴时钟","");
    }
}

void ConfigWindow::on_runChk_2_clicked(bool checked)
{

        ui->spnVolSys->setEnabled(checked);
        settings->setValue("Report/ForceRegulateSystemVolume",checked);

}

void ConfigWindow::on_spnVolSys_valueChanged(int arg1)
{
    settings->setValue("Report/SystemVolume",arg1);
}
