#if _MSC_VER >=1600
#pragma execution_character_set("utf-8")
#endif
#ifndef ABOUTME_H
#define ABOUTME_H
#include "displaywindow.h"
#include "ui_displaywindow.h"
#include <QPaintEvent>
#include <QDate>
#include <QMessageBox>
#include <mainmenu.h>
#include <QSound>
#include <reportthread.h>
#include <QSystemTrayIcon>
#include <QMenu>
#include <Windows.h>
#include <mmdeviceapi.h>
#include <endpointvolume.h>
#include <audioclient.h>
#include <winuser.h>
//#include <combaseapi.h>
//#include <ks.h>
#include <QAxBase>
enum AccentState
{
        ACCENT_DISABLED = 0,
        ACCENT_ENABLE_GRADIENT = 1,
        ACCENT_ENABLE_TRANSPARENTGRADIENT = 2,
        ACCENT_ENABLE_BLURBEHIND = 3,
        ACCENT_INVALID_STATE = 4
};
struct AccentPolicy
{
        AccentState AccentState;
        int AccentFlags;
        int GradientColor;
        int AnimationId;
};
enum WindowCompositionAttribute
{
        WCA_UNDEFINED = 0,
        WCA_NCRENDERING_ENABLED = 1,
        WCA_NCRENDERING_POLICY = 2,
        WCA_TRANSITIONS_FORCEDISABLED = 3,
        WCA_ALLOW_NCPAINT = 4,
        WCA_CAPTION_BUTTON_BOUNDS = 5,
        WCA_NONCLIENT_RTL_LAYOUT = 6,
        WCA_FORCE_ICONIC_REPRESENTATION = 7,
        WCA_EXTENDED_FRAME_BOUNDS = 8,
        WCA_HAS_ICONIC_BITMAP = 9,
        WCA_THEME_ATTRIBUTES = 10,
        WCA_NCRENDERING_EXILED = 11,
        WCA_NCADORNMENTINFO = 12,
        WCA_EXCLUDED_FROM_LIVEPREVIEW = 13,
        WCA_VIDEO_OVERLAY_ACTIVE = 14,
        WCA_FORCE_ACTIVEWINDOW_APPEARANCE = 15,
        WCA_DISALLOW_PEEK = 16,
        WCA_CLOAK = 17,
        WCA_CLOAKED = 18,
        WCA_ACCENT_POLICY = 19,
        WCA_FREEZE_REPRESENTATION = 20,
        WCA_EVER_UNCLOAKED = 21,
        WCA_VISUAL_OWNER = 22,
        WCA_LAST = 23
};
struct WindowCompositionAttributeData
{
        WindowCompositionAttribute Attribute;
        int * Data;
        int SizeOfData;
};

typedef int* (*pfun)(HWND hwnd, WindowCompositionAttributeData *data);
DisplayWindow::DisplayWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DisplayWindow)
{
    ui->setupUi(this);
     lastTime="";
    report=new reportthread;
    tray=new QSystemTrayIcon(this);
    state=0;
   this->setAttribute(Qt::WA_TranslucentBackground);//设置窗口背景透明
    this->setWindowFlags
    (this->windowFlags()|Qt::FramelessWindowHint);

    tmReport=new QTimer;

connect( tmReport,SIGNAL(timeout()),this,SLOT(on_tmReport_timout()));
tmReport->start(600);
    tmChange=new QTimer;
    connect(tmChange,SIGNAL(timeout()),this,SLOT(on_tmChange_timout()));
    iniSettings();
    tmChange->start();
    ui->label->setScaledContents(1);

    tray->setIcon(QIcon(":/logo/res/PS.ico"));
    tray->setToolTip("水滴时钟");
    tray->show();
    connect(tray,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(active(QSystemTrayIcon::ActivationReason)));
   tray->showMessage("水滴时钟","你好。很高兴见到你。水滴时钟正在运行。",QIcon(":/logo/res/PS.ico"),10000);
   m_animation = new QPropertyAnimation();
      m_animation->setTargetObject(ui->mainframe);    //设置使用动画的控件
      m_animation->setEasingCurve(QEasingCurve::Linear);

      m_animation->setPropertyName("pos");    //指定动画属性名
          m_animation->setDuration(500);    //设置动画时间（单位：毫秒）
          m_animation->setStartValue(QPoint(-391,0));  //设置动画起始位置在label控件当前的pos
          m_animation->setEndValue( QPoint(0,0)); //设置动画结束位置
          m_animation->start();




}



