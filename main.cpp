#include "mainwindow.h"
#include <QApplication>
#include "matrix.h"
#include <qdebug.h>
#include "figure.h"
#include <math.h>
#include "triangle.h"
using namespace std;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    Matrix m;
    m.addLine(0,0,0,0);
    m.addLine(7,0,0,0);
    m.addLine(4,5,-1,0);
    Triangle *a1 = new Triangle(m, 0,0,0);
    qDebug() << a1->isUnderTriangle(3, 4, -0.3);
    return a.exec();
}
