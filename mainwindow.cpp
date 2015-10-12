#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    fig1 = new Figure();
    showWindow1 = new TShowWindow();
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
    fig1->addPoint(x,y,z);

    x = this->ui->lineEdit_4->text().toDouble();
    y = this->ui->lineEdit_5->text().toDouble();
    z = this->ui->lineEdit_6->text().toDouble();
    fig1->addPoint(x,y,z);

    x = this->ui->lineEdit_7->text().toDouble();
    y = this->ui->lineEdit_8->text().toDouble();
    z = this->ui->lineEdit_9->text().toDouble();
    fig1->addPoint(x,y,z);

    x = this->ui->lineEdit_10->text().toDouble();
    y = this->ui->lineEdit_11->text().toDouble();
    z = this->ui->lineEdit_12->text().toDouble();
    fig1->addPoint(x,y,z);

    x = this->ui->lineEdit_13->text().toDouble();
    y = this->ui->lineEdit_14->text().toDouble();
    z = this->ui->lineEdit_15->text().toDouble();
    fig1->addPoint(x,y,z);

    x = this->ui->lineEdit_16->text().toDouble();
    y = this->ui->lineEdit_17->text().toDouble();
    z = this->ui->lineEdit_18->text().toDouble();
    fig1->addPoint(x,y,z);

    x = this->ui->lineEdit_19->text().toDouble();
    y = this->ui->lineEdit_20->text().toDouble();
    z = this->ui->lineEdit_21->text().toDouble();
    fig1->addPoint(x,y,z);

    x = this->ui->lineEdit_22->text().toDouble();
    y = this->ui->lineEdit_23->text().toDouble();
    z = this->ui->lineEdit_24->text().toDouble();
    fig1->addPoint(x,y,z);

}

void MainWindow::turn_button_clicked()
{
    int axis = this->ui->comboBox->currentIndex();
    double angle = this->ui->lineEdit_25->text().toDouble();
    fig1->turn(axis,angle);
}

void MainWindow::show_button_clicked()
{
    //вообще тут надо по нажатию выводить данные с матрицы
    if (this->showWindow1->isVisible())
        this->showWindow1->hide();
    else
        this->showWindow1->show();

}
