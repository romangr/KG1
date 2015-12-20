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
            //qDebug() << tr->getNormal(0) << " " << tr->getNormal(1) << " " << tr->getNormal(2);

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

    pointsCount = (N+1)*(N+1) - 1;
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

void LightedSurface::addTriangleToSorted(Triangle *triangle, bool debug)
{
    //bool debug = false;
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
                //есть ли общее ребро?
                if (triangle_j->hasMutualEdge(triangle))
                {
                    if (triangle->getZmin() < triangle_j->getZmin())
                    {
                        if (debug) qDebug() << "mutual edge triangle added before";
                        sortedTriangles.insert(it, triangle);
                        isAdded = true;
                        break;
                    } else
                    {
                        if (debug) qDebug() << "mutual edge triangle continued";
                        continue;
                    }
                }
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
                                if (t_intersect == -1 || fabs(t_intersect < 0.0001))
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
                                    newTriangle1 = new Triangle(m1, triangle->pointNumbers.getElement(0,0), ++pointsCount, triangle->pointNumbers.getElement(0,2));
                                    newTriangle1->setNormal(triangle);

                                    LineSegment *side1 = triangle->getSide(1);
                                    double newX2 = side1->getX(t_intersections[1]);
                                    double newY2 = side1->getY(t_intersections[1]);
                                    double newZ2 = side1->getZ(t_intersections[1]);
                                    Matrix m2;
                                    m2.addLine(newX, newY, newZ, 0);
                                    m2.addLine(newX2, newY2, newZ2, 0);
                                    m2.addLine(triangle->getCoord(2,0), triangle->getCoord(2,1), triangle->getCoord(2,2), 0);
                                    newTriangle2 = new Triangle(m2, pointsCount, ++pointsCount, triangle->pointNumbers.getElement(0,2));
                                    newTriangle2->setNormal(triangle);

                                    Matrix m3;
                                    m3.addLine(newX, newY, newZ, 0);
                                    m3.addLine(triangle->getCoord(1,0), triangle->getCoord(1,1), triangle->getCoord(1,2), 0);
                                    m3.addLine(newX2, newY2, newZ2, 0);
                                    newTriangle3 = new Triangle(m3, pointsCount-1,triangle->pointNumbers.getElement(0,1), pointsCount);
                                    newTriangle3->setNormal(triangle);
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
                                    newTriangle1 = new Triangle(m1, ++pointsCount, triangle->pointNumbers.getElement(0,1), triangle->pointNumbers.getElement(0,2));
                                    newTriangle1->setNormal(triangle);

                                    Matrix m2;
                                    m2.addLine(newX, newY, newZ, 0);
                                    m2.addLine(triangle->getCoord(1,0), triangle->getCoord(1,1), triangle->getCoord(1,2), 0);
                                    m2.addLine(newX2, newY2, newZ2, 0);
                                    newTriangle2 = new Triangle(m2, ++pointsCount, triangle->pointNumbers.getElement(0,1), pointsCount-1);
                                    newTriangle2->setNormal(triangle);

                                    Matrix m3;
                                    m3.addLine(triangle->getCoord(0,0), triangle->getCoord(0,1), triangle->getCoord(0,2), 0);
                                    m3.addLine(newX, newY, newZ, 0);
                                    m3.addLine(newX2, newY2, newZ2, 0);
                                    newTriangle3 = new Triangle(m3, triangle->pointNumbers.getElement(0,0), pointsCount, pointsCount-1);
                                    newTriangle3->setNormal(triangle);
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
                                newTriangle1 = new Triangle(m1, triangle->pointNumbers.getElement(0,0), triangle->pointNumbers.getElement(0,1), ++pointsCount);
                                newTriangle1->setNormal(triangle);

                                Matrix m2;
                                m2.addLine(triangle->getCoord(0,0), triangle->getCoord(0,1), triangle->getCoord(0,2), 0);
                                m2.addLine(newX, newY, newZ, 0);
                                m2.addLine(newX2, newY2, newZ2, 0);
                                newTriangle2 = new Triangle(m2, triangle->pointNumbers.getElement(0,0), pointsCount, ++pointsCount);
                                newTriangle2->setNormal(triangle);

                                Matrix m3;
                                m3.addLine(newX2, newY2, newZ2, 0);
                                m3.addLine(newX, newY, newZ, 0);
                                m3.addLine(triangle->getCoord(2,0), triangle->getCoord(2,1), triangle->getCoord(2,2), 0);
                                newTriangle3 = new Triangle(m3, pointsCount, pointsCount-1, triangle->pointNumbers.getElement(0,2));
                                newTriangle3->setNormal(triangle);
                            }

                            //рекурсия типа
                            addTriangleToSorted(newTriangle1, true);
                            addTriangleToSorted(newTriangle2, true);
                            addTriangleToSorted(newTriangle3, true);
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
    this->illuminant[0] = -500;
    this->illuminant[1] = 100;
    this->illuminant[2] = 400;
    qDebug() << "triangles count = " << this->triangles.size();
}

