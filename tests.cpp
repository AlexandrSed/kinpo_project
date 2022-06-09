#include "tests.h"
#include <QtTest/QTest>
#include "header.h"

tests::tests(QObject *parent) : QObject(parent)
{

}

void comparePoints(point actualPoint, point expectedPoint,char testName[150])
{
    QVERIFY2(actualPoint.x == expectedPoint.x, testName);

    QVERIFY2(actualPoint.y == expectedPoint.y, testName);

    QVERIFY2(actualPoint.z == expectedPoint.z, testName);
}

void compareParallelogramms(parallelogram actual, parallelogram expected, char testName[150])
{
    comparePoints(actual.A, expected.A, testName);
    comparePoints(actual.B, expected.B, testName);
    comparePoints(actual.C, expected.C, testName);
    comparePoints(actual.D, expected.D, testName);
    comparePoints(actual.side1.getExtremePoint1(), expected.side1.getExtremePoint1(), testName);
    comparePoints(actual.side1.getExtremePoint2(), expected.side1.getExtremePoint2(), testName);
    comparePoints(actual.side2.getExtremePoint1(), expected.side2.getExtremePoint1(), testName);
    comparePoints(actual.side2.getExtremePoint2(), expected.side2.getExtremePoint2(), testName);
    comparePoints(actual.side3.getExtremePoint1(), expected.side3.getExtremePoint1(), testName);
    comparePoints(actual.side3.getExtremePoint2(), expected.side3.getExtremePoint2(), testName);
    comparePoints(actual.side4.getExtremePoint1(), expected.side4.getExtremePoint1(), testName);
    comparePoints(actual.side4.getExtremePoint2(), expected.side4.getExtremePoint2(), testName);
}

