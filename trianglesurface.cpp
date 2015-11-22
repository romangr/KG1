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
    //creating list of edges
    for (int i = 0; i < this->figure->getSize(); i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (this->figure->edgeExist(i,j))
            {
                double x1 = figure->getCoord(i,0);
                double y1 = figure->getCoord(i,1);
                double z1 = figure->getCoord(i,2);

                double x2 = figure->getCoord(j,0);
                double y2 = figure->getCoord(j,1);
                double z2 = figure->getCoord(j,2);

                LineSegment *ls = new LineSegment(x1, y1, z1, x2, y2, z2);
                this->lineSegments.append(ls);
            }
        }
    }
    qDebug() << "edges count = " << this->lineSegments.size();
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
    Figure *f = new Figure();
    for (int i = 0; i < this->lineSegments.size(); i++)
    {
        LineSegment *currentLS = lineSegments[i];
        for (int j = 0; j < this->triangles.size(); j++)
        {
            Triangle *currentTr = triangles[j];
            //лежат ли все точки отрезка за точками треугольника?
            if (this->triangles.at(j)->isBehindTriangle(this->lineSegments.at(i)->getZ(0)) && this->triangles.at(j)->isBehindTriangle(this->lineSegments.at(i)->getZ(1)))
            {
                //алгоритм отсечения отрезка выпуклым окном наоборот
            } else
            {
                //лежат ли все точки отрезка перед точками треугольника?
                if (currentTr->isInFrontOfTriangle(currentLS->getCoord(0,2)) && currentTr->isInFrontOfTriangle(currentLS->getCoord(1,2)))
                {
                    //отрезок перед треугольником, можно рисовать
                    continue;
                }
                //пересекает ли отрезок проекцию треугольника?
                QVector<double> t_intersections;
                QVector<int> n_intersections;
                double x1 = currentTr->getCoord(0,0); double x2 = currentTr->getCoord(1,0); double x3 = currentTr->getCoord(2, 0);
                double y1 = currentTr->getCoord(0,1); double y2 = currentTr->getCoord(1,1); double y3 = currentTr->getCoord(2, 1);
                double z1 = currentTr->getCoord(0,2); double z2 = currentTr->getCoord(1,2); double z3 = currentTr->getCoord(2, 2);
                double dx = currentLS->getCoord(2,0); double dy = currentLS->getCoord(2,1);
                double delta = -(y2 - y1)*dx + (x2 - x1)*dy;
                double delta1 = -(x1 - currentLS->getCoord(0,0))*(y2-y1) + (x2 - x1)*(y1 - currentLS->getCoord(0,1));
                double t_p = delta1 / delta;
                if (t_p >= 0 && t_p <= 1) {t_intersections.push_back(t_p); n_intersections.push_back(0);}

                delta = -(y3 - y2)*dx + (x3 - x2)*dy;
                delta1 = -(x2 - currentLS->getCoord(0,0))*(y3-y2) + (x3 - x2)*(y2 - currentLS->getCoord(0,1));
                t_p = delta1 / delta;
                if (t_p >= 0 && t_p <= 1) {t_intersections.push_back(t_p); n_intersections.push_back(1);}

                delta = -(y3 - y1)*dx + (x3 - x1)*dy;
                delta1 = -(x1 - currentLS->getCoord(0,0))*(y3-y1) + (x3 - x1)*(y1 - currentLS->getCoord(0,1));
                t_p = delta1 / delta;
                if (t_p >= 0 && t_p <= 1) {t_intersections.push_back(t_p); n_intersections.push_back(2);}

                if (t_intersections.size() > 0)
                {
                    //пересекает проекцию, знаем точки
                    //проверить точки пересечения на положение относительно плоскости треугольника
                    //если отрезок пересекает проекцию два раза, можно сделать вывод о пересечении отрезком плоскости (внутри) треугольника
                    //иначе нужно провести тест
                    //пересекает ли отрезок плоскость треугольника?
                    bool flag[2] = {false, false};
                    if (t_intersections.size() > 1)
                    {
                        //имеем две точки пересечения
                        for (int k1 = 0; k1 < 2; k1++)
                        {
                            double x_p = currentLS->getX(t_intersections[k1]);
                            double z_p = currentLS->getZ(t_intersections[k1]);
                            LineSegment *side;
                            switch (n_intersections[k1]) {
                            case 0: side = new LineSegment(x1, y1, z1, x2, y2, z2); break;
                            case 1: side = new LineSegment(x2, y2, z2, x3, y3, z3); break;
                            case 2: side = new LineSegment(x1, y1, z1, x3, y3, z3); break;
                            }
                            double z_tr = side->getZ(side->getTbyX(x_p));
                            delete(side);
                            if (z_tr < z_p) {flag[k1] = true;}
                        }
                        if (flag[0] && flag[1])
                        {
                            //треугольник за отрезком, можно рисовать
                            continue;
                        }
                        if (!flag[0] && !flag[1])
                        {
                            //кусок отрезка за треугольником, надо вырезать
                            if (t_intersections[0] < t_intersections[1])
                            {
                                currentLS->addIntersection(t_intersections[0], t_intersections[1]);
                            } else
                            {
                                currentLS->addIntersection(t_intersections[1], t_intersections[0]);
                            }
                            continue;
                        }
                    }
                    //одно пересечение или неопределенность с двумя
                    double A = y1*(z2 - z3) + y2*(z3 - z1) + y3*(z1 - z2);
                    double B = z1*(x2 - x3) + z2*(x3 - x1) + z3*(x1 - x2);
                    double C = x1*(y2 - y3) + x2*(y3 - y1) + x3*(y1 - y2);
                    double D = x1*(y2*z3 - y3*z2) + x2*(y3*z1 - y1*z3) + x3*(y1*z2 - y2*z1);
                    D = -D;
                    double testFunctionBeginning = A*currentLS->getCoord(0,0) + B*currentLS->getCoord(0,1) + C*currentLS->getCoord(0,2) + D;
                    double testFunctionEnd = A*currentLS->getCoord(1,0) + B*currentLS->getCoord(1,1) + C*currentLS->getCoord(1,2) + D;
                    if (testFunctionBeginning * testFunctionEnd < 0)
                    {
                        //таки пересекает, надо искать точку пересечения
                        double t_intresect = (A*currentLS->getCoord(0,0) + B*currentLS->getCoord(0,1) + C*currentLS->getCoord(0,2) + D)/
                                (A*currentLS->getCoord(2,0) + B*currentLS->getCoord(2,1) + C*currentLS->getCoord(2,2));
                        if (t < 0 || t > 1) {qDebug() << "It's impossible!";}
                        //находится ли точка внутри треугольника? (в его проекции на плоскость визуализации)
                        if (currentTr->isInProjection(currentLS->getX(t_intresect), currentLS->getY(t_intresect)))
                        {
                            //случай с одной точкой
                            if (t_intersections.size() == 1)
                           {    /* точка внутри треугольника, надо проверить точку пересечения со стороной:
                                * когда она выше стороны треугольника, не рисуем с точки пересечения с плоскостью и до конца;
                                * в противном случае не рисуем от точки пересечения со стороной до точки пересечения с плоскостью
                                */
                                double x_p = currentLS->getX(t_intersections[0]); //координаты отрезка точке пересечения со стороной
                                double z_p = currentLS->getZ(t_intersections[0]);
                                LineSegment *side;
                                switch (n_intersections[0]) {
                                case 0: side = new LineSegment(x1, y1, z1, x2, y2, z2); break;
                                case 1: side = new LineSegment(x2, y2, z2, x3, y3, z3); break;
                                case 2: side = new LineSegment(x1, y1, z1, x3, y3, z3); break;
                                }
                                double z_tr = side->getZ(side->getTbyX(x_p)); //координата стороны в точке пересечения с отрезком
                                if (z_tr < z_p)
                                {
                                    if (t_intersect > t_intersections[0])
                                    {
                                        currentLS->addIntersection(t_intresect, 1);
                                    } else
                                    {
                                        currentLS->addIntersection(0, t_intresect;
                                    }
                                } else
                                {
                                    if (t_intersections[0] > t_intresect)
                                    {
                                        currentLS->addIntersection(t_intresect, t_intersections[0]);
                                    } else
                                    {
                                        currentLS->addIntersection(t_intersections[0], t_intresect);
                                    }
                                }
                                delete(side);
                                continue;
                            } else //неопределенность с двумя точками
                            {
                                /* не рисуем от точки пересечения с плоскостью до нижней точки;
                                 * т.е. от t_intersect до точки с флагом false */
                                if (!flag[0])
                                {
                                    if (t_intresect > t_intersections[0])
                                    {
                                        currentLS->addIntersection(t_intersections[0], t_intresect);
                                    } else
                                    {
                                        currentLS->addIntersection(t_intresect, t_intersections[0]);
                                    }
                                } else
                                {
                                    if (t_intresect > t_intersections[1])
                                    {
                                        currentLS->addIntersection(t_intersections[1], t_intresect);
                                    } else
                                    {
                                        currentLS->addIntersection(t_intresect, t_intersections[1]);
                                    }
                                }
                                continue;
                            }
                        }

                    }
                } else 
                {
                    //нет точек пересечения с проекцией
                    continue;
                }
            }
        }
    }
    return f;
}

TriangleSurface::~TriangleSurface()
{
    for (int j = 0; j < N*N*2; j++)
    {
        delete(triangles[j]);
    }
    delete(figure);
}

