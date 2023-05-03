#include "frmdisplay.h"
#include "ui_frmdisplay.h"

frmDisplay::frmDisplay(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmDisplay)
{
    ui->setupUi(this);
}

frmDisplay::~frmDisplay()
{
    delete ui;
}
