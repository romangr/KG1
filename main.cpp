#include "mainwindow.h"
#include <QApplication>
#include "matrix.h"
#include <qdebug.h>
#include "figure.h"
#include <math.h>
#include "triangle.h"
#include "linesegment.h"
#include "lightedsurface.h"
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    /*Matrix m;
    m.addLine(0,0,-1,0);
    m.addLine(7,0,-1,0);
    m.addLine(4,5,-1,0);
    Triangle *a1 = new Triangle(m, 0,0,0);
    qDebug() << a1->getZmax() << " " << a1->getZmin();*/
    //qDebug() << a1->isUnderTriangle(3, 4, -0.3);
 /*   LineSegment *ls = new LineSegment(0,0,0,1,1,1);
    ls->addIntersection(0.9,0.95);
    ls->addIntersection(0,0.5);
    ls->addIntersection(0.25,0.75);
    ls->addIntersection(0.25,0.63);
    ls->addIntersection(0.1,0.8);
    ls->calculateIntersections().print();
  */  //qDebug() << res[0] << " " << res[1];
    /*TriangleSurface *trs = new TriangleSurface(0);
    Figure *f = trs->getVisibleFigure();
    f->printMatrix();
    f->printAdjacency();*/


    /*Matrix m;
    m.addLine(-3,0,0,0);
    m.addLine(0,3,0,0);
    m.addLine(3,0,0,0);
    Triangle *a1 = new Triangle(m, 0,0,0);
    Matrix m2;
    m2.addLine(-2,-2,-1,0);
    m2.addLine(0,1,1,0);
    m2.addLine(2,2,-1,0);
    Triangle *a3 = new Triangle(m2, 0,0,0);
    qDebug() << a3->isUnderTrianglePlane(a1);

    LightedSurface lightedSurface;
    lightedSurface.addTriangleToSorted(a1);
    lightedSurface.addTriangleToSorted(a3);

    //qDebug() << a2->getCoord(1,0);
    QLinkedListIterator<Triangle*> it(lightedSurface.sortedTriangles);

    while (it.hasNext())
    {
        Triangle *a2 = it.next();
        qDebug() << "x = " << a2->getCoord(0,0) << "y = " << a2->getCoord(0,1) << "z = " << a2->getCoord(0,2);
        qDebug() << "x = " << a2->getCoord(1,0) << "y = " << a2->getCoord(1,1) << "z = " << a2->getCoord(1,2);
        qDebug() << "x = " << a2->getCoord(2,0) << "y = " << a2->getCoord(2,1) << "z = " << a2->getCoord(2,2);
        qDebug() << "";
    }*/

    /*Matrix m;
    m.addLine(-3,0,0,0);
    m.addLine(0,3,0,0);
    m.addLine(3,0,0,0);
    Triangle *a1 = new Triangle(m, 0,0,0);
    Matrix m2;
    m2.addLine(-1.5,1.5,0,0);
    m2.addLine(0,2.5,-1,0);
    m2.addLine(1.5,1.5,0,0);
    Triangle *a3 = new Triangle(m2, 0,0,0);

    qDebug() << a1->isUnderTrianglePlane(a3);
    LineSegment *ls = a3->getSide(0);
    qDebug() << "x = " << ls->getCoord(0,0) << "y = " << ls->getCoord(0,1) << "z = " << ls->getCoord(0,2);
    qDebug() << "x = " << ls->getCoord(1,0) << "y = " << ls->getCoord(1,1) << "z = " << ls->getCoord(1,2);
    qDebug() << a1->doesIntersectPlane(ls);*/
    return a.exec();
}
