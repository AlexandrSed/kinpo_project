#ifndef TESTS_H
#define TESTS_H

#include <QObject>

class tests : public QObject
{
    Q_OBJECT
public:
    explicit tests(QObject *parent = nullptr);

private slots:
    void testDetermineMutualArrangementOfLines();
    void testFindIntersectionPointIntersectingLines();
    void testDetermineSidesOfParallelogram();
};

#endif // TESTS_H