void ME::paintEvent(QPaintEvent *event)
{
    if(isBlur)
    {
        static bool v = false;
        if (v) return;

        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setPen(Qt::NoPen);
        painter.setBrush(bgColor);
        painter.drawRoundedRect(rect(), 0, 0);
        v = true;
        //painter.fillRect(ui.frame->rect(), bgColor);
    }
    else{
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

}

void DisplayWindow::mousePressEvent(QMouseEvent *event)
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

void DisplayWindow::mouseMoveEvent(QMouseEvent *event)
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

void DisplayWindow::mouseReleaseEvent(QMouseEvent *event)
{
 m_moving=false; //停止移动
 QSettings *settingsPos=new QSettings("WaterDropLab","WaterDropClock");
 settingsPos->setValue("Display/Postion/X",geometry().x());
 settingsPos->setValue("Display/Postion/Y",geometry().y());
 delete settingsPos;
}


DisplayWindow::~DisplayWindow()
{
    delete ui;
}

bool DisplayWindow::SetVolumeLevel(int level)
{
    HRESULT hr;
    IMMDeviceEnumerator* pDeviceEnumerator = 0;
    IMMDevice* pDevice = 0;
    IAudioEndpointVolume* pAudioEndpointVolume = 0;
    IAudioClient* pAudioClient = 0;

    try {
        hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_ALL, __uuidof(IMMDeviceEnumerator), (void**)&pDeviceEnumerator);
        if (FAILED(hr)) throw "CoCreateInstance";
        hr = pDeviceEnumerator->GetDefaultAudioEndpoint(eRender, eMultimedia, &pDevice);
        if (FAILED(hr)) throw "GetDefaultAudioEndpoint";
        hr = pDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_ALL, NULL, (void**)&pAudioEndpointVolume);
        if (FAILED(hr)) throw "pDevice->Active";
        hr = pDevice->Activate(__uuidof(IAudioClient), CLSCTX_ALL, NULL, (void**)&pAudioClient);
        if (FAILED(hr)) throw "pDevice->Active";

        if (level == -2) {
            hr = pAudioEndpointVolume->SetMute(FALSE, NULL);
            if (FAILED(hr)) throw "SetMute";
        }
        else if (level == -1) {
            hr = pAudioEndpointVolume->SetMute(TRUE, NULL);
            if (FAILED(hr)) throw "SetMute";
        }
        else {
            if (level<0 || level>100) {
                hr = E_INVALIDARG;
                throw "Invalid Arg";
            }

            float fVolume;
            fVolume = level / 100.0f;
            hr = pAudioEndpointVolume->SetMasterVolumeLevelScalar(fVolume, &GUID_NULL);
            if (FAILED(hr)) throw "SetMasterVolumeLevelScalar";
            hr = pAudioEndpointVolume->SetMute(FALSE, NULL);
            pAudioClient->Release();
            pAudioEndpointVolume->Release();
            pDevice->Release();
            pDeviceEnumerator->Release();
            return true;
        }
    }
    catch (...) {
        if (pAudioClient) pAudioClient->Release();
        if (pAudioEndpointVolume) pAudioEndpointVolume->Release();
        if (pDevice) pDevice->Release();
        if (pDeviceEnumerator) pDeviceEnumerator->Release();
        throw;
    }
    return false;
}

void DisplayWindow::noMute()
{
   SendMessage(HWND_BROADCAST, WM_APPCOMMAND, 0x200eb0, APPCOMMAND_VOLUME_MUTE *0x10000);

}

