#include "showwindow.h"
#include "ui_showwindow.h"

TShowWindow::TShowWindow(QWidget *parent, Figure *figure) :
    QWidget(parent),
    ui(new Ui::TShowWindow)
{
    ui->setupUi(this);
    this->f = figure;
}

TShowWindow::~TShowWindow()
{
    delete ui;
}

void TShowWindow::paintEvent(QPaintEvent *)
{
    this->f->draw(this);
}

void TShowWindow::setFigure(Figure *figure)
{
    f = figure;
}
