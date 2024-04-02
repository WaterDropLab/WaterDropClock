#if _MSC_VER >=1600
#pragma execution_character_set("utf-8")
#endif

#ifndef CONFIGWINDOW_H
#define CONFIGWINDOW_H

#include <QSoundEffect>
#include <QDialog>
#include <QPainter>
#include <QMouseEvent>
#include <QSettings>
#include <QFont>
#include <QtTextToSpeech>
#include <QVoice>
#include <reportthread.h>
#include <QPropertyAnimation>
namespace Ui {
class ConfigWindow;
}

class ConfigWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigWindow(QWidget *parent = nullptr);
    ~ConfigWindow();
    void  iniSettings();
    QSettings *settings;
    QFont mainFont;
    QFont subFont;
    QFont parFont;
    QTextToSpeech *m_speech;
    QVector<QVoice> m_voices;
    reportthread *report;
    QSoundEffect *sound;

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
private slots:
    void on_btndef_2_clicked();

    void on_btndef_clicked();


    void speechEnded();

    void on_tabDisplay_clicked();

    void on_tabReport_clicked();

    void on_tabOthers_clicked();


    void on_chk1_clicked(bool checked);

    void on_chk2_clicked(bool checked);

    void on_chk3_clicked(bool checked);

    void on_txtTitle1_textChanged(const QString &arg1);

    void on_txtTitle2_textChanged(const QString &arg1);

    void on_txtParagraph_textChanged();

    void on_spinInterval1_valueChanged(int arg1);

    void on_spinInterval2_valueChanged(int arg1);

    void on_spinInterval3_valueChanged(int arg1);

    void on_date1_userDateChanged(const QDate &date);

    void on_date2_userDateChanged(const QDate &date);

    void on_btnEdit1_clicked();

    void on_btnEdit2_clicked();

    void on_btnEditPar_clicked();

    void on_rechk1_clicked(bool checked);

    void on_rechk2_clicked(bool checked);

    void on_rechk3_clicked(bool checked);

    void on_rechk_clicked(bool checked);

    void on_timRe_userTimeChanged(const QTime &time);

    void on_sliVol_sliderMoved(int position);

    void on_sliRate_sliderMoved(int position);

    void on_retxtTitle1_textChanged(const QString &arg1);

    void on_retxtTitle2_cursorPositionChanged(int arg1, int arg2);

    void on_retxtParagraph_textChanged();

    void on_retxtTitle2_textChanged(const QString &arg1);

    void on_redate1_dateChanged(const QDate &date);

    void on_redate2_dateChanged(const QDate &date);

    void on_bthListen_clicked(bool checked);

    void  soundStopped();
    void  startSpeak();

    void on_runChk_clicked(bool checked);

    void on_runChk_2_clicked(bool checked);

    void on_spnVolSys_valueChanged(int arg1);

private:
    Ui::ConfigWindow *ui;
     QPoint  m_lastPos;
     bool    m_moving=false;

};

#endif // CONFIGWINDOW_H
