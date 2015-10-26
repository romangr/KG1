#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    fig1 = new Figure();
    showWindow1 = new TShowWindow(0,fig1); //чтоб не вылетало при попытке показа вхолостую
    //wtf, надо координаты mainwindow
    showWindow1->setGeometry(this->x()+50,this->y(),400,300);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete fig1;
    delete showWindow1;
}

void MainWindow::set_coord_clicked()
{
    double x1,y1,z1,x2,y2,z2,x3,y3,z3;
    double k;
    x1 = this->ui->lineEdit->text().toDouble();
    y1 = this->ui->lineEdit_2->text().toDouble();
    z1 = this->ui->lineEdit_3->text().toDouble();

    x2 = this->ui->lineEdit_4->text().toDouble();
    y2 = this->ui->lineEdit_5->text().toDouble();
    z2 = this->ui->lineEdit_6->text().toDouble();

    x3 = this->ui->lineEdit_7->text().toDouble();
    y3 = this->ui->lineEdit_8->text().toDouble();
    z3 = this->ui->lineEdit_9->text().toDouble();
    Parabola p1(x1,y1,z1,x2,y2,z2,x3,y3,z3);

    x1 = this->ui->lineEdit_10->text().toDouble();
    y1 = this->ui->lineEdit_11->text().toDouble();
    z1 = this->ui->lineEdit_12->text().toDouble();

    x2 = this->ui->lineEdit_13->text().toDouble();
    y2 = this->ui->lineEdit_14->text().toDouble();
    z2 = this->ui->lineEdit_15->text().toDouble();

    x3 = this->ui->lineEdit_16->text().toDouble();
    y3 = this->ui->lineEdit_17->text().toDouble();
    z3 = this->ui->lineEdit_18->text().toDouble();
    Parabola p2(x1,y1,z1,x2,y2,z2,x3,y3,z3);

    k = this->ui->lineEdit_19->text().toDouble();

    fig1 = RuledParabols(p1,p2).getFigure(k);
    showWindow1->setFigure(fig1);

    //думал, что надоело мигать, но нет - без этого при холодном запуске
    //сначала show, затем set coord ничего не отображает
    showWindow1->activateWindow();
}

void MainWindow::turn_button_clicked()
{
    int axis = this->ui->comboBox->currentIndex();
    double angle = this->ui->lineEdit_25->text().toDouble();
    fig1->turn(axis,angle);
    showWindow1->activateWindow();
}

void MainWindow::show_button_clicked()
{
    if (this->showWindow1->isVisible())
        { showWindow1->hide();}
    else
        { showWindow1->show();}

}

void MainWindow::autoscale_clicked()
{
    this->fig1->autoscale(showWindow1);
}
