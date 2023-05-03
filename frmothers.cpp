#include "frmothers.h"
#include "ui_frmothers.h"

frmothers::frmothers(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmothers)
{
    ui->setupUi(this);
}

frmothers::~frmothers()
{
    delete ui;
}
