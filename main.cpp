#include "mainwindow.h"
#include <QApplication>
#include "matrix.h"
#include <qdebug.h>
using namespace std;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();
    Matrix b;
    double line1[3] = {1, 0, 0};
    double line2[3] = {0, 1, 0};
    double line3[3] = {0, 0, 1};

    b.addLine(3, line1);
    b.addLine(3, line2);
    b.addLine(3, line3);

    Matrix c = b;
    Matrix d = c*b;

    for (int i = 0; i < 3; i++)
        qDebug() << d.getElement(i, 0) << " " << d.getElement(i, 1) << " " << d.getElement(i, 2);
    return a.exec();
}
