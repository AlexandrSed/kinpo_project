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

point segment::calculateGuideVector()
{

}

void segment::setExtremePoints(point point1, point point2)
{

}

mutualArrangementOfLines segment::determineMutualArrangementOfLines(segment &segment2)
{

}

point segment::findIntersectionPointIntersectingLines(segment &segment2)
{

}
