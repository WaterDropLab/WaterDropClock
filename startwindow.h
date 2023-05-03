#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QDialog>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class StartWindow; }
QT_END_NAMESPACE

class StartWindow : public QDialog
{
    Q_OBJECT

public:
    StartWindow(QWidget *parent = nullptr);

    ~StartWindow();
    QTimer *time;
    QTimer *time1;
    int  state;
protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private slots:
    void on_btndef_clicked();
        void on_time_timout();
        void on_time1_timout();

private:
    Ui::StartWindow *ui;
    bool    m_moving=false;//表示窗口是否在鼠标操作下移动
    QPoint  m_lastPos;  //上一次的鼠标位置

};
#endif // STARTWINDOW_H
