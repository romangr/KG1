#include "lightedsurface.h"

void LightedSurface::fillTriangles()
{
    while (triangles.size() > 0)
    {
        delete triangles[0];
        triangles.removeFirst();
    }
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

            abc.addLine(ax, ay, az, 0);
            abc.addLine(bx, by, bz, 0);
            abc.addLine(cx, cy, cz, 0);

            Triangle *tr = new Triangle(abc, i*(N+1) + j, (i+1)*(N+1) + j, i*(N+1) + j + 1);
            tr->setNormal(2, 0, 1, 0);

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
            tr->setNormal(1, 0, 2, 0);

            triangles.push_back(tr);
        }
    }
}

int LightedSurface::getPlaneSide(Triangle *triangle)
{
    //нормаль к OXY Nx = 0; Ny = 0;
    double Nz = -10;
    double norma = sqrt(triangle->getNormal(0)*triangle->getNormal(0) + triangle->getNormal(1)*triangle->getNormal(1)+
                        triangle->getNormal(2)*triangle->getNormal(2));
    double cosA = (triangle->getNormal(2) * Nz) / (norma * 10.0);
    if (fabs(cosA) < 0.00000001) return 1;
    if (cosA < 0)
    {
        return 2;
    } else
    {
        return 1;
    }
}

void LightedSurface::addTriangleToSorted(Triangle *triangle)
{
    /*
     * Добавляем с учетом условия Z(j)_max <= Z(j+1)_min, проверяем обратное условие, если оно выполняется,
     * то переходим на проверку со следующим элементом, иначе разрешаем противоречия.
     * Если они неразрешимы, то делим реугольник на части и рекурсивно запускаем функцию добавления.
     */
}

LightedSurface::LightedSurface()
{

}

LightedSurface::LightedSurface(RuledSurface &r, int N)
{
    this->N = N;
    this->surface = &r;
    if (this->surface == NULL)
    {
        qDebug() << "Ошибка задания поверхности, указатель на нее нулевой";
    }
    this->originalFigure = this->surface->getFigure(N);
    this->figure = this->originalFigure->getCopy();
    //this->figure->roundCoords();
    this->fillTriangles();
    qDebug() << "triangles count = " << this->triangles.size();
}


LightedSurface::~LightedSurface()
{
    delete figure;
    delete originalFigure;
    while (triangles.size() > 0)
    {
        delete triangles[0];
        triangles.removeFirst();
    }
    while (sortedTriangles.size() > 0)
    {
        delete sortedTriangles[0];
        sortedTriangles.removeFirst();
    }
}

