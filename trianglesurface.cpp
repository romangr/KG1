#include "trianglesurface.h"
#include <QDebug>

TriangleSurface::TriangleSurface(int n)
{
    Matrix trMatrix;
    trMatrix.addLine(-50, 0, 0, 0);
    trMatrix.addLine(50, 0, 0, 0);
    trMatrix.addLine(0, 50, -20, 0);
    Triangle *triangle = new Triangle(trMatrix,0,1,2);
    this->triangles.push_back(triangle);
    //LineSegment *lnSegment = new LineSegment(0, -20, -50, 0, 70, 60); //протыкает
    //LineSegment *lnSegment = new LineSegment(-20, -20, -50, 20, 70, 60);
    LineSegment *lnSegment = new LineSegment(5, 10, -20, 5, 70, -30);
    lnSegment->setFigurePoints(0,5);
    this->lineSegments.push_back(lnSegment);
    debug = true;
}

TriangleSurface::TriangleSurface(RuledSurface &r)
{
    debug = false;
    N = 8;
    this->surface = &r;
    this->figure = this->surface->getFigure(N);
    //this->figure->turn(2,30);

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
            /*qDebug() << "ax = " << ax << "ay = " << ay << "az = " << az;
            qDebug() << "bx = " << bx << "by = " << by << "bz = " << bz;
            qDebug() << "cx = " << cx << "cy = " << cy << "cz = " << cz;*/
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
                ls->setFigurePoints(i, j);
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
        //qDebug() << "i = " << i;
        LineSegment *currentLS = lineSegments[i];
        for (int j = 0; j < this->triangles.size(); j++)
        {
            //qDebug() << "tr.size" << triangles.size();
            //qDebug() << "j = " << j;
            Triangle *currentTr = triangles[j];
            //if (currentTr->isEdge(currentLS)) { continue;}
            if (currentTr->isApex(currentLS->getFigurePoint(0)))
            {
                if (currentTr->isApex(currentLS->getFigurePoint(1)))
                {
                    if (debug) qDebug() << "apex";
                    continue;
                }
            }
            //лежат ли все точки отрезка за точками треугольника?
            if (false)//(this->triangles.at(j)->isBehindTriangle(this->lineSegments.at(i)->getZ(0)) && this->triangles.at(j)->isBehindTriangle(this->lineSegments.at(i)->getZ(1)))
            {
                //алгоритм отсечения отрезка выпуклым окном наоборот
            } else
            {
                if (debug) qDebug() << "always goes";
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
                double delta2 = dx*(y1 - currentLS->getCoord(0,1)) - dy*(x1 - currentLS->getCoord(0,0));
                double t_tr = delta2 / delta;
                double t_p = delta1 / delta;
                //qDebug() << "t_tr = " << t_tr;
                //qDebug() << "t_p = " << t_p;
                if ((t_p >= 0 && t_p <= 1) && (t_tr >= 0 && t_tr <= 1))
                {
                    t_intersections.push_back(t_p); n_intersections.push_back(0);
                }

                delta = -(y3 - y2)*dx + (x3 - x2)*dy;
                delta1 = -(x2 - currentLS->getCoord(0,0))*(y3-y2) + (x3 - x2)*(y2 - currentLS->getCoord(0,1));
                delta2 = dx*(y2 - currentLS->getCoord(0,1)) - dy*(x2 - currentLS->getCoord(0,0));
                t_p = delta1 / delta;
                t_tr = delta2 / delta;

                //qDebug() << "t_tr = " << t_tr;
                //qDebug() << "t_p = " << t_p;
                if ((t_p >= 0 && t_p <= 1) && (t_tr >= 0 && t_tr <= 1))
                {
                    if (t_intersections.size() == 1)
                    {
                        if (t_intersections.at(0) != t_p)
                        {
                            t_intersections.push_back(t_p); n_intersections.push_back(1);
                        } else
                        {
                            if (debug) qDebug() << "попали в вершину";
                        }
                    } else
                    {
                        t_intersections.push_back(t_p); n_intersections.push_back(1);
                    }

                }

                delta = -(y3 - y1)*dx + (x3 - x1)*dy;
                delta1 = -(x1 - currentLS->getCoord(0,0))*(y3-y1) + (x3 - x1)*(y1 - currentLS->getCoord(0,1));
                delta2 = dx*(y1 - currentLS->getCoord(0,1)) - dy*(x1 - currentLS->getCoord(0,0));
                t_p = delta1 / delta;
                t_tr = delta2 / delta;
                //qDebug() << "t_tr = " << t_tr;
                //qDebug() << "t_p = " << t_p;
                if ((t_p >= 0 && t_p <= 1) && (t_tr >= 0 && t_tr <= 1))
                {
                    bool write = true;
                    for (int ij = 0; ij < t_intersections.size(); ij++)
                    {
                        if (t_p == t_intersections.at(ij))
                        {
                            write = false;
                            if (debug) qDebug() << "попали в вершину";
                        }
                    }
                    if (write) t_intersections.push_back(t_p); n_intersections.push_back(2);
                }
                if (debug) qDebug() << "t_intersections.size() = " << t_intersections.size();
                /*for (int kk = 0; kk < t_intersections.size(); kk++)
                {
                    qDebug() << "t_intersections[" << kk << "] = " << t_intersections[kk];
                }*/
                if (t_intersections.size() > 0)
                {
                    //qDebug() << "t_intersections.size() > 0";
                    //пересекает проекцию, знаем точки
                    //проверить точки пересечения на положение относительно плоскости треугольника
                    //если отрезок пересекает проекцию два раза, можно сделать вывод о пересечении отрезком плоскости (внутри) треугольника
                    //иначе нужно провести тест
                    //пересекает ли отрезок плоскость треугольника?
                    bool flag[2] = {false, false};
                    if (t_intersections.size() > 1)
                    {
                        if (debug) qDebug() << "t_intersections.size() == 2";
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
                            if (debug) qDebug() << "треугольник за отрезком, можно рисовать";
                            //треугольник за отрезком, можно рисовать
                            continue;
                        }
                        if (!flag[0] && !flag[1])
                        {
                            if (debug) qDebug() << "кусок отрезка за треугольником, надо вырезать";
                            //кусок отрезка за треугольником, надо вырезать
                            if (t_intersections[0] < t_intersections[1])
                            {
                                //qDebug() << "addIntersection(t_intersections[0], t_intersections[1]);";
                                currentLS->addIntersection(t_intersections[0], t_intersections[1]);
                            } else
                            {
                                //qDebug() << "addIntersection(t_intersections[1], t_intersections[0]);";
                                currentLS->addIntersection(t_intersections[1], t_intersections[0]);
                            }
                            if (debug) qDebug() << "continue";
                            continue;
                        }
                    }
                    if (debug) qDebug() << "одно пересечение или неопределенность с двумя";
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
                         if (debug) qDebug() << "отрезок пересекает плоскость треугольника";
                        //таки пересекает, надо искать точку пересечения
                        double t_intresect = -(A*currentLS->getCoord(0,0) + B*currentLS->getCoord(0,1) + C*currentLS->getCoord(0,2) + D)/
                                (A*currentLS->getCoord(2,0) + B*currentLS->getCoord(2,1) + C*currentLS->getCoord(2,2));
                        if (debug) qDebug() << "t_intresect = " << t_intresect;
                        if (t_intresect < 0 || t_intresect > 1)
                        {
                            if (debug) qDebug() << "It's impossible!";
                            /*qDebug() << "A = " << x1 << " B = " << y1 << " C = " << z1;
                            qDebug() << "A = " << x2 << " B = " << y2 << " C = " << z2;
                            qDebug() << "A = " << x3 << " B = " << y3 << " C = " << z3;
                            qDebug() << "x1 = " << currentLS->getCoord(0, 0) << " y1 = " << currentLS->getCoord(0, 1) << " z1 = " << currentLS->getCoord(0, 2);
                            qDebug() << "x2 = " << currentLS->getCoord(1, 0) << " y2 = " << currentLS->getCoord(1, 1) << " z2 = " << currentLS->getCoord(1, 2);*/
                        }
                        //находится ли точка внутри треугольника? (в его проекции на плоскость визуализации)
                        if (currentTr->isInProjection(currentLS->getX(t_intresect), currentLS->getY(t_intresect)))
                        {
                            if (debug) qDebug() << "отрезок пересекает плоскость треугольника внутри него";
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
                                    //qDebug() << "z_tr < z_p";
                                    if (t_intresect > t_intersections[0])
                                    {
                                        currentLS->addIntersection(t_intresect, 1);
                                    } else
                                    {
                                        currentLS->addIntersection(0, t_intresect);
                                    }
                              } else
                                {
                                    //qDebug() << "z_tr >= z_p";
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
                        } else
                        {
                            //точка пересечения с плоскостью треугольника вне его проекции
                            //если точка пересечения со стороной под треугольником, значит с этой точки не рисуем
                            //если над стороной, то рисуем полностью
                            double x_p1 = currentLS->getX(t_intersections[0]); //координаты отрезка точке пересечения со стороной
                            double z_p1 = currentLS->getZ(t_intersections[0]);
                            LineSegment *side1;
                            switch (n_intersections[0]) {
                            case 0: side1 = new LineSegment(x1, y1, z1, x2, y2, z2); break;
                            case 1: side1 = new LineSegment(x2, y2, z2, x3, y3, z3); break;
                            case 2: side1 = new LineSegment(x1, y1, z1, x3, y3, z3); break;
                            }
                            double z_tr1 = side1->getZ(side1->getTbyX(x_p1)); //координата стороны в точке пересечения с отрезком
                            if (z_tr1 > z_p1)
                            {
                                if (t_intresect > t_intersections[0])
                                {
                                    if (t_intersections.size() > 1)
                                    {
                                        if (t_intersections[1] > t_intersections[0])
                                        {
                                           currentLS->addIntersection(t_intersections[0], t_intersections[1]);
                                        } else
                                        {
                                            currentLS->addIntersection(t_intersections[1], t_intersections[0]);
                                        }
                                    } else
                                    {
                                        currentLS->addIntersection(0, t_intersections[0]);
                                    }
                                } else
                                {
                                    if (t_intersections.size() > 1)
                                    {
                                        if (t_intersections[1] > t_intersections[0])
                                        {
                                           currentLS->addIntersection(t_intersections[0], t_intersections[1]);
                                        } else
                                        {
                                            currentLS->addIntersection(t_intersections[1], t_intersections[0]);
                                        }
                                    } else
                                    {
                                        currentLS->addIntersection(t_intersections[0], 1);
                                    }
                                }
                            }
                        }

                    } else
                    {
                        if (debug) qDebug() << "есть точка пересечения с проекцией, но плоскость не пересекает";
                        if (t_intersections.size() == 1)
                        {
                            if (debug) qDebug() << "одна точка пересечения";
                            double x_p = currentLS->getX(t_intersections[0]);
                            double z_p = currentLS->getZ(t_intersections[0]);
                            LineSegment *side;
                            switch (n_intersections[0]) {
                            case 0: side = new LineSegment(x1, y1, z1, x2, y2, z2); break;
                            case 1: side = new LineSegment(x2, y2, z2, x3, y3, z3); break;
                            case 2: side = new LineSegment(x1, y1, z1, x3, y3, z3); break;
                            }
                            double z_tr = side->getZ(side->getTbyX(x_p));
                            if (z_tr > z_p)
                            {
                                if (debug) qDebug() << "отрезок частично за треугольником, режем";
                                if (currentTr->isInProjection(currentLS->getCoord(0,0), currentLS->getCoord(0,1)))
                                {
                                    if (debug) qDebug() << "начало отрезка за треугольником";
                                    currentLS->addIntersection(0,t_intersections[0]);
                                } else
                                {
                                    qDebug() << "конец отрезка за треугольником";
                                    currentLS->addIntersection(t_intersections[0],1);
                                }
                            }
                        } else
                        {
                            if (debug) qDebug() << "два пересечения, даже не должны были сюда попасть";
                        }
                    }
                } else
                {
                    //концы отрезка за плоскостью
                    if (!currentTr->isInProjection(currentLS->getCoord(0,0), currentLS->getCoord(0,1)))
                    {
                        if (!currentTr->isInProjection(currentLS->getCoord(1,0), currentLS->getCoord(1,1)))
                        {
                            if (debug) qDebug() << "начало и конец отрезка за плоскостью";
                            continue;
                        }
                    }
                    //проверить пересечение с плоскостью
                    if (debug) qDebug() << "проверка пересечения с плоскостью, когда нет пересечения с проекцией";
                    double A = y1*(z2 - z3) + y2*(z3 - z1) + y3*(z1 - z2);
                    double B = z1*(x2 - x3) + z2*(x3 - x1) + z3*(x1 - x2);
                    double C = x1*(y2 - y3) + x2*(y3 - y1) + x3*(y1 - y2);
                    double D = x1*(y2*z3 - y3*z2) + x2*(y3*z1 - y1*z3) + x3*(y1*z2 - y2*z1);
                    D = -D;
                    double testFunctionBeginning = A*currentLS->getCoord(0,0) + B*currentLS->getCoord(0,1) + C*currentLS->getCoord(0,2) + D;
                    double testFunctionEnd = A*currentLS->getCoord(1,0) + B*currentLS->getCoord(1,1) + C*currentLS->getCoord(1,2) + D;
                    if (testFunctionBeginning * testFunctionEnd < 0)
                    {
                        double t_intresect = -(A*currentLS->getCoord(0,0) + B*currentLS->getCoord(0,1) + C*currentLS->getCoord(0,2) + D)/
                                (A*currentLS->getCoord(2,0) + B*currentLS->getCoord(2,1) + C*currentLS->getCoord(2,2));
                        if (debug) qDebug() << "пересекает " << t_intresect << " " << triangles.size();
                        if (currentTr->isInProjection(currentLS->getX(t_intresect), currentLS->getY(t_intresect)))
                        {
                            double z_int = currentLS->getZ(t_intresect);
                            if (z_int < currentLS->getCoord(0,2))
                            {
                                currentLS->addIntersection(t_intresect, 1);
                            } else
                            {
                                currentLS->addIntersection(0, t_intresect);
                            }
                        }
                    } else
                    {
                       if (debug)  qDebug() << "не пересекает плоскость, проверяем: лежит за плоскостью или перед";
                        double viewerTest = C*10000 + D;
                        if (testFunctionBeginning*viewerTest < 0)
                        {
                            if (debug) qDebug() << "отрезок лежит за плоскостью, вообще не рисуем";
                            currentLS->addIntersection(0,1);
                        }
                    }
                }
            }//if !false
        }//for j=0..triangles size

        Matrix edgeParts;
        if (i == 353) edgeParts = currentLS->calculateIntersections(false);
                else edgeParts = currentLS->calculateIntersections(false);
        edgeParts.addFirstLine(0,0,0,0);
        edgeParts.addLine(1,1,0,0);
        for (int j = 0; j < edgeParts.getHeight()-1; j++)
        {
            double bx = currentLS->getX(edgeParts.getElement(j,1));
            double by = currentLS->getY(edgeParts.getElement(j,1));
            double bz = currentLS->getZ(edgeParts.getElement(j,1));

            double ex = currentLS->getX(edgeParts.getElement(j+1,0));
            double ey = currentLS->getY(edgeParts.getElement(j+1,0));
            double ez = currentLS->getZ(edgeParts.getElement(j+1,0));
            if (bx == ex && by == ey && ez == ez)
            {
                continue;
            }
            int figureSize = f->getSize();
            f->addPoint(bx, by, bz);
            f->addPoint(ex, ey, ez);
            f->setEdge(figureSize+1, figureSize+2, true);
        }
    }
    return f;
}

TriangleSurface::~TriangleSurface()
{
    for (int j = 0; j < triangles.size(); j++)
    {
        delete(triangles[j]);
    }
    delete(figure);
}

