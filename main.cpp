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

}

void findIntersectionPointsOfSegmentWithParallelogram(parallelogram &ABCD, segment MN, intersectionPoints &answer)
{

}
