#include "trianglesurface.h"
#include <QDebug>

TriangleSurface::TriangleSurface(RuledSurface &r)
{

    N = 16;
    this->surface = &r;

    this->figure = this->surface->getFigure(N);


    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            Matrix abc;
            double ax = figure->getCoord(i*(N+1) + j, 0);
            double ay = figure->getCoord(i*(N+1) + j, 1);
            double az = figure->getCoord(i*(N+1) + j, 2);

            double bx = figure->getCoord((i+1)*(N+1) + j, 0);
            double by = figure->getCoord((i+1)*(N+1) + j, 1);
            double bz = figure->getCoord((i+1)*(N+1) + j, 2);

            double cx = figure->getCoord(i*(N+1) + j + 1, 0);
            double cy = figure->getCoord(i*(N+1) + j + 1, 1);
            double cz = figure->getCoord(i*(N+1) + j + 1, 2);
            qDebug() << "ax = " << ax << "ay = " << ay << "az = " << az;
            qDebug() << "bx = " << bx << "by = " << by << "bz = " << bz;
            qDebug() << "cx = " << cx << "cy = " << cy << "cz = " << cz;
            abc.addLine(ax, ay, az, 0);
            abc.addLine(bx, by, bz, 0);
            abc.addLine(cx, cy, cz, 0);

            Triangle *tr = new Triangle(abc, i*(N+1) + j, (i+1)*(N+1) + j, i*(N+1) + j + 1);

            triangles.push_back(tr);

            Matrix def;
            double dx = figure->getCoord(i*(N+1) + j + 1, 0);
            double dy = figure->getCoord(i*(N+1) + j + 1, 1);
            double dz = figure->getCoord(i*(N+1) + j + 1, 2);

            double ex = figure->getCoord((i+1)*(N+1) + j + 1, 0);
            double ey = figure->getCoord((i+1)*(N+1) + j + 1, 1);
            double ez = figure->getCoord((i+1)*(N+1) + j + 1, 2);

            double fx = figure->getCoord((i+1)*(N+1) + j, 0);
            double fy = figure->getCoord((i+1)*(N+1) + j, 1);
            double fz = figure->getCoord((i+1)*(N+1) + j, 2);

            def.addLine(dx, dy, dz, 0);
            def.addLine(ex, ey, ez, 0);
            def.addLine(fx, fy, fz, 0);

            tr = new Triangle(def, i*(N+1) + j + 1, (i+1)*(N+1) + j + 1, (i+1)*(N+1) + j);

            triangles.push_back(tr);
        }
    }
}

void TriangleSurface::turn(char axis, double angle)
{
    this->figure->turn(axis, angle);

    for (int j = 0; j < N*N*2; j++)
    {
        Triangle *tr = triangles[0];
        triangles.removeAt(0);
        delete(tr);
    }


    for (int i = 0; i < (N); i++)
    {
        for (int j = 0; j < (N); j++)
        {
            Matrix abc;
            double ax = figure->getCoord(i*(N+1) + j, 0);
            double ay = figure->getCoord(i*(N+1) + j, 1);
            double az = figure->getCoord(i*(N+1) + j, 2);

            double bx = figure->getCoord((i+1)*(N+1) + j, 0);
            double by = figure->getCoord((i+1)*(N+1) + j, 1);
            double bz = figure->getCoord((i+1)*(N+1) + j, 2);

            double cx = figure->getCoord(i*(N+1) + j + 1, 0);
            double cy = figure->getCoord(i*(N+1) + j + 1, 1);
            double cz = figure->getCoord(i*(N+1) + j + 1, 2);

            abc.addLine(ax, ay, az, 0);
            abc.addLine(bx, by, bz, 0);
            abc.addLine(cx, cy, cz, 0);

            Triangle *tr = new Triangle(abc, i*(N+1) + j, (i+1)*(N+1) + j, i*(N+1) + j + 1);

            triangles.push_back(tr);

            Matrix def;
            double dx = figure->getCoord(i*(N+1) + j + 1, 0);
            double dy = figure->getCoord(i*(N+1) + j + 1, 1);
            double dz = figure->getCoord(i*(N+1) + j + 1, 2);

            double ex = figure->getCoord((i+1)*(N+1) + j + 1, 0);
            double ey = figure->getCoord((i+1)*(N+1) + j + 1, 1);
            double ez = figure->getCoord((i+1)*(N+1) + j + 1, 2);

            double fx = figure->getCoord((i+1)*(N+1) + j, 0);
            double fy = figure->getCoord((i+1)*(N+1) + j, 1);
            double fz = figure->getCoord((i+1)*(N+1) + j, 2);

            def.addLine(dx, dy, dz, 0);
            def.addLine(ex, ey, ez, 0);
            def.addLine(fx, fy, fz, 0);

            tr = new Triangle(def, i*(N+1) + j + 1, (i+1)*(N+1) + j + 1, (i+1)*(N+1) + j);

            triangles.push_back(tr);
        }
    }
}

Figure *TriangleSurface::getVisibleFigure()
{
    Figure *f = this->figure->getCopy();
    int count = 0;
    for (int i = 0; i < (N*N); i++)
    {
        double x = f->getCoord(i, 0);
        double y = f->getCoord(i, 1);
        double z = f->getCoord(i, 2);

        for (int j = 0; j < N*N*2; j++)
        {
            if (triangles.at(j)->isApex(i)) {/*qDebug() << "continued";*/  continue;}
            if (triangles.at(j)->isUnderTriangle(x, y, z))
            {
                f->cutPoint(i);
                count++;
                qDebug() << "apex #" << i << " triangle:" << triangles[j]->pointNumbers.getElement(0,0);// << " " << triangles[j]->pointNumbers.getElement(0,1)<< " " << triangles[j].getElement(0,2);
                qDebug() << "#" << count;
                break;
            }
        }
    }
    qDebug() << count << " вершин вырезано";
    return f;
}

TriangleSurface::~TriangleSurface()
{
    for (int j = 0; j < N*N*2; j++)
    {
        delete(triangles[j]);
    }
}

