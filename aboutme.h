#if _MSC_VER >=1600
#pragma execution_character_set("utf-8")
#endif
#ifndef ABOUTME_H
#define ABOUTME_H
#include <QDialog>
#include <QPainter>
#include <QMouseEvent>
#include <QSettings>
#include <QFont>
namespace Ui {
class AboutMe;
}

class AboutMe : public QDialog
{
    Q_OBJECT
protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

public:
    explicit AboutMe(QWidget *parent = nullptr);
    ~AboutMe();
    bool state=0;
private slots:
    void on_btndef_2_clicked();

    void on_btndef_3_clicked();

    void on_btndef_4_clicked();

private:
    Ui::AboutMe *ui;
    QPoint  m_lastPos;
    bool    m_moving=false;
};

#endif // ABOUTME_H
