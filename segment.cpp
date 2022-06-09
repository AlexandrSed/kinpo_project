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
    calculateGuideVector();
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
            ((l1 != l2 || l2 != 0) && (m1 != m2 || m2 != 0) &&
             (n1 != n2 || n2 != 0) && m2*n1 == n2*m1 && l2*n1 == n2*l1))
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
    // Рассчитать направляющий вектор (l1, m1, n1) для первого отрезка…
    calculateGuideVector();
    // Рассчитать направляющий вектор (l2, m2, n2) для второго отрезка…
    segment2.calculateGuideVector();

    point answer;
    double l1 = guideVector.x, m1 = guideVector.y, n1 = guideVector.z;
    double l2 = segment2.getGuideVector().x, m2 = segment2.getGuideVector().y, n2 = segment2.getGuideVector().z;
    double x1 = extremePoint1.x, y1 = extremePoint1.y, z1 = extremePoint1.z;
    double x2 = segment2.getExtremePoint1().x, y2 = segment2.getExtremePoint1().y, z2 = segment2.getExtremePoint1().z;


    // Если m1 != 0 и m2*l1/m1 != l2, то есть прямые не лежат в плоскости перпендикулярной плоскости XOY...
    if(m1 != 0 && (m2*l1)/m1 != l2)
    {
        answer.y = (m2*x2 - l2*y2 +(m2*l1*y1)/m1 - x1*m2)/((m2*l1)/m1 - l2); // вычисляем у координату точки пересечения
        answer.x = (answer.y*l1 - l1*y1 + m1*x1)/m1; // вычисляем х координату

        if (l1 != 0) // если l1 != 0…
            answer.z = (n1*answer.x - n1*x1 + l1*z1)/l1; // вычисляем z координату через l1
         else // иначе…
            answer.z = (n2*answer.x - n2*x2 + l2*z2)/l2; // вычисляем z координату через l2
    }
    // Иначе, если n1 !=0 n2*l1/n1 != l2, то есть прямые не лежат в плоскости перпендикулярной плоскости XOZ...
    else if(n1 != 0 && (n2*l1)/n1 != l2)
    {
        answer.z = (n2*x2 - l2*z2 +(n2*l1*z1)/n1 - x1*n2)/((n2*l1)/n1 - l2); // вычисляем z координату точки пересечения
        answer.x = (answer.z*l1 - l1*z1 + n1*x1)/n1; // вычисляем х координату

        if(l1 != 0) // если l1 != 0…
            answer.y = (m1*answer.x - m1*x1 + l1*y1)/l1; // вычисляем y координату через l1
        else // иначе…
            answer.y = (m2*answer.x - m2*x2 + l2*y2)/l2; // вычисляем y координату через l2
    }
    // Иначе, если n1 != 0 и n2*m1/n1 != m2, то есть прямые не лежат в плоскости перпендикулярной плоскости YOZ...
    else if(n1 != 0 && (n2*m1)/n1 != m2)
    {
        answer.z = (n2*y2 - m2*z2 +(n2*m1*z1)/n1 - y1*n2)/((n2*m1)/n1 - m2); // вычисляем z координату точки пересечения
        answer.y = (answer.z*m1 - z1*m1 + y1*n1)/n1; // вычисляем y координату

        if(m1 != 0) // если m1 != 0…
            answer.z = (answer.y*l1 - y1*l1 + m1*x1)/m1; // вычисляем x координату через m1
        else // иначе…
            answer.z = (answer.y*l2 - y2*l2 + m2*x2)/m2; // вычисляем x координату через m2
    }
    // Иначе, если l1 != 0 и l2*m1/l1 != m2, то есть прямые не лежат в плоскости перпендикулярной плоскости YOZ...
    else if (l1 != 0 && (l2*m1)/l1 != m2)
    {
        answer.x = (m2*x2 - l2*y2 - l2*m1*x1/l1 + y1*l2)/(m2 - l2*m1/l1); // вычисляем x координату точки пересечения
        answer.y = (m1*answer.x - m1*x1 + y1*l1)/l1; // вычисляем y координату

        if(m1 != 0) // если m1 != 0…
            answer.z = (answer.y*n1 - y1*n1 + z1*m1)/m1; // вычисляем z координату через m1
        else // иначе…
            answer.z = (answer.y*n2 - y2*n2 + z2*m2)/m2; // вычисляем z координату через m2
    }


    return answer;// возвращаем точку пересечения
}
