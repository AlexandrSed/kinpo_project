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
    // Выдать ошибку, если координаты разных точек параллелограмма повторяются
    // Выдать ошибку, если Отрезок вырождается в точку
    // Выдать ошибку, если количества введенных чисел недостаточно для расчета
    // Выдать ошибку, если количество введенных чисел больше, чем надо
    // Выдать ошибку, если один или несколько аргументов не являются числом

    determineSidesOfParallelogram(ABCD); // Определить стороны параллелограмма…

    segment side;

    for(int i = 1; i<=4 && answer.pointCounter<2 ; i++)// Для каждой стороны параллелограмма…
    {
        if(i==1)
            side = ABCD.side1;
        else if(i==2)
            side = ABCD.side2;
        else if(i==3)
            side = ABCD.side3;
        else
            side = ABCD.side4;

        /* если прямые, на которых лежат отрезок и сторона пересекаются, и нет найденной точки пересечения,
        которая равнялась бы одному из концов стороны…*/
        if((side.determineMutualArrangementOfLines(MN) == intersection ||
                side.determineMutualArrangementOfLines(MN) == perpendicular) &&
                answer.intersectionPoint1 != side.getExtremePoint1() &&
                answer.intersectionPoint1 != side.getExtremePoint2())
        {
            // Найти точку пересечения отрезка со стороной…
            findTheIntersectionPointOfSegmentsLyingOnIntersectingLines(side, MN, answer);
        }
        // иначе, если прямые совпадают…
        else if(side.determineMutualArrangementOfLines(MN) == coincidence)
        {
            // если отрезок частично совпадает со стороной…
            if((side.getExtremePoint1().x > MN.getExtremePoint1().x && side.getExtremePoint1().x < MN.getExtremePoint2().x) ||
                    (side.getExtremePoint1().y > MN.getExtremePoint1().y && side.getExtremePoint1().y < MN.getExtremePoint2().y) ||
                    (side.getExtremePoint1().z > MN.getExtremePoint1().z && side.getExtremePoint1().z < MN.getExtremePoint2().z) ||
                    (side.getExtremePoint1().x < MN.getExtremePoint1().x && side.getExtremePoint1().x > MN.getExtremePoint2().x) ||
                    (side.getExtremePoint1().y < MN.getExtremePoint1().y && side.getExtremePoint1().y > MN.getExtremePoint2().y) ||
                    (side.getExtremePoint1().z < MN.getExtremePoint1().z && side.getExtremePoint1().z > MN.getExtremePoint2().z) ||
                    (side.getExtremePoint2().x > MN.getExtremePoint1().x && side.getExtremePoint2().x < MN.getExtremePoint2().x) ||
                    (side.getExtremePoint2().y > MN.getExtremePoint1().y && side.getExtremePoint2().y < MN.getExtremePoint2().y) ||
                    (side.getExtremePoint2().z > MN.getExtremePoint1().z && side.getExtremePoint2().z < MN.getExtremePoint2().z) ||
                    (side.getExtremePoint2().x < MN.getExtremePoint1().x && side.getExtremePoint2().x > MN.getExtremePoint2().x) ||
                    (side.getExtremePoint2().y < MN.getExtremePoint1().y && side.getExtremePoint2().y > MN.getExtremePoint2().y) ||
                    (side.getExtremePoint1().z < MN.getExtremePoint1().z && side.getExtremePoint2().z > MN.getExtremePoint1().z) ||
                    (side.getExtremePoint1().x > MN.getExtremePoint1().x && side.getExtremePoint2().x < MN.getExtremePoint1().x) ||
                    (side.getExtremePoint1().y > MN.getExtremePoint1().y && side.getExtremePoint2().y < MN.getExtremePoint1().y) ||
                    (side.getExtremePoint1().z > MN.getExtremePoint1().z && side.getExtremePoint2().z < MN.getExtremePoint1().z) ||
                    (side.getExtremePoint1().x < MN.getExtremePoint1().x && side.getExtremePoint2().x > MN.getExtremePoint1().x) ||
                    (side.getExtremePoint1().y < MN.getExtremePoint1().y && side.getExtremePoint2().y > MN.getExtremePoint1().y) ||
                    (side.getExtremePoint1().z < MN.getExtremePoint1().z && side.getExtremePoint2().z > MN.getExtremePoint1().z))
            {
                // выдать ошибку: отрезок и сторона параллелограмма совпадают
            }
        }
    }

}

bool operator!=(point p1, point p2)
{
    return p1.x != p2.x || p1.y != p2.y || p1.z != p2.z;
}
