#include <QCoreApplication>
#include "header.h"
#include <QTextStream>
#include <QFile>
#include <QtTest/QTest>
#include "tests.h"

int main(int argc, char *argv[])
{
    QString inputQStr; ///< Строка входных данных
    bool open = true;

    /// Если есть второй переданный аргумент...
    if(argc>1)
    {
        /// Файл, именем которого является второй аргумент
        QFile in(argv[1]);

        /// Если входной файл удается открыть для чтения...
        if(in.open(QIODevice::ReadOnly))
        {
            /// Считываем из входного файла строку
            QTextStream ReadStrem(&in);
            inputQStr = ReadStrem.readLine();

            /// Закрываем файл
            in.close();
        }
        else ///< Иначе...
        {
            /// Запоминаем, что входной файл не был открыт
            open = false;
        }
    }
    else ///< Иначе...
    {
        /// Выдать ошибку: входной файл не указан
        qDebug()<<"input file not is not specified";
    }

    /// Разбиваем входную строку на части
    QStringList input = inputQStr.split(" ", Qt::SkipEmptyParts);

    /// Если есть третий переданный аргумент...
    if(argc >2)
    {
        /// Файл, именем которого является третий аргумент
        QFile fout(argv[2]);

        /// Если выходной файл удается открыть для записи...
        if(fout.open(QIODevice::WriteOnly))
        {

            QTextStream writeStream(&fout);
            bool isNum = true;

            /// Для каждого символа входной строки, пока не найдется символ, не являющийся цифрой или пробелом...
            for(int i = 0; i < inputQStr.length() && isNum == true; i++)
            {
                /// Запоминаем, если символ является цифрой или пробелом...
                isNum = inputQStr[i].isNumber() || inputQStr[i] == ' ';
            }

            /// Если указанный входной файл не существует...
            if(!open)
            {
                /// Выдать ошибку, если указанный входной файл не существует
                writeStream<<"указанный входной файл не существует";
            }
            /// Иначе, если количество частей, на которые разбили входную строку, больше 18
            else if(input.count() < 18)
            {
                /// Выдать ошибку, если количества введенных чисел недостаточно для расчета
                writeStream<<"количества введенных чисел недостаточно для расчета";
            }
            /// Иначе, если количество частей, на которые разбили входную строку, меньше 18
            else if(input.count() > 18)
            {
                /// Выдать ошибку, если количество введенных чисел больше, чем надо
                writeStream<<"количества введенных чисел больше, чем надо";
            }
            /// Иначе, если один или несколько аргументов не являются числом
            else if(!isNum)
            {
                /// Выдать ошибку, если один или несколько аргументов не являются числом
                writeStream << "один или несколько аргументов не являются числом";
            }
            else
            {
                /// преобразуем данные из строки в числа...
                point A = {input[0].toDouble(),input[1].toDouble(), input[2].toDouble()};
                point B = {input[3].toDouble(),input[4].toDouble(), input[5].toDouble()};
                point C = {input[6].toDouble(),input[7].toDouble(), input[8].toDouble()};
                point D = {input[9].toDouble(),input[10].toDouble(), input[11].toDouble()};
                point M = {input[12].toDouble(),input[13].toDouble(), input[14].toDouble()};
                point N = {input[15].toDouble(),input[16].toDouble(), input[17].toDouble()};
                segment MN(M, N), AB, BC, CD, AD;
                parallelogram ABCD = {A, B, C, D, AB, BC, CD, AD};
                intersectionPoints answer;
                answer.pointCounter = 0;
                try
                {
                    findIntersectionPointsOfSegmentWithParallelogram(ABCD, MN, answer);
                    QString answerStr("количество точек пересечения: ");
                    answerStr.append(QString::number(answer.pointCounter));

                    if(answer.pointCounter>0)
                    {
                        answerStr.append("\n точки: ");
                        answerStr.append(pointToQStr(answer.intersectionPoint1));
                        if(answer.pointCounter>1)
                        {
                            answerStr.append("; ");
                            answerStr.append(pointToQStr(answer.intersectionPoint2));
                        }
                    }
                    writeStream<<answerStr;
                }
                catch (Errors error)
                {
                    if(error == noParallelogram)
                        writeStream << "указанный четырёхугольник не является параллелограммом";
                    else if(error == pointsParallelogramRepeat)
                        writeStream << "координаты разных точек параллелограмма повторяются";
                    else if(error == segmentIntoPoint)
                        writeStream << "Отрезок вырождается в точку";
                    else if(error == MNCoincidesWithSide)
                        writeStream << "отрезок и сторона параллелограмма совпадают";
                }
            }

            fout.close();
        }
    }
    else ///< Иначе...
    {
        /// Выдать ошибку: выходной файл не указан
        qDebug()<<"output file not is not specified";
    }

    /// Тесты
    QTest::qExec(new tests);
    return 0;

}

