#if _MSC_VER >=1600
#pragma execution_character_set("utf-8")
#endif
#ifndef ABOUTME_H
#define ABOUTME_H
#include "parfontselector.h"
#include "ui_parfontselector.h"
#include <QFontDialog>
parFontSelector::parFontSelector(QFont font,QString content,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::parFontSelector)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_TranslucentBackground);//设置窗口背景透明
    this->setWindowFlags
    (this->windowFlags()|Qt::FramelessWindowHint);
     ui->label->setScaledContents(1);
     reStr=content;
     cfont=font;
     ui->txtTitle1->setPlainText(content);
     ui->labTitle->setText(reStr);
     ui->labTitle->setFont(cfont);

}

parFontSelector::~parFontSelector()
{
    delete ui;
}
void parFontSelector::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    QColor color;
    color.setRgb(97,97,97);
    QPen pen;
    pen.setWidth(2);
    QColor penColor;
    penColor.setRgb(80,80,80);
    pen.setColor(penColor);
       painter.setRenderHint(QPainter::Antialiasing); // 设置抗锯齿，不然边框会有明显锯齿
       painter.setBrush(color);                   // 设置窗体颜色
       QRect rect = this->rect();
    painter.setPen(pen);

       painter.drawRoundedRect(rect,10,10);

}

void parFontSelector::mousePressEvent(QMouseEvent *event)
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

void parFontSelector::mouseMoveEvent(QMouseEvent *event)
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

void parFontSelector::mouseReleaseEvent(QMouseEvent *event)
{
 m_moving=false; //停止移动

}



void parFontSelector::on_btndef_clicked()
{
    reject();

}

void parFontSelector::on_txtTitle1_textChanged(const QString &arg1)
{

}

void parFontSelector::on_btnSelect_clicked()
{

    bool ok;
    QFont font;
      font = QFontDialog::getFont(&ok, cfont, this);
      if (ok) {
          cfont=font;
          ui->labTitle->setFont(cfont);
      }


}

void parFontSelector::on_pushButton_2_clicked()
{
    reject();
}

void parFontSelector::on_pushButton_clicked()
{
    accept();
}


void parFontSelector::on_txtTitle1_textChanged()
{
    ui->labTitle->setText(ui->txtTitle1->toPlainText());
    reStr=ui->txtTitle1->toPlainText();
}
