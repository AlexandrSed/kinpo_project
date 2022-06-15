/*!
\file
\brief Заголовочный файл с описанием структур, классов, и функций программы
*/
#ifndef HEADER_H
#define HEADER_H

#include <QObject>
#include <QString>
#include <QChar>

/*!
\enum Errors

Набор возможных ошибок
*/
enum Errors
{
    noParallelogram, ///< данная фигура не является параллелограммом
    pointsParallelogramRepeat, ///< точки параллелограмма повторяются
    segmentIntoPoint, ///< отрезок вырождается в точку
    MNCoincidesWithSide ///< отрезок совпадает со стороной параллелограмма
};

/*!
\struct point

Для представления точки в трехмерном пространстве
 */
struct point
{
    double x,y,z; ///< координаты точки
};

/*!
логический оператор "не равно" для точек
\param p1 первая точка
\param p2 вторая точка
\return true в случае, если точки не равны, false в случае если точки равны
*/
bool operator!=(point p1, point p2);

/*!
логический оператор "равно" для точек
\param p1 первая точка
\param p2 вторая точка
\return true в случае, если точки равны, false в случае если точки не равны
*/
bool operator==(point p1, point p2);

/*!
перевести точку в строковое представление
\param p точка
\return строка, в которой координаты точки перечислены через запятую
*/
QString pointToQStr(point &p);

/*!
\enum mutualArrangementOfLines

Набор возможных расположений прямых, относительно друг друга
*/
enum mutualArrangementOfLines{
    parallel, ///< параллельны
    perpendicular, ///< перпендикулярны
    intersection, ///< пересекаются
    crossing, ///< скрещиваются
    coincidence ///< совпадают
};

/*!
 * \class segment
 * \brief класс segment для представления отрезков в трехмерном пространстве и работы с ними
 */
class segment
{

public:

    /*!
    создает отрезок с нулевыми значениями координат крайних точек и направляющего вектора
    */
    segment();

    /*!
    создает отрезок с нулевыми значениями координат направляющего вектора и крайними точками, как у переданного отрезка
    \param [in] s1 отрезок
    */
    segment(segment &s1);

    /*!
    создает отрезок с нулевыми значениями координат направляющего вектора и данными крайними точками
    \param point1 первая крайняя точка
    \param point2 вторая крайняя точка
    */
    segment(point point1, point point2);
    /*!
    расчитать направляющий вектор
    \return координаты направляющего вектора отрезка
    */
    point calculateGuideVector();

    /*!
    установить крайние точки
    \param point1 первая крайняя точка
    \param point2 вторая крайняя точка
    */
    void setExtremePoints(point point1, point point2);

    /*!
    определить взаимное расположение прямых, на которых лежат отрезки
    \param segment2 отрезок
    \return взаимное расположение прямых
    */
    mutualArrangementOfLines determineMutualArrangementOfLines(segment &segment2);

    /*!
    Найти точку пересечения пересекающихся прямых, на которых лежат отрезки
    \param segment2 отрезок
    \return точка пересечения
    */
    point findIntersectionPointIntersectingLines(segment &segment2);
    /*!
    получить первую точку
    \return первую точку отрезка
    */
    point getExtremePoint1();

    /*!
    получить вторую точку
    \return вторую точку отрезка
    */
    point getExtremePoint2();

    /*!
    получить направляющий вектор
    \return координаты направляющего вектора отрезка
    */
    point getGuideVector();

    /*!
    оператор присваивания
    \param other отрезок
    */
    void operator=(segment other);

private:
    /// направляющий вектор
    point guideVector;

    /// крайние точки
    point extremePoint1, extremePoint2;

};

/*!
\struct intersectionPoints

Структура для представления ответа в виде двух пересекающихся точек и счетчика найденных точек
*/
struct intersectionPoints
{
    point intersectionPoint1, intersectionPoint2; ///< точки пересечения
    int pointCounter; ///< счетчик точек
};

/*!
\struct parallelogram

структура для представления параллелограмма, его угловых точек и сторон
*/
struct parallelogram
{
    point A, B, C, D; ///< угловые точки параллелограмма
    segment side1, side2, side3, side4; ///< стороны параллелограмма
};

/*!
Найти точки пересечения отрезка с параллелограммом
\param [in] ABCD параллелограмм
\param [in] MN отрезок
\param [out] answer точки пересечения и их счетчик
\throw pointsParallelogramRepeat координаты разных точек параллелограмма повторяются
\throw segmentIntoPoint отрезок вырождается в точку
\throw MNCoincidesWithSide отрезок и сторона параллелограмма совпадают
*/
void findIntersectionPointsOfSegmentWithParallelogram(parallelogram &ABCD, segment MN, intersectionPoints &answer);

/*!
Найти точку пересечения двух отрезков, лежащих на пересекающихся прямых
\param [in] segmentA первый отрезок
\param [in] segmentB вторый отрезок
\param [in,out] answer точка пересечения, в зависимости от счетчика записывается в соответствующую позицию
*/
void findTheIntersectionPointOfSegmentsLyingOnIntersectingLines(segment segmentA, segment segmentB, intersectionPoints &answer);

/*!
определить стороны параллелограмма
\param [in,out] ABCD точки параллелограмма на вход, и стороны - на выход
\throw noParallelogram указанный четырёхугольник не является параллелограммом
*/
void determineSidesOfParallelogram(parallelogram &ABCD);



#endif // HEADER_H