void DisplayWindow::iniSettings()
{

    QSettings *settings=new QSettings("WaterDropLab","WaterDropClock");
    QDate dateCur=QDate::currentDate();
    move(settings->value("Display/Postion/X",geometry().x()).toInt(),settings->value("Display/Postion/Y",geometry().y()).toInt());
    if(settings->value("Display/Section1/Enabled",1).toBool())
    {
        tmChange->setInterval(settings->value("Display/Section1/Interval",5).toInt()*1000);

       QDate dateTarget=dateTarget.fromString(settings->value("Display/Section1/TargetDate",QDate::currentDate().toString("yyyy-MM-dd")).toString(),"yyyy-MM-dd");
        int days=dateCur.daysTo(dateTarget);
        if (days>=0)
            ui->lcdDay->display(days);
        else goto l2;
        ui->lcdDay->setVisible(1);
        ui->labDay->setVisible(1);
        QFont font;
        font.setPointSize(settings->value("Display/Section1/FontSize",36).toInt());
        font.setFamily(settings->value("Display/Section1/FontName","幼圆").toString());
        ui->labTitle->setFont(font);
        ui->labTitle->setText(settings->value("Display/Section1/Title","标题1未命名").toString());

    }

    else if(settings->value("Display/Section2/Enabled",1).toBool())
    {
        l2:
        if(!settings->value("Display/Section2/Enabled",1).toBool())
        {
            goto l3;
        }
       tmChange->setInterval(settings->value("Display/Section2/Interval",5).toInt()*1000);
        ui->lcdDay->setVisible(1);
        ui->labDay->setVisible(1);
        QDate dateTarget=dateTarget.fromString(settings->value("Display/Section2/TargetDate",QDate::currentDate().toString("yyyy-MM-dd")).toString(),"yyyy-MM-dd");
        int days=dateCur.daysTo(dateTarget);
        if (days>=0)
            ui->lcdDay->display(days);
        else goto l3;
        QFont font;
        font.setPointSize(settings->value("Display/Section2/FontSize",36).toInt());
        font.setFamily(settings->value("Display/Section2/FontName","幼圆").toString());
        ui->labTitle->setFont(font);
        ui->labTitle->setText(settings->value("Display/Section2/Title","标题2未命名").toString());
    }
    else if(settings->value("Display/Paragraph/Enabled",1).toBool())
    {
        l3:
       tmChange->setInterval(settings->value("Display/Paragraph/Interval",5).toInt()*1000);
        QFont font;
        font.setPointSize(settings->value("Display/Paragraph/FontSize",36).toInt());
        font.setFamily(settings->value("Display/Paragraph/FontName","幼圆").toString());
        ui->labTitle->setFont(font);
        ui->labTitle->setText(settings->value("Display/Paragraph/Content","无内容").toString());
        ui->lcdDay->setVisible(0);
        ui->labDay->setVisible(0);
    }
    if(settings->value("Display/isBlur",0).toBool()){
        isBlur=1;
        HWND hWnd = HWND(winId());
        HMODULE hUser = GetModuleHandle(L"user32.dll");

        if (hUser) {
            pfun setWindowCompositionAttribute = (pfun)GetProcAddress(hUser, "SetWindowCompositionAttribute");
            if (setWindowCompositionAttribute) {
    //            AccentPolicy accent = { ACCENT_ENABLE_BLURBEHIND, 0x20 | 0x40 | 0x80 | 0x100, 0, 0 };
                AccentPolicy accent = { ACCENT_ENABLE_BLURBEHIND,0, 0, 0 };
                WindowCompositionAttributeData data;
                data.Attribute = WCA_ACCENT_POLICY;
                data.Data = reinterpret_cast<int *>(&accent) ;
                data.SizeOfData = sizeof(accent);
                setWindowCompositionAttribute(hWnd, &data);
            }
        }
        this->setAttribute(Qt::WA_TranslucentBackground);//设置窗口背景透明
    //    setWindowOpacity(1);
        setWindowTitle(QString(""));
        ui->btnMenu->setStyleSheet("#btnMenu{border-radius:5px;border: 0px solid rgb(0,0,0); background: transparent; color:rgb(255,255,255);}");


        //
        bgColor = QColor(255, 255, 255, 100);
    }
    else {
        isBlur=0;
    }
    delete  settings;

}

void DisplayWindow::active(QSystemTrayIcon::ActivationReason r)
{
    //tray->showMessage("水滴时钟","你好。很高兴见到你。水滴时钟正在运行。",QIcon(":/logo/res/PS.ico"),10000);
    QMenu *menu=new QMenu(this);
    QMenu *power=new QMenu(menu);
    power->setTitle("强制电源选项");
    menu->addAction(ui->actExit);
   ui->actDisplay->setChecked(isVisible());
    menu->addAction(ui->actDisplay);
    menu->addSeparator();
    menu->addMenu(power);
    power->addAction(ui->actShutdown);
    power->addAction(ui->actRebbot);
    power->addAction(ui->actForceLogout);

    menu->addAction(ui->actNoForceReboot);
    menu->addAction(ui->actLogout);
    menu->addAction(ui->actNoForceShutdown);





    menu->move(tray->geometry().x(),tray->geometry().y()-menu->height()*5);
    menu->exec();
}