void tests::testDetermineMutualArrangementOfLines()
{
    segment AB({1,7,3},{3,8,7});
    segment CD({6,-1,-2},{9,-3,-1});

    // пересекаются
    QVERIFY2(AB.determineMutualArrangementOfLines(CD)==intersection,"intersection");

    // парарллельны
    AB.setExtremePoints({0,-8,-3},{1,-12,-6});
    CD.setExtremePoints({0,0,0},{-1,4,3});
    QVERIFY2(AB.determineMutualArrangementOfLines(CD)==parallel,"parallel");

    // перпендикулярны
    AB.setExtremePoints({0,1,3},{4,3,5});
    CD.setExtremePoints({1,2,5},{3,0,3});
    QVERIFY2(AB.determineMutualArrangementOfLines(CD)==perpendicular,"perpendikular");

    // скрещиваются
    AB.setExtremePoints({3,-1,4},{4,1,4});
    CD.setExtremePoints({0,2,6},{1,3,8});
    QVERIFY2(AB.determineMutualArrangementOfLines(CD)==crossing,"crossing");

    // совпадают
    AB.setExtremePoints({0,2,6},{1,3,8});
    CD.setExtremePoints({3,5,12},{-1,1,4});
    QVERIFY2(AB.determineMutualArrangementOfLines(CD)==coincidence,"coincidence");

    // пересекаются и одна из них параллельна оси координат
    AB.setExtremePoints({6,2,5},{2,2,5});
    CD.setExtremePoints({7,0,2},{5,4,8});
    QVERIFY2(AB.determineMutualArrangementOfLines(CD)==intersection,"intersection, and one of the lines is parallel to the coordinate axis");

    // паралллельны между собой и параллельны оси координат
    AB.setExtremePoints({2,6,5},{2,2,5});
    CD.setExtremePoints({-5,4,0},{-5,5,0});
    QVERIFY2(AB.determineMutualArrangementOfLines(CD)==parallel,"lines are parallel to the coordinate axis");

    //прямые скрещиваются, и одна из них параллельна координатной оси
    AB.setExtremePoints({2,5,6},{2,5,2});
    CD.setExtremePoints({0,2,7},{2,4,5});
    QVERIFY2(AB.determineMutualArrangementOfLines(CD)==crossing,"lines intersect, and one of them is parallel to the coordinate axis");

    // совпадают и параллельны оси координат
    AB.setExtremePoints({6,2,5},{2,2,5});
    CD.setExtremePoints({-7,2,5},{-3,2,5});
    QVERIFY2(AB.determineMutualArrangementOfLines(CD)==coincidence,"coincidence, and line is parallel to the coordinate axis");

    // пересекаются и лежат в одной плоскости, параллельной координатной
    AB.setExtremePoints({1,1,3},{3,2,3});
    CD.setExtremePoints({1,3,3},{2,-1,3});
    QVERIFY2(AB.determineMutualArrangementOfLines(CD)==intersection,"intersection and lie in the same plane parallel to the coordinate");

    // пересекаются и одна из них лежит в одной плоскости, параллельной координатной
    AB.setExtremePoints({3,1,1},{3,3,2});
    CD.setExtremePoints({2,2,0},{4,0,2});
    QVERIFY2(AB.determineMutualArrangementOfLines(CD)==intersection,"intersect and one of them lies in the same plane parallel to the coordinate");

    // совпадают и лежат в одной плоскости, параллельной координатной
    AB.setExtremePoints({2,2,4},{6,2,5});
    CD.setExtremePoints({10,2,6},{14,2,7});
    QVERIFY2(AB.determineMutualArrangementOfLines(CD)==coincidence,"coincidence and lie in the same plane parallel to the coordinate");

    // парарллельны и лежат в одной плоскости
    AB.setExtremePoints({2,2,4},{6,2,5});
    CD.setExtremePoints({5,2,6},{9,2,7});
    QVERIFY2(AB.determineMutualArrangementOfLines(CD)==parallel,"parallel and lie in the same plane parallel to the coordinate");

    /*прямые пересекаются и лежат обе в одной плоскости
    параллельной координатной, и одна прямая параллельна координатной оси*/
    AB.setExtremePoints({3,1,1},{3,3,2});
    CD.setExtremePoints({3,2,0},{3,2,2});
    QVERIFY2(AB.determineMutualArrangementOfLines(CD)==intersection,
             "the lines intersect and both lie in the same plane parallel to the coordinate, and one line is parallel to the coordinate axis");
}

