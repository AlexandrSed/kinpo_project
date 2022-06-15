/*!
\file
\brief заголовочный файл для тестового класса
*/
#ifndef TESTS_H
#define TESTS_H

#include <QObject>

/*!
 * \class tests
 * \brief class tests для тестирования функций и методов программы
 */
class tests : public QObject
{
    Q_OBJECT
public:
    explicit tests(QObject *parent = nullptr);

private slots:
    /*!
      testDetermineMutualArrangementOfLines
      тестирует метод DetermineMutualArrangementOfLines
     */
    void testDetermineMutualArrangementOfLines();

    /*!
     testFindIntersectionPointIntersectingLines
     тестирует метод FindIntersectionPointIntersectingLines
     */
    void testFindIntersectionPointIntersectingLines();

    /*!
     testDetermineSidesOfParallelogram
     тестирует функцию DetermineSidesOfParallelogram
     */
    void testDetermineSidesOfParallelogram();

    /*!
     testFindTheIntersectionPointOfSegmentsLyingOnIntersectingLines
     тестирует функцию FindTheIntersectionPointOfSegmentsLyingOnIntersectingLines
     */
    void testFindTheIntersectionPointOfSegmentsLyingOnIntersectingLines();

    /*!
     testFindIntersectionPointsOfSegmentWithParallelogram
     тестирует функцию FindIntersectionPointsOfSegmentWithParallelogram
     */
    void testFindIntersectionPointsOfSegmentWithParallelogram();
};

#endif // TESTS_H
