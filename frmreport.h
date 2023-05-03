#ifndef FRMREPORT_H
#define FRMREPORT_H

#include <QWidget>

namespace Ui {
class frmReport;
}

class frmReport : public QWidget
{
    Q_OBJECT

public:
    explicit frmReport(QWidget *parent = nullptr);
    ~frmReport();

private:
    Ui::frmReport *ui;
};

#endif // FRMREPORT_H
