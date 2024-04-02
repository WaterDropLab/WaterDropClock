#if _MSC_VER >=1600
#pragma execution_character_set("utf-8")
#endif
#ifndef PARFONTSELECTOR_H
#define PARFONTSELECTOR_H

#include <QDialog>
#include <QPainter>
#include <QMouseEvent>
#include <QSettings>
#include <QFont>
namespace Ui {
class parFontSelector;
}

class parFontSelector : public QDialog
{
    Q_OBJECT

public:
    explicit parFontSelector(QFont font,QString content,QWidget *parent = nullptr);
    ~parFontSelector();
    QFont cfont;
    QString reStr;
private:
    Ui::parFontSelector *ui;
    QPoint  m_lastPos;
    bool    m_moving=false;

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
private slots:
    void on_btndef_clicked();

    void on_txtTitle1_textChanged(const QString &arg1);

    void on_btnSelect_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_txtTitle1_textChanged();
};

#endif // PARFONTSELECTOR_H
