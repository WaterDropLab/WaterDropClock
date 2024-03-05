#ifndef DISPLAYWINDOW_H
#define DISPLAYWINDOW_H
#define ME DisplayWindow
#include <QDialog>
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QSettings>
#include <QTimer>
#include <QTime>
#include <QSystemTrayIcon>
#include <reportthread.h>
#include <QGraphicsBlurEffect>
#include <QGraphicsPixmapItem>
#include <QPaintEvent>
#include <QPainter>



#include <QDesktopWidget>
#include <QEvent>
#include <QPropertyAnimation>
#include <qscreen.h>
namespace Ui {
class DisplayWindow;
}

class DisplayWindow : public QDialog
{
    Q_OBJECT
protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

public:
    explicit DisplayWindow(QWidget *parent = nullptr);
    ~DisplayWindow();
    bool SetVolumeLevel(int level);
    void  noMute();
QSystemTrayIcon *tray;
    void iniSettings();
    QSettings set;
    QPoint  m_lastPos;  //上一次的鼠标位置
    QTimer *tmChange;
    QTimer *tmReport;
    reportthread *report;
    int  state;
    bool MySystemShutDown();
    bool MySystemReboot();
    bool SysShut();
    bool SysReboot();
    bool sysLogout();
    bool sysLogoutForce();
    QString lastTime;
     QPropertyAnimation *m_animation;

public slots:
void active(QSystemTrayIcon::ActivationReason r);
    void on_tmChange_timout();
    void on_tmReport_timout();

private slots:
    void on_btnMenu_clicked();

    void on_actExit_triggered();

    void on_actShutdown_triggered();

    void on_actRebbot_triggered();

    void on_actNoForceShutdown_triggered();

    void on_actNoForceReboot_triggered();

    void on_actDisplay_triggered(bool checked);

    void on_actLogout_triggered();

    void on_actForceLogout_triggered();

private:
    Ui::DisplayWindow *ui;
    QColor bgColor;
    bool isBlur;
    bool    m_moving=false;//表示窗口是否在鼠标操作下移动

};

#endif // DISPLAYWINDOW_H
