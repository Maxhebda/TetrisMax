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
    void setShapeCell(unsigned short int y, unsigned short int x, unsigned short int i);
    void rotateShape();                 // turn left
    void newShape();
    unsigned short int row();           // length row
    short int x();
    short int y();
    void setX(unsigned short int);
    void goDown();
    void goLeft();
    void goRight();
    unsigned short int type();

private:
    QVector <unsigned short int> shape; // 0 - empty, 1 - stone, 2 - sand
    unsigned short int xPosition;
    unsigned short int yPosition;
    bool direction;                     // shape rotate direction - true = right, false = left
    unsigned short int lengthRow;
    uint8_t typeOfShape;    // 0 - other, 1 - point, 2 - line
};

#endif // SHAPE_H
