#ifndef SCORESCELL_H
#define SCORESCELL_H
#include <ctime>
#include <cstdlib>

class ScoresCell
{
public:
    ScoresCell();
    void setX(double x);
    void setY(double y);
    unsigned short int getX();
    unsigned short int getY();
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
};

#endif // SCORESCELL_H