void tests::testFindIntersectionPointIntersectingLines()
{
    segment AB({1,7,3},{3,8,7});
    segment CD({6,-1,-2},{9,-3,-1});
    point expectedAnswer={-3,5,-5};

    // прямые пересекаются
    comparePoints(AB.findIntersectionPointIntersectingLines(CD), expectedAnswer, "Lines intersection");

    // прямые перпендикулярны
    AB.setExtremePoints({0,1,3},{4,3,5});
    CD.setExtremePoints({1,4,5},{3,0,3});
    expectedAnswer = {2,2,4};
    comparePoints(AB.findIntersectionPointIntersectingLines(CD), expectedAnswer, "Lines perpendicular");

    // прямые пересекаются, и одна из них параллельна координатной оси OX
    AB.setExtremePoints({6,2,5},{2,2,5});
    CD.setExtremePoints({7,0,2},{5,4,8});
    expectedAnswer = {6,2,5};
    comparePoints(AB.findIntersectionPointIntersectingLines(CD), expectedAnswer,
                  "intersection, and one of the lines is parallel to the coordinate axis OX");

    // прямые пересекаются, и одна из них параллельна координатной оси OY
    AB.setExtremePoints({2,6,5},{2,2,5});
    CD.setExtremePoints({0,7,2},{4,5,8});
    expectedAnswer = {2,6,5};
    comparePoints(AB.findIntersectionPointIntersectingLines(CD), expectedAnswer,
                  "intersection, and one of the lines is parallel to the coordinate axis OY");

    // прямые пересекаются, и одна из них параллельна координатной оси OZ
    AB.setExtremePoints({2,5,6},{2,5,2});
    CD.setExtremePoints({0,2,7},{4,8,5});
    expectedAnswer = {2,5,6};
    comparePoints(AB.findIntersectionPointIntersectingLines(CD), expectedAnswer,
                "intersection, and one of the lines is parallel to the coordinate axis OZ");

    // прямые пересекаются и лежат в одной плоскости, параллельной координатной плоскости XOY
    AB.setExtremePoints({1,1,3},{3,2,3});
    CD.setExtremePoints({1,3,3},{2,-1,3});
    expectedAnswer = {1.44,1.22,3};
    comparePoints(AB.findIntersectionPointIntersectingLines(CD), expectedAnswer,
                  "intersection and lie in the same plane parallel to the coordinate plane XOY");

    // прямые пересекаются и лежат в одной плоскости, параллельной координатной плоскости XOZ
    AB.setExtremePoints({1,3,1},{3,3,2});
    CD.setExtremePoints({1,3,3},{2,3,-1});
    expectedAnswer = {1.44,3,1.22};
    comparePoints(AB.findIntersectionPointIntersectingLines(CD), expectedAnswer,
          "intersection and lie in the same plane parallel to the coordinate plane XOZ");

    // прямые пересекаются и лежат в одной плоскости, параллельной координатной плоскости YOZ
    AB.setExtremePoints({3,1,1},{3,3,2});
    CD.setExtremePoints({3,1,3},{3,2,-1});
    expectedAnswer = {3,1.44,1.22};
    comparePoints(AB.findIntersectionPointIntersectingLines(CD), expectedAnswer,
          "intersection and lie in the same plane parallel to the coordinate plane YOZ");

    /* прямые пересекаются и лежат обе в одной плоскости параллельной
 координатной, и одна прямая параллельна координатной оси*/
    AB.setExtremePoints({3,1,1},{3,3,2});
    CD.setExtremePoints({3,2,0},{3,2,2});
    expectedAnswer = {3,2,1.5};
    comparePoints(AB.findIntersectionPointIntersectingLines(CD), expectedAnswer,
          "the lines intersect and both lie in the same plane parallel to the coordinate, and one line is parallel to the coordinate axis");
}

void tests::testDetermineSidesOfParallelogram()
{
    segment AB, BC, CD, AD;
    parallelogram actual = {{2,4,2},{3,5,6},{6,8,8},{5,7,4}, AB, BC, CD, AD};
    segment ABexp({2,4,2},{3,5,6});
    segment BCexp({3,5,6},{6,8,8});
    segment CDexp({6,8,8},{5,7,4});
    segment ADexp({5,7,4},{2,4,2});
    parallelogram expected = {{2,4,2},{3,5,6},{6,8,8},{5,7,4}, ABexp, BCexp, CDexp, ADexp};

    // переданные точки перечислены по порядку
    determineSidesOfParallelogram(actual);
    compareParallelogramms(actual, expected, "transmitted points are listed in order");

    // переданные точки перечислены не по порядку
    actual.B = {6,8,8};
    actual.C = {5,7,4};
    actual.D = {3,5,6};
    expected.B = {6,8,8};
    expected.C = {5,7,4};
    expected.D = {3,5,6};
    determineSidesOfParallelogram(actual);
    compareParallelogramms(actual, expected, "transmitted points are listed out of order");

}

