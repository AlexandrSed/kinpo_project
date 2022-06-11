#ifndef HEADER_H
#define HEADER_H

#include <QObject>

struct point
{
    double x,y,z;
};

enum mutualArrangementOfLines{
    parallel,
    perpendicular,
    intersection,
    crossing,
    coincidence
};



class segment
{

public:

    segment();
    segment(segment &s1);
    segment(point point1, point point2);

    point calculateGuideVector();
    void setExtremePoints(point point1, point point2);
    mutualArrangementOfLines determineMutualArrangementOfLines(segment &segment2);
    point findIntersectionPointIntersectingLines(segment &segment2);
    point getExtremePoint1();
    point getExtremePoint2();
    point getGuideVector();
    void operator=(segment other);

private:
    point guideVector;
    point extremePoint1, extremePoint2;

};


struct intersectionPoints
{
    point intersectionPoint1, intersectionPoint2;
    int pointCounter;
};

struct parallelogram
{
    point A, B, C, D;
    segment side1, side2, side3, side4;
};

/*! Найти точки пересечения отрезка с параллелограммом
 *   \param [in] ABCD параллелограмм
 *   \param [in] MN отрезок
 *   \param [out] answer точки пересечения и их счетчик
*/
void findIntersectionPointsOfSegmentWithParallelogram(parallelogram &ABCD, segment MN, intersectionPoints &answer);

/*! Найти точку пересечения двух отрезков, лежащих на пересекающихся прямых
 *   \param [in] segmentA первый отрезок
 *   \param [in] segmentB вторый отрезок
 *   \param [out] answer точки пересечения
*/
void findTheIntersectionPointOfSegmentsLyingOnIntersectingLines(segment segmentA, segment segmentB, intersectionPoints &answer);

/*! определить стороны параллелограмма
 *   \param [in|out] ABCD точки параллелограмма на вход, и стороны - на выход
*/
void determineSidesOfParallelogram(parallelogram &ABCD);



#endif // HEADER_H
