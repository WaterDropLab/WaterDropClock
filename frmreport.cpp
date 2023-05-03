#include "frmreport.h"
#include "ui_frmreport.h"

frmReport::frmReport(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmReport)
{
    ui->setupUi(this);
}

frmReport::~frmReport()
{
    delete ui;
}
