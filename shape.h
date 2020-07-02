#ifndef SHAPE_H
#define SHAPE_H
#include <QVector>
#include <ctime>


class Shape
{
public:
    Shape();
    QVector <unsigned short int> getShape();
    void rotateShape();                 // turn left
    void newShape();

private:
    QVector <unsigned short int> shape; // 0 - empty, 1 - stone, 2 - sand
    unsigned short int x;
    unsigned short int y;
    bool direction;                     // shape rotate direction - true = right, false = left
    void clearShape();
};

#endif // SHAPE_H
