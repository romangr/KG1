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
    double line1[4] = {1, 0, 0, 0};
    double line2[4] = {0, 1, 0, 0};
    double line3[4] = {0, 0, 1, 0};
    double line8[4] = {0, 0, 0, 1};

    Matrix c;
    double line4[4] = {1, 2, 3, 0};
    double line5[4] = {4, 5, 6, 0};
    double line6[4] = {7, 8, 9, 0};
    double line7[4] = {0, 0, 0, 1};

    b.addLine(4, line1);
    b.addLine(4, line2);
    b.addLine(4, line3);
    //b.addLine(4, line8);
    c.addLine(4, line4);
    c.addLine(4, line5);
    c.addLine(4, line6);
    c.addLine(4, line7);

    Figure *f1 = new Figure(b);
    f1->printMatrix();
    f1->finalize();
    f1->transform(c);
    f1->printMatrix();
    f1->printAdjacency();
    f1->turn(0, 30);
    f1->printMatrix();
    f1->setEdge(1,1,1);
    f1->printAdjacency();
    return a.exec();
}
