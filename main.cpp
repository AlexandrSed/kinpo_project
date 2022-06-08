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

}

void findTheIntersectionPointOfSegmentsLyingOnIntersectingLines(segment segmentA, segment segmentB, intersectionPoints &answer)
{

}

void findIntersectionPointsOfSegmentWithParallelogram(parallelogram &ABCD, segment MN, intersectionPoints &answer)
{

}
