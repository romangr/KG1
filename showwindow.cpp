#include "showwindow.h"
#include "ui_showwindow.h"

TShowWindow::TShowWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TShowWindow)
{
    ui->setupUi(this);
}

TShowWindow::~TShowWindow()
{
    delete ui;
}