void DisplayWindow::on_tmChange_timout()
{
    QSettings *settings=new QSettings("WaterDropLab","WaterDropClock");
    QDate dateCur=QDate::currentDate();
    switch (state) {
    case 0:
    {
        if(settings->value("Display/Section1/Enabled",1).toBool())
        {
            tmChange->setInterval(settings->value("Display/Section1/Interval",5).toInt()*1000);
           QDate dateTarget=dateTarget.fromString(settings->value("Display/Section1/TargetDate",QDate::currentDate().toString("yyyy-MM-dd")).toString(),"yyyy-MM-dd");
            int days=dateCur.daysTo(dateTarget);
            if (days>=0)
                ui->lcdDay->display(days);
            else goto l2;
            ui->lcdDay->setVisible(1);
            ui->labDay->setVisible(1);
            QFont font;
            font.setPointSize(settings->value("Display/Section1/FontSize",36).toInt());
            font.setFamily(settings->value("Display/Section1/FontName","幼圆").toString());
            ui->labTitle->setFont(font);
            ui->labTitle->setText(settings->value("Display/Section1/Title","标题1未命名").toString());
            state++;
            break;
        }
        else
        {
             goto l2;
        }

    }
     case 1:
    {
        if(settings->value("Display/Section2/Enabled",1).toBool())
       {
           l2:
           if(!settings->value("Display/Section2/Enabled",1).toBool())
           {
               goto l3;
           }
           tmChange->setInterval(settings->value("Display/Section2/Interval",5).toInt()*1000);
           ui->lcdDay->setVisible(1);
           ui->labDay->setVisible(1);
           QDate dateTarget=dateTarget.fromString(settings->value("Display/Section2/TargetDate",QDate::currentDate().toString("yyyy-MM-dd")).toString(),"yyyy-MM-dd");
           int days=dateCur.daysTo(dateTarget);
           if (days>=0)
               ui->lcdDay->display(days);
           else goto l3;
           QFont font;
           font.setPointSize(settings->value("Display/Section2/FontSize",36).toInt());
           font.setFamily(settings->value("Display/Section2/FontName","幼圆").toString());
           ui->labTitle->setFont(font);
           ui->labTitle->setText(settings->value("Display/Section2/Title","标题2未命名").toString());
           state++;
           break;
       }
       else
       {
            goto l3;
       }
    }
    case 2:
    {
        if(settings->value("Display/Paragraph/Enabled",1).toBool())
       {
           l3:
            tmChange->setInterval(settings->value("Display/Paragraph/Interval",5).toInt()*1000);
           QFont font;
           font.setPointSize(settings->value("Display/Paragraph/FontSize",36).toInt());
           font.setFamily(settings->value("Display/Paragraph/FontName","幼圆").toString());
           ui->labTitle->setFont(font);
           ui->labTitle->setText(settings->value("Display/Paragraph/Content","无内容").toString());
           ui->lcdDay->setVisible(0);
           ui->labDay->setVisible(0);
           state=0;
           break;
       }
    }

    }





    delete  settings;
}

void DisplayWindow::on_tmReport_timout()
{

     QSettings *reg=new QSettings("WaterDropLab","WaterDropClock");
     if(reg->value("Report/Enabled",1).toBool() && reg->value("Report/Time","07:30:00")==QTime::currentTime().toString("HH:mm:ss") && (QTime::currentTime().toString("HH:mm:ss") !=lastTime))
     {
          QSettings *settings=new QSettings("WaterDropLab","WaterDropClock");
         if(settings->value("Report/ForceRegulateSystemVolume",0).toBool()){

             SetVolumeLevel(settings->value("Report/SystemVolume",50).toInt());
         }
         delete settings;
          tray->showMessage("水滴时钟","水滴时钟正在进行今日播报。",QIcon(":/logo/res/PS.ico"),10000);
         QSound::play(":/wav/res/DingDong.wav");
         report->start(QThread::HighestPriority);
     }
      lastTime=QTime::currentTime().toString("HH:mm:ss");
     delete reg;
}



void DisplayWindow::on_btnMenu_clicked()
{
    MainMenu *mainmenu=new MainMenu(this);
   mainmenu->move(geometry().x()+ui->btnMenu->geometry().x()-mainmenu->width()/2,geometry().y()+ui->btnMenu->geometry().y()+ui->btnMenu->height());
   mainmenu->show();
}

void DisplayWindow::on_actExit_triggered()
{
    QApplication* app;
    app->exit(0);
}

void DisplayWindow::on_actShutdown_triggered()
{
    MySystemShutDown();
}

