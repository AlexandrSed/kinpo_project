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
    CD.setExtremePoints({1,4,5},{3,0,3});
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
    QVERIFY2(AB.determineMutualArrangementOfLines(CD)==intersection,"the lines intersect and both lie in the same plane parallel to the coordinate, and one line is parallel to the coordinate axis");
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
    comparePoints(AB.findIntersectionPointIntersectingLines(CD), expectedAnswer, "intersection, and one of the lines is parallel to the coordinate axis OX");

    // прямые пересекаются, и одна из них параллельна координатной оси OY
    AB.setExtremePoints({2,6,5},{2,2,5});
    CD.setExtremePoints({7,0,2},{5,4,8});
    expectedAnswer = {2,6,5};
    comparePoints(AB.findIntersectionPointIntersectingLines(CD), expectedAnswer, "intersection, and one of the lines is parallel to the coordinate axis OY");

    // прямые пересекаются, и одна из них параллельна координатной оси OZ
    AB.setExtremePoints({2,5,6},{2,5,2});
    CD.setExtremePoints({0,2,7},{4,8,5});
    expectedAnswer = {2,5,6};
    comparePoints(AB.findIntersectionPointIntersectingLines(CD), expectedAnswer, "intersection, and one of the lines is parallel to the coordinate axis OZ");

    // прямые пересекаются и лежат в одной плоскости, параллельной координатной плоскости XOY
    AB.setExtremePoints({1,1,3},{3,2,3});
    CD.setExtremePoints({1,3,3},{2,-1,3});
    expectedAnswer = {1.44,1.22,3};
    comparePoints(AB.findIntersectionPointIntersectingLines(CD), expectedAnswer, "intersection and lie in the same plane parallel to the coordinate plane XOY");

    // прямые пересекаются и лежат в одной плоскости, параллельной координатной плоскости XOZ
    AB.setExtremePoints({1,3,1},{3,3,2});
    CD.setExtremePoints({1,3,3},{2,3,-1});
    expectedAnswer = {1.44,3,1.22};
    comparePoints(AB.findIntersectionPointIntersectingLines(CD), expectedAnswer, "intersection and lie in the same plane parallel to the coordinate plane XOZ");

    // прямые пересекаются и лежат в одной плоскости, параллельной координатной плоскости YOZ
    AB.setExtremePoints({3,1,1},{3,3,2});
    CD.setExtremePoints({3,1,3},{3,2,-1});
    expectedAnswer = {1.44,1.22,3};
    comparePoints(AB.findIntersectionPointIntersectingLines(CD), expectedAnswer, "intersection and lie in the same plane parallel to the coordinate plane YOZ");

    /* прямые пересекаются и лежат обе в одной плоскости параллельной
 координатной, и одна прямая параллельна координатной оси*/
    AB.setExtremePoints({3,1,1},{3,3,2});
    CD.setExtremePoints({3,2,0},{3,2,2});
    expectedAnswer = {3,2,1.5};
    comparePoints(AB.findIntersectionPointIntersectingLines(CD), expectedAnswer, "the lines intersect and both lie in the same plane parallel to the coordinate, and one line is parallel to the coordinate axis");
}