void LightedSurface::turn(char axis, double angle)
{
    this->figure->turn(axis, angle);
    while (triangles.size() > 0)
    {
        delete triangles[0];
        triangles.removeFirst();
    }
    sortedTriangles.clear();
    /*while (sortedTriangles.size() > 0)
    {
        delete sortedTriangles.takeFirst();
        sortedTriangles.removeFirst();
    }*/
    this->fillTriangles();
}

Figure *LightedSurface::getFigure()
{

    Figure *f = new Figure();
    for (int i = 0; i < triangles.size(); i++)
    {
        this->addTriangleToSorted(triangles[i]);
    }
    //qDebug() << "lighted figure";
    QLinkedListIterator<Triangle*> it(this->sortedTriangles);
    //it.toFront();
    //int j = 0;
    while (it.hasNext()/* && j < sortedTriangles.size()*/)
    {
        Triangle *currentTr = it.next();
        int figureSize = f->getSize();
        f->addPoint(currentTr->getCoord(0,0), currentTr->getCoord(0,1), currentTr->getCoord(0,2));
        f->addPoint(currentTr->getCoord(1,0), currentTr->getCoord(1,1), currentTr->getCoord(1,2));
        f->setEdge(figureSize+1, figureSize+2, 1);
        f->addPoint(currentTr->getCoord(2,0), currentTr->getCoord(2,1), currentTr->getCoord(2,2));
        f->setEdge(figureSize+1, figureSize+3, 1);
        f->setEdge(figureSize+2, figureSize+3, 1);
        //j++;
    }
    return f;
}

