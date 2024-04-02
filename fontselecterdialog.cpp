#include "fontselecterdialog.h"
#include "ui_fontselecterdialog.h"
#include <QPaintEvent>
#include <QSettings>
#include <QFont>
#include <QFontDialog>
fontSelecterDialog::fontSelecterDialog(QFont font,QString title,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::fontSelecterDialog)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_TranslucentBackground);//设置窗口背景透明
    this->setWindowFlags
    (this->windowFlags()|Qt::FramelessWindowHint);
    cfont=font;
    reStr=title;
    ui->txtTitle1->setText(title);
    ui->labTitle->setText(reStr);
    ui->labTitle->setFont(cfont);
    ui->label->setScaledContents(1);
}

fontSelecterDialog::~fontSelecterDialog()
{
    delete ui;
}


void fontSelecterDialog::paintEvent(QPaintEvent *event)
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

void fontSelecterDialog::mousePressEvent(QMouseEvent *event)
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

void fontSelecterDialog::mouseMoveEvent(QMouseEvent *event)
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

void fontSelecterDialog::mouseReleaseEvent(QMouseEvent *event)
{
 m_moving=false; //停止移动

}

void fontSelecterDialog::closeEvent(QCloseEvent *event)
{



}
void fontSelecterDialog::on_btndef_clicked()
{
    reject();

}

void fontSelecterDialog::on_txtTitle1_textChanged(const QString &arg1)
{
    ui->labTitle->setText(arg1);
    reStr=arg1;
}

void fontSelecterDialog::on_btnSelect_clicked()
{

    bool ok;
    QFont font;
      font = QFontDialog::getFont(&ok, cfont, this);
      if (ok) {
          cfont=font;
          ui->labTitle->setFont(cfont);
      }


}

void fontSelecterDialog::on_pushButton_2_clicked()
{
    reject();
}

void fontSelecterDialog::on_pushButton_clicked()
{
    accept();
}