/// Определить стороны параллелограмма
void determineSidesOfParallelogram(parallelogram &ABCD)
{
    segment AB(ABCD.A, ABCD.B), CD(ABCD.C, ABCD.D);
    segment AC(ABCD.A, ABCD.C), DB(ABCD.D, ABCD.B);
    segment AD(ABCD.A, ABCD.D), BC(ABCD.B, ABCD.C);

    /// если прямая АВ параллельна прямой CD…
    if(AB.determineMutualArrangementOfLines(CD) == parallel)
    {
        /// если AC параллельна BD…
        if(AC.determineMutualArrangementOfLines(DB) == parallel)
        {
            /// вернуть: стороны параллелограмма AB, CD, AC, BD
            ABCD.side1 = AB;
            ABCD.side2 = CD;
            ABCD.side3 = AC;
            ABCD.side4 = DB;
        }
        else if(AD.determineMutualArrangementOfLines(BC) == parallel) // иначе, если AD параллельна BC…
        {
            /// вернуть: стороны параллелограмма AB, CD, AD, BC
            ABCD.side1 = AB;
            ABCD.side3 = CD;
            ABCD.side4 = AD;
            ABCD.side2 = BC;
        }
        else ///< иначе…
        {
            /// выдать ошибку: указанный четырёхугольник не является параллелограммом
        }
    }
    else if(AC.determineMutualArrangementOfLines(DB) == parallel) // иначе, если AC параллельна BD…
    {
        if(AD.determineMutualArrangementOfLines(BC) == parallel) // если AD параллельна BC…
        {
            /// вернуть: стороны параллелограмма AC, BD, AD, BC
            ABCD.side4 = AC;
            ABCD.side2 = DB;
            ABCD.side1 = AD;
            ABCD.side3 = BC;
        }
        else ///< иначе…
        {
            /// выдать ошибку: указанный четырёхугольник не является параллелограммом
            throw noParallelogram;
        }
    }
    else ///< иначе…
    {
        /// выдать ошибку: указанный четырёхугольник не является параллелограммом
        throw noParallelogram;
    }

}

/// Найти точку пересечения двух отрезков, лежащих на пересекающихся прямых
void findTheIntersectionPointOfSegmentsLyingOnIntersectingLines(segment segmentA, segment segmentB, intersectionPoints &answer)
{
    /// Найти точку пересечения прямых на которых лежат отрезки…
    point intersectionPoint = segmentA.findIntersectionPointIntersectingLines(segmentB);

    /// если точка пересечения лежит на обоих отрезках…
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
        /// …вернуть ее координаты и счетчик точек пересечения повысить на один
        if(answer.pointCounter == 0)
            answer.intersectionPoint1 = intersectionPoint;
        else
            answer.intersectionPoint2 = intersectionPoint;

        answer.pointCounter++;
    }

}

/// Найти точки пересечения отрезка с параллелограммом
void findIntersectionPointsOfSegmentWithParallelogram(parallelogram &ABCD, segment MN, intersectionPoints &answer)
{
    /// Выдать ошибку, если координаты разных точек параллелограмма повторяются
    if(ABCD.A == ABCD.B || ABCD.A == ABCD.C || ABCD.A == ABCD.D || ABCD.B == ABCD.C || ABCD.B == ABCD.D || ABCD.C == ABCD.D)
        throw pointsParallelogramRepeat;

    /// Выдать ошибку, если Отрезок вырождается в точку
    if(MN.getExtremePoint1() == MN.getExtremePoint2())
        throw segmentIntoPoint;

    determineSidesOfParallelogram(ABCD); ///< Определить стороны параллелограмма…

    segment side;

    for(int i = 1; i<=4 && answer.pointCounter<2 ; i++) ///< Для каждой стороны параллелограмма…
    {
        if(i==1)
            side = ABCD.side1;
        else if(i==2)
            side = ABCD.side2;
        else if(i==3)
            side = ABCD.side3;
        else
            side = ABCD.side4;

        /*!
         * Если прямые, на которых лежат отрезок и сторона пересекаются, и нет найденной точки пересечения,
         * которая равнялась бы одному из концов стороны…
         */
        if((side.determineMutualArrangementOfLines(MN) == intersection ||
                side.determineMutualArrangementOfLines(MN) == perpendicular) &&
                answer.intersectionPoint1 != side.getExtremePoint1() &&
                answer.intersectionPoint1 != side.getExtremePoint2())
        {
            /// Найти точку пересечения отрезка со стороной…
            findTheIntersectionPointOfSegmentsLyingOnIntersectingLines(side, MN, answer);
        }
        /// Иначе, если прямые совпадают…
        else if(side.determineMutualArrangementOfLines(MN) == coincidence)
        {
            /// Если отрезок частично совпадает со стороной…
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
                throw MNCoincidesWithSide; ///< Выдать ошибку: отрезок и сторона параллелограмма совпадают
            }
        }
    }

}

bool operator!=(point p1, point p2)
{
    return p1.x != p2.x || p1.y != p2.y || p1.z != p2.z;
}

bool operator==(point p1, point p2)
{
    return p1.x == p2.x && p1.y == p2.y && p1.z == p2.z;
}

QString pointToQStr(point &p)
{
    QString strPoint(QString::number(p.x, 'f', 2));
    strPoint.remove(QRegularExpression("0$|.00$"));
    strPoint.append(',');

    strPoint.append(QString::number(p.y, 'f', 2));
    strPoint.remove(QRegularExpression("0$|.00$"));
    strPoint.append(',');

    strPoint.append(QString::number(p.z, 'f', 2));
    strPoint.remove(QRegularExpression("0$|.00$"));

    return strPoint;
}
