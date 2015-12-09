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
    bool debug = false;
    if (debug) qDebug() << "LightedSurface::addTriangleToSorted";
    /*
     * Добавляем с учетом условия Z(j)_max <= Z(j+1)_min, проверяем обратное условие, если оно выполняется,
     * то переходим на проверку со следующим элементом, иначе разрешаем противоречия.
     * Если они неразрешимы, то делим реугольник на части и рекурсивно запускаем функцию добавления.
     */
    //QLinkedListIterator<Triangle*> it(sortedTriangles);
    //it.toFront();
    QLinkedList<Triangle*>::iterator it;
    //if (!it.hasNext()) { qDebug() << "hasn't next element!"; return;}
    Triangle *triangle_j;
    bool isAdded = false;

//    for (it.toFront(); it.hasNext(); triangle_j = it.next())
    for (it = sortedTriangles.begin(); it != sortedTriangles.end(); ++it)
    {
        triangle_j = *it;
        //triangle_j = triangle_j_it;
        //triangle_j = (*triangle_j_it);
        if (triangle->getZmax() < triangle_j->getZmin()) // Zmax < Zmin_j
        {
            if (debug) qDebug() << "Zmax < Zmin_j";
            sortedTriangles.insert(it, triangle);
            isAdded = true;
            break;
        } else
        {
            if (triangle_j->getZmax() < triangle->getZmin()) //должен стоять дальше по списку, продолжаем поиск места;
            {
                if (debug) qDebug() << "должен стоять дальше по списку, продолжаем поиск места";
                continue;
            } else
            {
                //необходимо разрешить противоречия
                if (triangle->isToRightOrToLeft(triangle_j) || triangle->isAboveOrBelow(triangle_j)) //оболочки не пересекаются по координате X
                {
                    sortedTriangles.insert(it, triangle); //игнорируем противоречие
                    isAdded = true;
                    if (debug) qDebug() << "игнорируем противоречие";
                    break; //не надо ли со следующими проверить?
                } else
                {
                    if (debug) qDebug() << "проверка, лежат ли треугольники один за плоскостью другого";
                    //проверка, лежат ли треугольники один за плоскостью другого
                    if (triangle->isUnderTrianglePlane(triangle_j))
                    {
                        sortedTriangles.insert(it, triangle); //игнорируем противоречие
                        isAdded = true;
                        if (debug) qDebug() << "лежит за плоскостью";
                        break;
                    } else
                    {
                        if (triangle_j->isUnderTrianglePlane(triangle))
                        {
                            if (debug) qDebug() << "треугольник выше текущего, нужно искать место дальше";
                            //треугольник выше текущего, нужно искать место дальше
                            continue;
                        } else
                        {
                            if (debug) qDebug() << "все плохо, надо искать пересечение";
                            //все плохо, надо искать пересечение
                            Triangle *newTriangle1;
                            Triangle *newTriangle2;
                            Triangle *newTriangle3;
                            QVector<int> n_intersections; //список сторон. пересекающих плоскость
                            for (int j = 0; j < 3; j++)
                            {
                                if (triangle_j->doesIntersectPlane(triangle->getSide(j)))
                                {
                                    if (debug) qDebug() << triangle->getSide(j)->getCoord(0,0) << " " << triangle->getSide(j)->getCoord(0,1);
                                    n_intersections.push_back(j);
                                }
                            } // по идее их всегда две (ну почти всегда)
                            if (debug) qDebug() << "n_intersections.size()" << n_intersections.size();
                            //поиск точек пересечения
                            if (n_intersections.size() == 0)
                            {
                                sortedTriangles.insert(it, triangle); //игнорируем противоречие
                                isAdded = true;
                                break;
                            }
                            QVector<double> t_intersections; //список точек пересечения плоскости
                            for (int j = 0; j < n_intersections.size(); j++)
                            {
                                double t_intersect = triangle_j->getPlaneIntersectPoint(triangle->getSide(n_intersections[j]));
                                t_intersections.push_back(t_intersect);
                                if (t_intersect == -1)
                                {
                                    sortedTriangles.insert(it, triangle); //игнорируем противоречие
                                    isAdded = true;
                                    return;
                                }
                                if (debug) qDebug() << n_intersections[j] << " " << t_intersect;

                            }
                            //return; //debug;
                            if (n_intersections[0] == 0)
                            {
                                LineSegment *side0 = triangle->getSide(0);
                                double newX = side0->getX(t_intersections[0]);
                                double newY = side0->getY(t_intersections[0]);
                                double newZ = side0->getZ(t_intersections[0]);

                                if (n_intersections[1] == 1)
                                {
                                    Matrix m1;
                                    m1.addLine(triangle->getCoord(0,0), triangle->getCoord(0,1), triangle->getCoord(0,2), 0);
                                    m1.addLine(newX, newY, newZ, 0);
                                    m1.addLine(triangle->getCoord(2,0), triangle->getCoord(2,1), triangle->getCoord(2,2), 0);
                                    newTriangle1 = new Triangle(m1, 0,0,0);

                                    LineSegment *side1 = triangle->getSide(1);
                                    double newX2 = side1->getX(t_intersections[1]);
                                    double newY2 = side1->getY(t_intersections[1]);
                                    double newZ2 = side1->getZ(t_intersections[1]);
                                    Matrix m2;
                                    m2.addLine(newX, newY, newZ, 0);
                                    m2.addLine(newX2, newY2, newZ2, 0);
                                    m2.addLine(triangle->getCoord(2,0), triangle->getCoord(2,1), triangle->getCoord(2,2), 0);
                                    newTriangle2 = new Triangle(m2, 0,0,0);

                                    Matrix m3;
                                    m3.addLine(newX, newY, newZ, 0);
                                    m3.addLine(triangle->getCoord(1,0), triangle->getCoord(1,1), triangle->getCoord(1,2), 0);
                                    m3.addLine(newX2, newY2, newZ2, 0);
                                    newTriangle3 = new Triangle(m3, 0,0,0);
                                } else
                                {
                                    Matrix m1;
                                    LineSegment *side2 = triangle->getSide(2);
                                    double newX2 = side2->getX(t_intersections[1]);
                                    double newY2 = side2->getY(t_intersections[1]);
                                    double newZ2 = side2->getZ(t_intersections[1]);
                                    m1.addLine(newX2, newY2, newZ2, 0);
                                    m1.addLine(triangle->getCoord(1,0), triangle->getCoord(1,1), triangle->getCoord(1,2), 0);
                                    m1.addLine(triangle->getCoord(2,0), triangle->getCoord(2,1), triangle->getCoord(2,2), 0);
                                    newTriangle1 = new Triangle(m1, 0,0,0);

                                    Matrix m2;
                                    m2.addLine(newX, newY, newZ, 0);
                                    m2.addLine(triangle->getCoord(1,0), triangle->getCoord(1,1), triangle->getCoord(1,2), 0);
                                    m2.addLine(newX2, newY2, newZ2, 0);
                                    newTriangle2 = new Triangle(m2, 0,0,0);

                                    Matrix m3;
                                    m3.addLine(triangle->getCoord(0,0), triangle->getCoord(0,1), triangle->getCoord(0,2), 0);
                                    m3.addLine(newX, newY, newZ, 0);
                                    m3.addLine(newX2, newY2, newZ2, 0);
                                    newTriangle3 = new Triangle(m3, 0,0,0);
                                }
                            } else
                            {
                                LineSegment *side1 = triangle->getSide(1);
                                double newX = side1->getX(t_intersections[0]);
                                double newY = side1->getY(t_intersections[0]);
                                double newZ = side1->getZ(t_intersections[0]);

                                LineSegment *side2 = triangle->getSide(2);
                                double newX2 = side2->getX(t_intersections[1]);
                                double newY2 = side2->getY(t_intersections[1]);
                                double newZ2 = side2->getZ(t_intersections[1]);

                                Matrix m1;
                                m1.addLine(triangle->getCoord(0,0), triangle->getCoord(0,1), triangle->getCoord(0,2), 0);
                                m1.addLine(triangle->getCoord(1,0), triangle->getCoord(1,1), triangle->getCoord(1,2), 0);
                                m1.addLine(newX, newY, newZ, 0);
                                newTriangle1 = new Triangle(m1, 0,0,0);

                                Matrix m2;
                                m2.addLine(triangle->getCoord(0,0), triangle->getCoord(0,1), triangle->getCoord(0,2), 0);
                                m2.addLine(newX, newY, newZ, 0);
                                m2.addLine(newX2, newY2, newZ2, 0);
                                newTriangle2 = new Triangle(m2, 0,0,0);

                                Matrix m3;
                                m3.addLine(newX2, newY2, newZ2, 0);
                                m3.addLine(newX, newY, newZ, 0);
                                m3.addLine(triangle->getCoord(2,0), triangle->getCoord(2,1), triangle->getCoord(2,2), 0);
                                newTriangle3 = new Triangle(m3, 0,0,0);
                            }

                            //рекурсия типа
                            addTriangleToSorted(newTriangle1);
                            addTriangleToSorted(newTriangle2);
                            addTriangleToSorted(newTriangle3);
                            break;
                        }
                    }
                }
            }
        }
    }
    if (!isAdded)
    {
        sortedTriangles.push_back(triangle);
    }
}

LightedSurface::LightedSurface()
{
    //this->triangles
    this->figure = NULL;
    this->originalFigure = NULL;
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
    /*delete figure;
    delete originalFigure;
    while (triangles.size() > 0)
    {
        delete triangles[0];
        triangles.removeFirst();
    }
    while (sortedTriangles.size() > 0)
    {
        delete sortedTriangles.takeFirst();
        sortedTriangles.removeFirst();
    }*/
}