void tests::testFindTheIntersectionPointOfSegmentsLyingOnIntersectingLines()
{
    segment AB({7,3,5},{3,1,-3});
    segment CD({2,4,0},{8,0,2});
    intersectionPoints actual ={{0,0,0},{0,0,0}, 0};
    intersectionPoints expected{{5,2,1},{0,0,0}, 1};

    //  точка пересечения прямых, на которых лежат отрезки, лежит на серединах обоих отрезков
    findTheIntersectionPointOfSegmentsLyingOnIntersectingLines(AB, CD, actual);
    QVERIFY2(actual.pointCounter == expected.pointCounter,
         "the point of intersection of the lines on which the segments lie, lie in the middle of both segments");
    comparePoints(actual.intersectionPoint1, expected.intersectionPoint1,
         "the point of intersection of the lines on which the segments lie, lie in the middle of both segments");

    // прямые, на которых лежат отрезки, не пересекаются
    AB.setExtremePoints({3,-1,4},{4,1,4});
    CD.setExtremePoints({0,2,6},{1,3,8});
    actual.pointCounter = 0;
    expected.pointCounter = 0;
    findTheIntersectionPointOfSegmentsLyingOnIntersectingLines(AB, CD, actual);
    QVERIFY2(actual.pointCounter == expected.pointCounter, "the lines on which the segments lie do not intersect");

    // точка пересечения прямых не лежит на отрезках
    AB.setExtremePoints({1,7,3},{3,8,7});
    CD.setExtremePoints({6,-1,-2},{9,-3,-1});
    actual.pointCounter = 0;
    expected.pointCounter = 0;
    findTheIntersectionPointOfSegmentsLyingOnIntersectingLines(AB, CD, actual);
    QVERIFY2(actual.pointCounter == expected.pointCounter, "the intersection point of the lines does not lie on the segments");

    // точка пересечения прямых лежит одном из отрезков
    AB.setExtremePoints({7,3,5},{3,1,-3});
    CD.setExtremePoints({2,4,0},{-1,6,-1});
    actual.pointCounter = 0;
    expected.pointCounter = 0;
    findTheIntersectionPointOfSegmentsLyingOnIntersectingLines(AB, CD, actual);
    QVERIFY2(actual.pointCounter == expected.pointCounter, "the intersection point of the straight lines lies in one of the segments");

    // точка пересечения лежит на середине одного и на конце другого отрезка
    AB.setExtremePoints({7,3,5},{3,1,-3});
    CD.setExtremePoints({2,4,0},{5,2,1});
    actual.pointCounter = 0;
    expected.pointCounter = 1;
    expected.intersectionPoint1 = {5,2,1};
    findTheIntersectionPointOfSegmentsLyingOnIntersectingLines(AB, CD, actual);
    QVERIFY2(actual.pointCounter == expected.pointCounter,
             "the intersection point lies in the middle of one and at the end of the other segment");
    comparePoints(actual.intersectionPoint1, expected.intersectionPoint1,
             "the intersection point lies in the middle of one and at the end of the other segment");

    // точка пересечения является концами обоих отрезков
    AB.setExtremePoints({7,3,5},{5,2,1});
    CD.setExtremePoints({2,4,0},{5,2,1});
    actual.pointCounter = 0;
    expected.pointCounter = 1;
    expected.intersectionPoint1 = {5,2,1};
    findTheIntersectionPointOfSegmentsLyingOnIntersectingLines(AB, CD, actual);
    QVERIFY2(actual.pointCounter == expected.pointCounter,
             "the intersection point is the ends of both segments");
    comparePoints(actual.intersectionPoint1, expected.intersectionPoint1,
             "the intersection point is the ends of both segments");
}

