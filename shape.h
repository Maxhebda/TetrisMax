#ifndef SHAPE_H
#define SHAPE_H
#include <QVector>
#include <ctime>


class Shape
{
public:
    Shape();
    QVector <unsigned short int> getShape();
    unsigned short int getShapeCell(unsigned short int y, unsigned short int x);
    void rotateShape();                 // turn left
    void newShape();
    unsigned short int row();           // length row
    unsigned short int x();
    unsigned short int y();
    void goDown();
    void goLeft();
    void goRight();

private:
    QVector <unsigned short int> shape; // 0 - empty, 1 - stone, 2 - sand
    unsigned short int xPosition;
    unsigned short int yPosition;
    bool direction;                     // shape rotate direction - true = right, false = left
    unsigned short int lengthRow;
};

#endif // SHAPE_H
