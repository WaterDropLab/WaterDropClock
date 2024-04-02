#if _MSC_VER >=1600
#pragma execution_character_set("utf-8")
#endif
#ifndef MAINMENU_H
#define MAINMENU_H

#include <QDialog>

namespace Ui {
class MainMenu;
}

class MainMenu : public QDialog
{
    Q_OBJECT

public:
    explicit MainMenu(QWidget *parent = nullptr);
    ~MainMenu();
protected:
    void paintEvent(QPaintEvent *event);
private slots:
    void on_btnExit_clicked();

    void on_btnSetting_clicked();

    void on_btnAbout_clicked();

    void on_btnAboutUs_clicked();

    void on_btnUpDate_clicked();

private:
    Ui::MainMenu *ui;
};

#endif // MAINMENU_H
