#ifndef FRMDISPLAY_H
#define FRMDISPLAY_H

#include <QWidget>

namespace Ui {
class frmDisplay;
}

class frmDisplay : public QWidget
{
    Q_OBJECT

public:
    explicit frmDisplay(QWidget *parent = nullptr);
    ~frmDisplay();

private:
    Ui::frmDisplay *ui;
};

#endif // FRMDISPLAY_H
