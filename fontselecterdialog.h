#ifndef FONTSELECTERDIALOG_H
#define FONTSELECTERDIALOG_H

#include <QDialog>
#include <QPainter>
#include <QMouseEvent>
#include <QSettings>
#include <QFont>
namespace Ui {
class fontSelecterDialog;
}

class fontSelecterDialog : public QDialog
{
    Q_OBJECT
protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void closeEvent(QCloseEvent *event);
public:
    explicit fontSelecterDialog(QFont font,QString title,QWidget *parent = nullptr);
    ~fontSelecterDialog();
    QFont cfont;
    QString reStr;
    bool state=0;
private slots:
    void on_btndef_clicked();

    void on_txtTitle1_textChanged(const QString &arg1);

    void on_btnSelect_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::fontSelecterDialog *ui;
    QPoint  m_lastPos;
    bool    m_moving=false;
};

#endif // FONTSELECTERDIALOG_H