TriangleFigure *LightedSurface::getLightedFigure()
{
    double PI = 3.1415;
    TriangleFigure *f = new TriangleFigure();
    for (int i = 0; i < triangles.size(); i++)
    {
        this->addTriangleToSorted(triangles[i]);
    }

    QVectorIterator<Triangle*> it1(this->triangles);
    while (it1.hasNext())
    {   //angle = angle * PI / 180;
        Triangle *currentTr = it1.next();
        double lx = illuminant[0];//-currentTr->getCoord(0,0);
        double ly = illuminant[1];//-currentTr->getCoord(0,1);
        double lz = illuminant[2];//-currentTr->getCoord(0,1);
        double l_norma = sqrt(pow(lx, 2) + pow(ly, 2) + pow(lz, 2));
        double lp_norma = sqrt(pow(lx, 2) + pow(lz, 2));
        double alpha = acos(lz/lp_norma)*180/PI;
        double gamma = acos((pow(lx, 2) + pow(lz, 2))/(l_norma*lp_norma))*180/PI;
        Figure triangle;
        triangle.addPoint(currentTr->getCoord(0,0), currentTr->getCoord(0,1), currentTr->getCoord(0,2));
        triangle.addPoint(currentTr->getCoord(1,0), currentTr->getCoord(1,1), currentTr->getCoord(1,2));
        triangle.addPoint(currentTr->getCoord(2,0), currentTr->getCoord(2,1), currentTr->getCoord(2,2));
        triangle.turn(1, -alpha);
        triangle.turn(0, -gamma);
        triangle.editPoint(1, triangle.getCoord(0,1), triangle.getCoord(0,2), -500);
        triangle.editPoint(2, triangle.getCoord(1,1), triangle.getCoord(1,2), -500);
        triangle.editPoint(3, triangle.getCoord(2,1), triangle.getCoord(2,2), -500);
        triangle.turn(0, gamma);
        triangle.turn(1, alpha);
        Matrix m;
        m.addLine(triangle.getCoord(0,0), triangle.getCoord(0,1), triangle.getCoord(0,2), 0);
        m.addLine(triangle.getCoord(1,0), triangle.getCoord(1,1), triangle.getCoord(1,2), 0);
        m.addLine(triangle.getCoord(2,0), triangle.getCoord(2,1), triangle.getCoord(2,2), 0);
        Triangle *shadowTriangle = new Triangle(m, 0,0,0);
        shadowTriangle->setBrightness(0);
        f->addTriangle(shadowTriangle);
        delete shadowTriangle;
    }
    QLinkedListIterator<Triangle*> it(this->sortedTriangles);
    it.toFront();
    while (it.hasNext())
    {
        Triangle *currentTr = it.next();
        //расчет освещенности
        //перенос ЛСК
        double lx = illuminant[0]-currentTr->getCoord(0,0);
        double ly = illuminant[1]-currentTr->getCoord(0,1);
        double lz = illuminant[2]-currentTr->getCoord(0,1);
        Figure l;
        l.addPoint(lx, ly, lz);
        Matrix parallelTransfer;
        parallelTransfer.addLine(1, 0, 0, 0);
        parallelTransfer.addLine(0, 1, 0, 0);
        parallelTransfer.addLine(0, 0, 1, 0);
        parallelTransfer.addLine(-currentTr->getCoord(0,0), -currentTr->getCoord(0,1), -currentTr->getCoord(0,2), 1);
        l.transform(parallelTransfer);
        double norma = sqrt(pow(currentTr->getNormal(0), 2) + pow(currentTr->getNormal(2), 2));
        double alpha = acos(currentTr->getNormal(2) / norma)*180/PI;
        norma *= sqrt(pow(currentTr->getNormal(0), 2) + pow(currentTr->getNormal(1), 2) + pow(currentTr->getNormal(2), 2));
        double gamma = acos((pow(currentTr->getNormal(0), 2) + pow(currentTr->getNormal(2), 2)) / norma)*180/PI;
        l.turn(1, -alpha);
        l.turn(0, -gamma);
        l.editPoint(1, -l.getCoord(0,0), -l.getCoord(0,1), l.getCoord(0,2));
        l.turn(0, gamma);
        l.turn(1, alpha);
        parallelTransfer.deleteLine(3);
        parallelTransfer.addLine(currentTr->getCoord(0,0), currentTr->getCoord(0,1), currentTr->getCoord(0,2), 1);
        l.transform(parallelTransfer);
        double kA = 0.35;
        double kS = 0.6;
        double kD = 0.1;
        double intense = 300;
        norma = sqrt(pow(currentTr->getNormal(0), 2) + pow(currentTr->getNormal(1), 2) + pow(currentTr->getNormal(2), 2));
        double cosT = (currentTr->getNormal(0)*lx + currentTr->getNormal(1)*ly + currentTr->getNormal(2)*lz) /
                (norma * sqrt(pow(lx, 2) + pow(ly, 2) + pow(lz, 2)));
        double cosA = (l.getCoord(0,2))/(sqrt(pow(lx, 2) + pow(ly, 2) + pow(lz, 2)));
        cosA = pow(cosA, 3);
        double r = sqrt(pow(illuminant[0]-currentTr->getCoord(0,0), 2) +
                pow(illuminant[0]-currentTr->getCoord(0,1), 2) + pow(illuminant[0]-currentTr->getCoord(0,2), 2));
        //qDebug() << "r = " << r;
        r = 1;
        double iS = intense*kA + (intense * (kD*cosT + kS*cosA))/pow(r,2);
        //qDebug() << iS;
        //расвет освещенности
        currentTr->setBrightness(iS);
        f->addTriangle(currentTr);
    }
    return f;
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