bool DisplayWindow::MySystemShutDown()
{
    HANDLE hToken;
    TOKEN_PRIVILEGES tkp;
   //获取进程标志
   if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
         return false;
    //获取关机特权的LUID
    LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME,    &tkp.Privileges[0].Luid);
    tkp.PrivilegeCount = 1;
    tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
    //获取这个进程的关机特权
    AdjustTokenPrivileges(hToken, false, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0);
    if (GetLastError() != ERROR_SUCCESS) return false;
    // 强制关闭计算机
    if ( !ExitWindowsEx(EWX_SHUTDOWN | EWX_FORCE, 0))
          return false;
    return true;
//   // 强制重启计算机
//    if ( !ExitWindowsEx(EWX_REBOOT| EWX_FORCE, 0))
//          return false;
    //    return true;
}

bool DisplayWindow::MySystemReboot()
{
    HANDLE hToken;
    TOKEN_PRIVILEGES tkp;
   //获取进程标志
   if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
         return false;
    //获取关机特权的LUID
    LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME,    &tkp.Privileges[0].Luid);
    tkp.PrivilegeCount = 1;
    tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
    //获取这个进程的关机特权
    AdjustTokenPrivileges(hToken, false, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0);
    if (GetLastError() != ERROR_SUCCESS) return false;
    if ( !ExitWindowsEx(EWX_REBOOT| EWX_FORCE, 0))
             return false;
    return true;
}

bool DisplayWindow::SysShut()
{
    HANDLE hToken;
    TOKEN_PRIVILEGES tkp;
   //获取进程标志
   if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
         return false;
    //获取关机特权的LUID
    LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME,    &tkp.Privileges[0].Luid);
    tkp.PrivilegeCount = 1;
    tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
    //获取这个进程的关机特权
    AdjustTokenPrivileges(hToken, false, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0);
    if (GetLastError() != ERROR_SUCCESS) return false;
    // 强制关闭计算机
    if ( !ExitWindowsEx(EWX_SHUTDOWN, 0))
          return false;
    return true;
}

bool DisplayWindow::SysReboot()
{
    HANDLE hToken;
    TOKEN_PRIVILEGES tkp;
   //获取进程标志
   if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
         return false;
    //获取关机特权的LUID
    LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME,    &tkp.Privileges[0].Luid);
    tkp.PrivilegeCount = 1;
    tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
    //获取这个进程的关机特权
    AdjustTokenPrivileges(hToken, false, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0);
    if (GetLastError() != ERROR_SUCCESS) return false;
    if ( !ExitWindowsEx(EWX_REBOOT, 0))
             return false;
    return true;
}

bool DisplayWindow::sysLogout()
{
    HANDLE hToken;
    TOKEN_PRIVILEGES tkp;
   //获取进程标志
   if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
         return false;
    //获取关机特权的LUID
    LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME,    &tkp.Privileges[0].Luid);
    tkp.PrivilegeCount = 1;
    tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
    //获取这个进程的关机特权
    AdjustTokenPrivileges(hToken, false, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0);
    if (GetLastError() != ERROR_SUCCESS) return false;
    if ( !ExitWindowsEx(EWX_LOGOFF, 0))
             return false;
    return true;
}

bool DisplayWindow::sysLogoutForce()
{
    HANDLE hToken;
    TOKEN_PRIVILEGES tkp;
   //获取进程标志
   if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
         return false;
    //获取关机特权的LUID
    LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME,    &tkp.Privileges[0].Luid);
    tkp.PrivilegeCount = 1;
    tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
    //获取这个进程的关机特权
    AdjustTokenPrivileges(hToken, false, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0);
    if (GetLastError() != ERROR_SUCCESS) return false;
    if ( !ExitWindowsEx(EWX_LOGOFF|EWX_FORCE, 0))
             return false;
    return true;
}

void DisplayWindow::on_actRebbot_triggered()
{
    MySystemReboot();
}

void DisplayWindow::on_actNoForceShutdown_triggered()
{
    SysShut();
}

void DisplayWindow::on_actNoForceReboot_triggered()
{
    SysReboot();
}

void DisplayWindow::on_actDisplay_triggered(bool checked)
{
    if(checked){
        this->setVisible(1);
    }
    else{
        this->setVisible(0);
    }
}

void DisplayWindow::on_actLogout_triggered()
{
    sysLogout();
}

void DisplayWindow::on_actForceLogout_triggered()
{
    sysLogoutForce();
}
