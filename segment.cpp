#include "header.h"

segment::segment()
{
    extremePoint1={0,0,0};
    extremePoint2={0,0,0};
    guideVector={0,0,0};
}

segment::segment(segment &s1)
{
    extremePoint1=s1.extremePoint1;
    extremePoint2=s1.extremePoint2;
    guideVector={0,0,0};
}

segment::segment(point point1, point point2)
{
    extremePoint1=point1;
    extremePoint2=point2;
    guideVector={0,0,0};
}

point segment::getExtremePoint1()
{
    return extremePoint1;
}

point segment::getExtremePoint2()
{
    return extremePoint2;
}

point segment::getGuideVector()
{
    return guideVector;
}

point segment::calculateGuideVector()
{
    guideVector.x = extremePoint2.x - extremePoint1.x;// Рассчитать x координату вектора
    guideVector.y = extremePoint2.y - extremePoint1.y;// Рассчитать y координату вектора
    guideVector.z = extremePoint2.z - extremePoint1.z;// Рассчитать z координату вектора
    return guideVector;
}

void segment::setExtremePoints(point point1, point point2)
{
    extremePoint1 = point1;
    extremePoint2 = point2;
}

mutualArrangementOfLines segment::determineMutualArrangementOfLines(segment &segment2)
{
    // Рассчитать направляющий вектор (l1, m1, n1) для первого отрезка…
    this->calculateGuideVector();
    // Рассчитать направляющий вектор (l2, m2, n2) для второго отрезка…
    segment2.calculateGuideVector();

    double l1 = guideVector.x, m1 = guideVector.y, n1 = guideVector.z;
    double l2 = segment2.getGuideVector().x, m2 = segment2.getGuideVector().y, n2 = segment2.getGuideVector().z;
    segment intersectSegment(extremePoint1, segment2.getExtremePoint1());
    intersectSegment.calculateGuideVector();
    if(intersectSegment.getGuideVector().x == 0 && intersectSegment.getGuideVector().y == 0 && intersectSegment.getGuideVector().y == 0)
    {
        intersectSegment.extremePoint1 = extremePoint2;
        intersectSegment.calculateGuideVector();
    }
    double l3 = intersectSegment.getGuideVector().x, m3 = intersectSegment.getGuideVector().y, n3 = intersectSegment.getGuideVector().z;

    /* Если l1 = l2 = l3 = m1 = m2 = m3 = 0  или n1 = n2 = n3 = m1 = m2 = m3 = 0 или l1 = l2 = l3 = n1 = n2 = n3 = 0
     * или одна из координат у всех трех векторов равна нулю, а другие пропорциональны,
     * или отношения соответствующих координат направляющих векторов равны,
     * и отношения соответствующих координат одного из направляющих векторов и вектора (l3, m3, n3),
     * начальная точка которого лежит на одной прямой, а конечная на другой … */
    if((l1 == l2 && l2 == l3 && l3 == m1 && m1 == m2 && m2 == m3 && m3 == 0) ||
            (n1 == n2 && n2 == n3 && n3 == m1 && m1 == m2 && m2 == m3 && m3 == 0)||
            (l1 == l2 && l2 == l3 && l3 == n1 && n1 == n2 && n2 == n3 && n3 == 0)||
            ((l1 == l2 && l2 == l3 && l3 == 0) && m2*n1 == n2*m1 && m3*n1 == n3*m1) ||
            ((m1 == m2 && m2 == m3 && m3 == 0) && l2*n1 == n2*l1 && l3*n1 == n3*l1) ||
            ((n1 == n2 && n2 == n3 && n3 == 0) && l2*m1 == m2*l1 && l3*m1 == m3*l1) ||
            ((l1 != l2 || l2 != l3 || l3 != 0) && (m1 != m2 || m2 != m3 || m3 != 0) &&
             (n1 != n2 || n2 != n3 || n3 != 0) &&
                (m2*n1 == n2*m1 && l2*n1 == n2*l1) && (m3*n1 == n3*m1 && l3*n1 == n3*l1)))
    {
        return coincidence; // Прямые совпадают
    }
    /* Иначе, если l1 = l2 = m1 = m2 = 0 или n1 = n2 = m1 = m2 = 0 или l1 = l2 = n1 = n2 = 0
     *  или одна из координат у обоих векторов равна нулю, а другие пропорциональны,
     *   отношения соответствующих координат направляющих векторов равны…*/
    else if((l1 == l2 && l2== m1 && m1 == m2 && m2 == 0) ||
            (n1 == n2 && n2 == m1 && m1 == m2 && m2 == 0)||
            (l1 == l2 && l2 == n1 && n1 == n2 && n2 == 0)||
            ((l1 == l2 && l2 == 0) && m2*n1 == n2*m1) ||
            ((m1 == m2 && m2 == 0) && l2*n1 == n2*l1) ||
            ((n1 == n2 && n2 == 0) && l2*m1 == m2*l1) ||
            (m2*n1 == n2*m1 && l2*n1 == n2*l1))
    {
         return parallel; // Прямые параллельны
    }
    // Иначе, если сумма произведений соответствующих координат направляющих векторов равна нулю…
    else if(l1*l2 + n1*n2 + m1*m2 == 0)
    {
        return perpendicular; // Прямые перпендикулярны
    }
    /* Иначе, если смешанное произведение направляющих векторов и вектора,
     * начальная точка которого лежит на одной прямой, а конечная на другой, отличны от нуля…*/
    else if((l1*m2*n3 + l2*m3*n1 + m1*n2*l3 - l3*m2*n1 - l2*m1*n3 - l1*m3*n2) != 0)
    {
        return crossing; // Прямые скрещиваются
    }
    // Иначе…
    else
    {
        return intersection; // Прямые пересекаются
    }

}

point segment::findIntersectionPointIntersectingLines(segment &segment2)
{

}
