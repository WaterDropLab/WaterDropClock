#include "aboutme.h"
#include "ui_aboutme.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDesktopServices>
AboutMe::AboutMe(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutMe)
{
    ui->setupUi(this);
    ui->pic->setScaledContents(1);
    this->setAttribute(Qt::WA_TranslucentBackground);//设置窗口背景透明
    this->setWindowFlags
    (this->windowFlags()|Qt::FramelessWindowHint);
}

AboutMe::~AboutMe()
{
    delete ui;
}

void AboutMe::on_btndef_2_clicked()
{
    close();
}
void AboutMe::paintEvent(QPaintEvent *event)
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

void AboutMe::mousePressEvent(QMouseEvent *event)
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

void AboutMe::mouseMoveEvent(QMouseEvent *event)
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

void AboutMe::mouseReleaseEvent(QMouseEvent *event)
{
 m_moving=false; //停止移动

}

void AboutMe::on_btndef_3_clicked()
{
    QDesktopServices::openUrl(QUrl(QLatin1String("https://github.com/WaterDropLab")));
}

void AboutMe::on_btndef_4_clicked()
{
    QDesktopServices::openUrl(QUrl(QLatin1String("https://github.com/WaterDropLab/WaterDropClock")));
}