void tests::testFindIntersectionPointsOfSegmentWithParallelogram()
{
    segment AB,BC,CD,AD,MN({6,9,13},{3,4,1});
    parallelogram ABCD = {{2,4,2},{3,5,6},{6,8,8},{5,7,4},AB,BC,CD,AD};
    intersectionPoints actual = {{0,0,0},{0,0,0}, 0};
    intersectionPoints expected = {{4.5,6.5,7},{0,0,0}, 1};


    // отрезок пересекает одну сторону параллелограмма
    findIntersectionPointsOfSegmentWithParallelogram(ABCD, MN, actual);
    QVERIFY2(actual.pointCounter == expected.pointCounter,
             "the segment intersects one side of the parallelogram");
    comparePoints(actual.intersectionPoint1, expected.intersectionPoint1,
             "the segment intersects one side of the parallelogram");

    // отрезок не пересекает параллелограмм
    MN.setExtremePoints({-6,6,3},{5,4,1});
    actual.pointCounter = 0;
    expected.pointCounter = 0;
    findIntersectionPointsOfSegmentWithParallelogram(ABCD, MN, actual);
    QVERIFY2(actual.pointCounter == expected.pointCounter,
             "the segment does not intersect the parallelogram");

    // отрезок пересекает две стороны параллелограмма
    MN.setExtremePoints({8,10,11},{1,3,3});
    actual = {{0,0,0},{0,0,0}, 0};
    expected = {{4.5,6.5,7},{2.75,4.75,5}, 2};
    findIntersectionPointsOfSegmentWithParallelogram(ABCD, MN, actual);
    QVERIFY2(actual.pointCounter == expected.pointCounter,
             "the segment intersects two sides of the parallelogram");
    comparePoints(actual.intersectionPoint1, expected.intersectionPoint1,
             "the segment intersects two sides of the parallelogram");
    comparePoints(actual.intersectionPoint2, expected.intersectionPoint2,
             "the segment intersects two sides of the parallelogram");

    // отрезок проходит через угловую точку параллелограмма
    MN.setExtremePoints({3,5,1},{1,3,3});
    actual = {{0,0,0},{0,0,0}, 0};
    expected = {{2,4,2},{0,0,0}, 1};
    findIntersectionPointsOfSegmentWithParallelogram(ABCD, MN, actual);
    QVERIFY2(actual.pointCounter == expected.pointCounter,
             "the segment passes through the corner point of the parallelogram");
    comparePoints(actual.intersectionPoint1, expected.intersectionPoint1,
             "the segment passes through the corner point of the parallelogram");

    // отрезок проходит через две противоположные угловые точки параллелограмма
    MN.setExtremePoints({7,9,2},{1,3,8});
    actual = {{0,0,0},{0,0,0}, 0};
    expected = {{3,5,6},{5,7,4}, 2};
    findIntersectionPointsOfSegmentWithParallelogram(ABCD, MN, actual);
    QVERIFY2(actual.pointCounter == expected.pointCounter,
             "the segment passes through two opposite corner points of the parallelogram");
    comparePoints(actual.intersectionPoint1, expected.intersectionPoint1,
             "the segment passes through two opposite corner points of the parallelogram");
    comparePoints(actual.intersectionPoint2, expected.intersectionPoint2,
             "the segment passes through two opposite corner points of the parallelogram");

    // отрезок пересекает одну сторону, и проходит через угловую точку параллелограмма
    MN.setExtremePoints({0,2,4},{10,12,4});
    actual = {{0,0,0},{0,0,0}, 0};
    expected = {{2.5,4.5,4},{5,7,4}, 2};
    findIntersectionPointsOfSegmentWithParallelogram(ABCD, MN, actual);
    QVERIFY2(actual.pointCounter == expected.pointCounter,
             "the segment intersects one side, and passes through the corner point of the parallelogram");
    comparePoints(actual.intersectionPoint1, expected.intersectionPoint1,
             "the segment intersects one side, and passes through the corner point of the parallelogram");
    comparePoints(actual.intersectionPoint2, expected.intersectionPoint2,
             "the segment intersects one side, and passes through the corner point of the parallelogram");

    // отрезок лежит на одной прямой со стороной, и имеет с ней одну общую точку
    MN.setExtremePoints({4,6,10},{3,5,6});
    actual = {{0,0,0},{0,0,0}, 0};
    expected = {{3,5,6},{0,0,0}, 1};
    findIntersectionPointsOfSegmentWithParallelogram(ABCD, MN, actual);
    QVERIFY2(actual.pointCounter == expected.pointCounter,
             "the segment lies on the same straight line with the side, and has one point in common with it");
    comparePoints(actual.intersectionPoint1, expected.intersectionPoint1,
             "the segment lies on the same straight line with the side, and has one point in common with it");

}
