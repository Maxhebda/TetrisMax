#ifndef SCORESCELL_H
#define SCORESCELL_H
#include <ctime>
#include <cstdlib>
#include <QString>

class ScoresCell
{
public:
    ScoresCell(QString value="100");
    void setX(double x);
    void setY(double y);
    unsigned short int getX();
    unsigned short int getY();
    QString getValue();
    void go();
    bool itsDead();

private:
    double x;
    double y;
    double gravitation;
    double xSpeed;
    double ySpeed;
    unsigned short int step;
    unsigned short int lengthOfLife;
    QString value;
};

#endif // SCORESCELL_H
