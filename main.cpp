#include <QCoreApplication>
#include "header.h"
#include <fstream>
#include <QtTest/QTest>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "tests.h"

using namespace std;

int main(int argc, char *argv[])
{

    freopen("testing.log", "w", stdout);
    QCoreApplication a(argc, argv);
    QTest::qExec(new tests, argc, argv);

    return 0;

}

void determineSidesOfParallelogram(parallelogram &ABCD)
{
    segment AB(ABCD.A, ABCD.B), CD(ABCD.C, ABCD.D);
    segment AC(ABCD.A, ABCD.C), DB(ABCD.D, ABCD.B);
    segment AD(ABCD.A, ABCD.D), BC(ABCD.B, ABCD.C);

    // если прямая АВ параллельна прямой CD…
    if(AB.determineMutualArrangementOfLines(CD) == parallel)
    {
        // если AC параллельна BD…
        if(AC.determineMutualArrangementOfLines(DB) == parallel)
        {
            // вернуть: стороны параллелограмма AB, CD, AC, BD
            ABCD.side1 = AB;
            ABCD.side2 = CD;
            ABCD.side3 = AC;
            ABCD.side4 = DB;
        }
        else if(AD.determineMutualArrangementOfLines(BC) == parallel) // иначе, если AD параллельна BC…
        {
            // вернуть: стороны параллелограмма AB, CD, AD, BC
            ABCD.side1 = AB;
            ABCD.side3 = CD;
            ABCD.side4 = AD;
            ABCD.side2 = BC;
        }
        else // иначе…
        {
            // выдать ошибку: указанный четырёхугольник не является параллелограммом
        }
    }
    else if(AC.determineMutualArrangementOfLines(DB) == parallel) // иначе, если AC параллельна BD…
    {
        if(AD.determineMutualArrangementOfLines(BC) == parallel) // если AD параллельна BC…
        {
            // вернуть: стороны параллелограмма AC, BD, AD, BC
            ABCD.side4 = AC;
            ABCD.side2 = DB;
            ABCD.side1 = AD;
            ABCD.side3 = BC;
        }
        else // иначе…
        {
            // выдать ошибку: указанный четырёхугольник не является параллелограммом
        }
    }
    else // иначе…
    {
        // выдать ошибку: указанный четырёхугольник не является параллелограммом
    }

}

void findTheIntersectionPointOfSegmentsLyingOnIntersectingLines(segment segmentA, segment segmentB, intersectionPoints &answer)
{
    // Найти точку пересечения прямых на которых лежат отрезки…
    point intersectionPoint = segmentA.findIntersectionPointIntersectingLines(segmentB);

    // если точка пересечения лежит на обоих отрезках…
    if(((intersectionPoint.x >= segmentA.getExtremePoint1().x && intersectionPoint.x <= segmentA.getExtremePoint2().x) ||
        (intersectionPoint.x <= segmentA.getExtremePoint1().x && intersectionPoint.x >= segmentA.getExtremePoint2().x)) &&
            ((intersectionPoint.y >= segmentA.getExtremePoint1().y && intersectionPoint.y <= segmentA.getExtremePoint2().y)||
             (intersectionPoint.y <= segmentA.getExtremePoint1().y && intersectionPoint.y >= segmentA.getExtremePoint2().y)) &&
            ((intersectionPoint.z >= segmentA.getExtremePoint1().z && intersectionPoint.z <= segmentA.getExtremePoint2().z)||
             (intersectionPoint.z <= segmentA.getExtremePoint1().z && intersectionPoint.z >= segmentA.getExtremePoint2().z)) &&
            ((intersectionPoint.x >= segmentB.getExtremePoint1().x && intersectionPoint.x <= segmentB.getExtremePoint2().x) ||
             (intersectionPoint.x <= segmentB.getExtremePoint1().x && intersectionPoint.x >= segmentB.getExtremePoint2().x)) &&
            ((intersectionPoint.y >= segmentB.getExtremePoint1().y && intersectionPoint.y <= segmentB.getExtremePoint2().y) ||
             (intersectionPoint.y <= segmentB.getExtremePoint1().y && intersectionPoint.y >= segmentB.getExtremePoint2().y)) &&
            ((intersectionPoint.z >= segmentB.getExtremePoint1().z && intersectionPoint.z <= segmentB.getExtremePoint2().z)||
             (intersectionPoint.z <= segmentB.getExtremePoint1().z && intersectionPoint.z >= segmentB.getExtremePoint2().z)))
    {
        // …вернуть ее координаты и счетчик точек пересечения повысить на один
        if(answer.pointCounter == 0)
            answer.intersectionPoint1 = intersectionPoint;
        else
            answer.intersectionPoint2 = intersectionPoint;

        answer.pointCounter++;
    }

}

void findIntersectionPointsOfSegmentWithParallelogram(parallelogram &ABCD, segment MN, intersectionPoints &answer)
{

}
