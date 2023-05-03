#ifndef FRMOTHERS_H
#define FRMOTHERS_H

#include <QWidget>

namespace Ui {
class frmothers;
}

class frmothers : public QWidget
{
    Q_OBJECT

public:
    explicit frmothers(QWidget *parent = nullptr);
    ~frmothers();

private:
    Ui::frmothers *ui;
};

#endif // FRMOTHERS_H
