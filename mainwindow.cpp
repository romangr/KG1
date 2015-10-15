#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    fig1 = new Figure();
    for (int i=0; i<8; i++)
        { fig1->addPoint(0,0,0);}

    showWindow1 = new TShowWindow(0,this->fig1);
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
    double x,y,z;
    x = this->ui->lineEdit->text().toDouble();
    y = this->ui->lineEdit_2->text().toDouble();
    z = this->ui->lineEdit_3->text().toDouble();
    fig1->editPoint(1,x,y,z);

    x = this->ui->lineEdit_4->text().toDouble();
    y = this->ui->lineEdit_5->text().toDouble();
    z = this->ui->lineEdit_6->text().toDouble();
    fig1->editPoint(2,x,y,z);
    fig1->setEdge(1,2,true);

    x = this->ui->lineEdit_7->text().toDouble();
    y = this->ui->lineEdit_8->text().toDouble();
    z = this->ui->lineEdit_9->text().toDouble();
    fig1->editPoint(3,x,y,z);
    fig1->setEdge(2,3,true);

    x = this->ui->lineEdit_10->text().toDouble();
    y = this->ui->lineEdit_11->text().toDouble();
    z = this->ui->lineEdit_12->text().toDouble();
    fig1->editPoint(4,x,y,z);
    fig1->setEdge(3,4,true);
    fig1->setEdge(1,4,true);

    x = this->ui->lineEdit_13->text().toDouble();
    y = this->ui->lineEdit_14->text().toDouble();
    z = this->ui->lineEdit_15->text().toDouble();
    fig1->editPoint(5,x,y,z);
    fig1->setEdge(1,5,true);

    x = this->ui->lineEdit_16->text().toDouble();
    y = this->ui->lineEdit_17->text().toDouble();
    z = this->ui->lineEdit_18->text().toDouble();
    fig1->editPoint(6,x,y,z);
    fig1->setEdge(2,6,true);
    fig1->setEdge(5,6,true);

    x = this->ui->lineEdit_19->text().toDouble();
    y = this->ui->lineEdit_20->text().toDouble();
    z = this->ui->lineEdit_21->text().toDouble();
    fig1->editPoint(7,x,y,z);
    fig1->setEdge(3,7,true);
    fig1->setEdge(6,7,true);

    x = this->ui->lineEdit_22->text().toDouble();
    y = this->ui->lineEdit_23->text().toDouble();
    z = this->ui->lineEdit_24->text().toDouble();
    fig1->editPoint(8,x,y,z);
    fig1->setEdge(4,8,true);
    fig1->setEdge(7,8,true);
    fig1->setEdge(5,8,true);

    fig1->finalize();

    //WTF?
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
