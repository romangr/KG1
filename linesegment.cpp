#include "linesegment.h"
#include <qdebug.h>

int LineSegment::isInSegments(QVector<double> &begin, QVector<double> &end, double x)
{
    for (int i = 0; i < begin.size(); i++)
    {
        if (x >= begin.at(i) && x <= end.at(i))
        {
            return i;
        }
    }
    return -1;
}

LineSegment::LineSegment(Matrix &m)
{
    this->coords = m;
    this->coords.addLine(m.getElement(1,0)-m.getElement(0,0), m.getElement(1,1)-m.getElement(0,1), m.getElement(1,2)-m.getElement(0,2), 0);
    this->intersections = new Matrix();
    //this->intersections->addLine(0, 1, 0, 0);
}

LineSegment::LineSegment(double x1, double y1, double z1, double x2, double y2, double z2)
{
    this->coords.addLine(x1, y1, z1, 0);
    this->coords.addLine(x2, y2, z2, 0);
    this->coords.addLine(x2-x1, y2-y1, z2-z1, 0);
    this->intersections = new Matrix();
    //this->intersections->addLine(0, 1, 0, 0);
}

double LineSegment::getX(double t)
{
    return this->coords.getElement(0,0) + this->coords.getElement(2,0)*t;
}

double LineSegment::getY(double t)
{
    return this->coords.getElement(0,1) + this->coords.getElement(2,1)*t;
}

double LineSegment::getZ(double t)
{
    return this->coords.getElement(0,2) + this->coords.getElement(2,2)*t;
}

double *LineSegment::getPoint(double t)
{
    double *point = new double[4];
    point[0] = getX(t);
    point[1] = getY(t);
    point[2] = getZ(t);
    point[3] = 0;
    return point;

}

double LineSegment::getCoord(int x, int y)
{
    return this->coords.getElement(x, y);
}

double LineSegment::getTbyX(double x)
{
    return (x - coords.getElement(0,0)) / coords.getElement(2,0);
}

void LineSegment::setFigurePoints(int x, int y)
{
    this->fPoints[0] = x;
    this->fPoints[1] = y;
}

int LineSegment::getFigurePoint(int i)
{
    if (i < 2) return fPoints[i];
    return -1;
}

void LineSegment::addIntersection(double t1, double t2)
{
    this->intersections->addLine(t1, t2, 0, 0);
}

Matrix LineSegment::calculateIntersections()
{
    QVector<double> begin;
    QVector<double> end;
    if (this->intersections->getHeight() > 0)
    {
        begin.push_back(this->intersections->getElement(0,0));
        end.push_back(this->intersections->getElement(0,1));
    } else
    {
        Matrix res;
        return res;
    }

    /*  begin.push_back(this->intersections->getElement(i,0));
        end.push_back(this->intersections->getElement(i,1));
     */
    for (int i = 0; i < this->intersections->getHeight(); i++)
    {
        QVector<int> toDelete;
        double b = this->intersections->getElement(i,0);
        double e = this->intersections->getElement(i,1);
        if (!(b != e && e >= 0 && b >= 0)) continue;
        int beginInN = isInSegments(begin, end, b);
        int endInN = isInSegments(begin, end, e);
        //проверка, не накроет ли этот отрезок другой целиком
        for (int j = 0; j < begin.size(); j++)
        {
            if (b < begin.at(j) && e > end.at(j))
            {
                if (toDelete.size() > 0)
                {
                    bool added = false;
                    for (int k = 0; k < toDelete.size(); k++)
                    {
                        if (j < toDelete.at(k))
                        {
                            toDelete.push_front(j);
                            added = true;
                        }
                    }
                    if (!added) { toDelete.push_back(j); }
                } else
                {
                    toDelete.push_back(j);
                }
            }
        }
        for (int j = toDelete.size()-1; j > -1 ; j--)
        {
            begin.removeAt(toDelete.at(j));
            end.removeAt(toDelete.at(j));
        }
        if (beginInN > -1)
        {
            if (endInN > -1)
            {
                if (beginInN == endInN)
                {
                    //отрезок полностью внутри другого, значит не нужен
                    continue;
                } else
                {
                    b = begin.at(beginInN);
                    e = end.at(endInN);
                    if (beginInN < endInN)
                    {
                        begin.removeAt(endInN);
                        end.removeAt(endInN);
                        begin.removeAt(beginInN);
                        end.removeAt(beginInN);
                    } else
                    {
                        begin.removeAt(beginInN);
                        end.removeAt(beginInN);
                        begin.removeAt(endInN);
                        end.removeAt(endInN);
                    }
                    begin.push_back(b);
                    end.push_back(e);
                }
            } else
            {
                b = begin.at(beginInN);
                begin.removeAt(beginInN);
                end.removeAt(beginInN);
                begin.push_back(b);
                end.push_back(e);
            }
        } else
        {
            if (endInN > -1)
            {
                e = begin.at(endInN);
                begin.removeAt(endInN);
                end.removeAt(endInN);
                begin.push_back(b);
                end.push_back(e);
            } else
            {
                begin.push_back(b);
                end.push_back(e);
            }
        }
    }
    Matrix result;
    result.addLine(begin.at(0), end.at(0), 0, 0);
    for (int i = 1; i < begin.size(); i++)
    {
        for (int j=0; j<result.getHeight(); j++)
        {
            if (result.getElement(j,0)>result.getElement(i,0))
            {
                result.addFirstLine(begin.at(i), end.at(i), 0, 0);
                break;
            }else
            {
                if (j==result.getHeight()-1)
                {result.addLine(begin.at(i), end.at(i), 0, 0);}
            }
        }
    }
    return result;
}

LineSegment::~LineSegment()
{
    delete(intersections);
}

