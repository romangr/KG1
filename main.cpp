#include "mainwindow.h"
#include <QApplication>
#include "matrix.h"
#include <qdebug.h>
#include "figure.h"
using namespace std;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Matrix b;
    double line1[3] = {1, 0, 0};
    double line2[3] = {0, 1, 0};
    double line3[3] = {0, 0, 1};

    Matrix c;
    double line4[3] = {1, 2, 3};
    double line5[3] = {4, 5, 6};
    double line6[3] = {7, 8, 9};

    b.addLine(3, line1);
    b.addLine(3, line2);
    b.addLine(3, line3);
    c.addLine(3, line4);
    c.addLine(3, line5);
    c.addLine(3, line6);

    Figure *f1 = new Figure(b);
    f1->printMatrix();
    f1->transform(c);
    f1->printMatrix();
    return a.exec();
}
